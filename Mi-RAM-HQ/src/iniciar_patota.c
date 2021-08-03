#include "iniciar_patota.h"

/* funciones privadas */
t_list * create_list_data_segmento(t_iniciar_patota data);

/* ******************* */

bool iniciar_patota_segmentacion(t_iniciar_patota init_patota){

    bool res_iniciar_patota;
    
    int tam_info = 8 + strlen(init_patota.tareas) + init_patota.cant_tripulantes* 21;//8 tam de PCB y 21 tam TCB

    t_list * data_segmentos = create_list_data_segmento(init_patota); // una lista de t_data_segmento

    if (se_puede_escribir(tam_info))
    {
        res_iniciar_patota = true;
        t_tabla_segmentos * tabla_seg = malloc(sizeof(t_tabla_segmentos));
        tabla_seg->segmentos = list_create();
        tabla_seg->pid = init_patota.patota_id;

        void agregar_segmento(t_data_segmento * data){
            t_segmento * segmento = escribir_segmentacion_pura(data);

            list_add(tabla_seg->segmentos, segmento);
        }

        list_iterate(data_segmentos, agregar_segmento); //equivale al for

        agregar_tabla_de_segmento(tabla_seg);
    }
    else
    {
        res_iniciar_patota = false;
    }
    
    
    return res_iniciar_patota;
}


/* *************************************** */
Posicion casteo_string_a_posicion(char * s_posicion){
    Posicion posicion_cast;

    char ** cordenadas = string_split(s_posicion,"|");
    posicion_cast.posx= atoi(cordenadas[0]);
    posicion_cast.posy= atoi(cordenadas[2]);

    return posicion_cast;
}

t_data_segmento * casteo_tareas_a_t_data_segmento(char * tareas){
    t_data_segmento * data = malloc(sizeof(t_data_segmento));
    data->data = malloc(strlen(tareas));
    data->tam_data = strlen(tareas);

    memcmp(data->data, tareas, strlen(tareas));

    return data;
}

Posicion get_posicion(char* posiciones, int indice){
    Posicion pos;
    pos.posx=0;
    pos.posy=0;
    if(strcmp(posiciones, "")!=0){
        pos = get_posicion_STR(posiciones, indice);
    }
    return pos;
}

t_list * create_list_data_segmento(t_iniciar_patota data){
    t_list * lista_data = list_create();

    t_data_segmento * seg_tarea = malloc(sizeof(t_data_segmento));
    seg_tarea->data = malloc(strlen(data.tareas));
    seg_tarea->tam_data = strlen(data.tareas);
    seg_tarea->tipo = TAREAS;

    t_data_segmento * seg_pcb = malloc(sizeof(t_data_segmento));
    void* stream_pcb =  get_stream_pcb(data);
    seg_pcb->data = stream_pcb; //8 tamaño de pcb
    seg_pcb->tam_data = 8;
    seg_pcb->tipo = PCB;

    memcpy(seg_tarea->data, data.tareas, strlen(data.tareas));//dato de la tarea
    
    list_add(lista_data, seg_tarea);
    list_add(lista_data, seg_pcb);

    void* stream_tcbs = get_stream_tcbs(data);
    int offset = 0;
    for (int i = 0; i < data.cant_tripulantes; i++)
    {
        void* stream_tcb = malloc(21);
        memcpy(stream_tcb, stream_tcbs + offset, 21);
        offset += 21;

        t_data_segmento * seg_tcb = malloc(sizeof(t_data_segmento));
        seg_tcb->data = stream_tcb;
        seg_tcb->tam_data = 21; //tam del tcb
        seg_tcb->tipo = TCB;

        list_add(lista_data, seg_tcb);
    }

    return lista_data;
    
}

bool iniciar_patota_paginacion(t_iniciar_patota data){
    int tamanio_total = 8 + 21 * data.cant_tripulantes + data.long_tareas;
    bool isAllow = existe_memoria_disponible_paginacion(bitmap_memoria_real, bitmap_memoria_virtual, tamanio_total);
    if(!isAllow) return false;

    void* stream_pcb = get_stream_pcb(data);
    void* stream_tcbs = get_stream_tcbs(data);
    
    int offset_informacion = 0;
    void* informacion = malloc(tamanio_total);
    memcpy(informacion+offset_informacion, data.tareas, data.long_tareas);
    offset_informacion+=data.long_tareas;
    memcpy(informacion+offset_informacion, stream_pcb, 8);
    offset_informacion+=8;    
    memcpy(informacion+offset_informacion, stream_tcbs, 21*data.cant_tripulantes);
    
    guardar_info_patota(data, informacion);
    return true;
}

void guardar_info_patota(t_iniciar_patota data, void* informacion){
    int tamanio_total = 8 + 21 * data.cant_tripulantes + data.long_tareas;
    int pagina_tam = get_tamanio_tamanio_pagina();
    int paginas_que_necesita = tamanio_total/pagina_tam;
    if(tamanio_total%pagina_tam!=0) paginas_que_necesita++;

    t_list* pages = list_create();
    t_list* tripulante_ids = list_create();
    int page_id = 0;
    int offset = 0;
    int tripulante_id = data.id_primer_tripulante;
    for(int c=0; c<paginas_que_necesita; c++){
        page_id++;
        void* informacion_dividida = malloc(pagina_tam);
        memcpy(informacion_dividida, informacion + offset, pagina_tam);
        offset+=pagina_tam;
        int frameid = get_first_frame_disponible(bitmap_memoria_real);

        t_page* page = malloc(sizeof(t_page));
        page->page = page_id;
        page->frame = frameid;
        page->presencia = true;
        page->uso = true;
        page->timestamp = temporal_get_string_time();
        // fijarse las comillas dobles 

        int base = frameid*pagina_tam;
        escribir_memoria_real(informacion_dividida, base, pagina_tam);

        list_add(pages, page);
        list_add(tripulante_ids, tripulante_id);
        tripulante_id++;
    }
    
    t_table_page* table_page = malloc(sizeof(t_table_page));
    table_page->patota_id = data.patota_id;
    table_page->pages = pages;
    table_page->tripulante_ids = tripulante_ids;
    table_page->cant_tripulantes = data.cant_tripulantes;
    table_page->cant_caracteres_tarea = data.long_tareas;

    list_add(list_tablas_paginacion, table_page);
}
// "hit-mongostore-validaciones"
void* get_stream_pcb(t_iniciar_patota data){
    void* stream = malloc(8);
    int offset = 0;
    memcpy(stream+offset, &data.patota_id, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    uint32_t dir_log =  strlen(data.tareas); //0+tamaño de la tarea
    memcpy(stream + offset, &dir_log, sizeof(uint32_t));
    return stream;
}

void* get_stream_tcbs(t_iniciar_patota data){
    void* stream = malloc(21*data.cant_tripulantes);
    int offset = 0;
    int tripulante_id_inicial = data.id_primer_tripulante;
    for (int i = 0; i < data.cant_tripulantes; i++)
    {
        Posicion pos = get_posicion(data.posiciones,i+1);

        t_TCB tcb;
        tcb.tid = tripulante_id_inicial;
        tcb.estado = 'N';
        tcb.posx = pos.posx;
        tcb.posy = pos.posy;
        tcb.prox_tarea = 1;
        tcb.puntero_pcb = 1+8;
        
        void* stream_tcb = get_stream_tcb(tcb);
        memcpy(stream + offset, stream_tcb, 21);
        offset += 21;

        tripulante_id_inicial++;
    }

    return stream;
}