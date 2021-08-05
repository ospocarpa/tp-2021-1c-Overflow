#include "memoria.h"

void * memoria_principal = NULL;
void * memoria_virtual = NULL;

/* Declaracion de funciones privadas */


/* ************************************************** */
void inicializacion_estructuras(){
    char * tipo_memoria = get_esquema_memoria();
    //printf("%s\n", tipo_memoria);
    if(strcmp(tipo_memoria,"SEGMENTACION") == 0){
        //printf("Paso\n");
        set_algoritmo_ubicacion(get_criterio_de_seleccion());
        list_tablas_segmentos = list_create();
        iniciar_tabla_huecos(get_tamanio_memoria());
    }
    else{
        list_create(list_tablas_paginacion);
        list_create(tablas_pag_libre);

        int cantidad_frames_virtual = get_tamanio_swap();
        int cantidad_frames = get_tamanio_tamanio_pagina();

        char* path = get_path_swap();
        int file_size = cantidad_frames_virtual/8;
        int fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
        ftruncate(fd, file_size);
        void* stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);

        void* puntero_bitmap = malloc(cantidad_frames/8);
        bitmap_memoria_real = bitarray_create_with_mode(puntero_bitmap, cantidad_frames/8, LSB_FIRST);
        bitmap_memoria_virtual = bitarray_create_with_mode(stream, cantidad_frames_virtual/8, LSB_FIRST);

        limpiar_bit_map(bitmap_memoria_real);
        limpiar_bit_map(bitmap_memoria_virtual);
    }
}

void iniciar_memoria_principal(int tam_memoria){

    if(memoria_principal == NULL){
        memoria_principal = malloc(tam_memoria);
		//logger_info("Se inicio memoria principal de tamaño: [%d]", tam_memoria);
    }
}

void iniciar_memoria_virtual(int tam_memoria){
    if(memoria_virtual == NULL){
        memoria_virtual = malloc(tam_memoria);
    }
}

void liberar_memoria_principal(){
    free(memoria_principal);
    memoria_principal = NULL;
}

void liberar_memoria_virtual(){
    free(memoria_virtual);
    memoria_virtual = NULL;
}

void cargar_informacion_PCB_a_MP(t_PCB pcb,int base){
    
    int offset = base;
    memcpy(memoria_principal + offset, &pcb.pid,sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(memoria_principal + offset, &pcb.tareas,sizeof(uint32_t));

}

void cargar_informacion_tareas_a_MP(char *tareas,int base){
    memcpy(memoria_principal+base,tareas,strlen(tareas));
}

t_PCB leer_info_PCB(int base){

    t_PCB  pcb;
    int offset =base;
    memcpy(&pcb.pid,memoria_principal+offset,sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&pcb.tareas,memoria_principal+offset,sizeof(uint32_t));

    return pcb;

}

t_TCB leer_info_TCB(int base){
    void* stream = malloc(21);
    memcpy(stream, memoria_principal + base, 21);
    t_TCB tcb = leer_info_TCB_generico(stream);
    return tcb;
}

t_TCB leer_info_TCB_generico(void* stream){
    t_TCB  tcb;
    
    int offset = 0;
    memcpy(&tcb.tid, stream + offset, sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(&tcb.estado, stream + offset, sizeof(char));
    offset += sizeof(char);
    memcpy(&tcb.posx, stream + offset, sizeof(int));
    offset +=sizeof(int);
    memcpy(&tcb.posy, stream + offset, sizeof(int));
    offset +=sizeof(int);
    memcpy(&tcb.prox_tarea, stream + offset, sizeof(uint32_t));
    offset +=sizeof(uint32_t);
    memcpy(&tcb.puntero_pcb, stream + offset, sizeof(uint32_t));

    return tcb;
}

void* get_stream_tcb(t_TCB tcb){
    // uint32_t tid;
    // char estado;
    // int posx;
    // int posy;
    // uint32_t prox_tarea;
    // uint32_t puntero_pcb;
    void* stream = malloc(21);
    
    int offset = 0;
    memcpy(stream + offset, &tcb.tid,sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(stream + offset, &tcb.estado,sizeof(char));
    offset += sizeof(char);
    memcpy(stream + offset, &tcb.posx,sizeof(int));
    offset +=sizeof(int);
    memcpy(stream + offset, &tcb.posy,sizeof(int));
    offset +=sizeof(int);
    memcpy(stream + offset, &tcb.prox_tarea,sizeof(uint32_t));
    offset +=sizeof(uint32_t);
    memcpy(stream + offset, &tcb.puntero_pcb,sizeof(uint32_t));   

    return stream;
}

void cargar_data_segmento(t_data_segmento * data_segmento, int base ){
    memcpy(memoria_principal+base, data_segmento->data, data_segmento->tam_data);
}

char* get_tareas(int patota_id){
    char * tipo_memoria = get_esquema_memoria();

    if(strcmp(tipo_memoria,"SEGMENTACION") == 0){
        return get_tareas_segmentacion(patota_id);
    }
    else{
        return get_tareas_paginacion(patota_id);
    }
}

void set_tripulante(t_TCB tcb, int patotaid){
    char * tipo_memoria = get_esquema_memoria();

    if(strcmp(tipo_memoria,"SEGMENTACION") == 0){
        set_tripulante_por_segmentacion(tcb, patotaid);
    }
    else{
        set_TCB_paginacion(tcb, patotaid);
    }
}

t_TCB get_TCB(int patota_id, int tripulante_id){
    t_TCB tcb;
    char * tipo_memoria = get_esquema_memoria();

    if(strcmp(tipo_memoria,"SEGMENTACION") == 0){
        tcb = get_TCB_segmentacion_pura(patota_id, tripulante_id);
    }
    else
    {
        tcb = get_TCB_paginacion(patota_id, tripulante_id);
    }
    return tcb;
}

bool iniciar_patota(t_iniciar_patota init_patota){
    bool isAllow = false;
    char * tipo_memoria = get_esquema_memoria();
    if(strcmp(tipo_memoria,"SEGMENTACION") == 0)
    {
        isAllow = iniciar_patota_segmentacion(init_patota);
    }
    else
    {
        isAllow = iniciar_patota_paginacion(init_patota);
    }
    return isAllow;
}

void mostrar_tcb(t_TCB tcb){
    printf("tid: %d\n", tcb.tid);
    printf("Estado: %c\n", tcb.estado);
    printf("Pos x: %d\n", tcb.posx);
    printf("Pos y: %d\n", tcb.posy);
    printf("Próxima tarea: %d\n", tcb.prox_tarea);
    printf("Puntero pcb: %d\n", tcb.puntero_pcb);
}

void method_sigusr1(){
    char* contenido = "";
    //Mostrar dump de la memoria principal
    if(strcmp(get_esquema_memoria(), "SEGMENTACION")==0){
        //Realizar compactacion
        compactacion();
        contenido = dump_segmentacion_pura();
    }else{
        contenido = dump_paginacion();
    }

    char *timestamp = temporal_get_string_time("");
    char* path = string_new();
    string_append_with_format(&path, "/home/utnso/tp-2021-1c-Overflow/Mi-RAM-HQ/Dump %s.dmp", timestamp);

    int file_size = strlen(contenido);
    int fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    ftruncate(fd, file_size);
    void* stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
    strcpy(stream, contenido);
}