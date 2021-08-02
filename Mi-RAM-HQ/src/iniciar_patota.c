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

//funcion mock
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
    seg_pcb->data = malloc(8); //8 tamaño de pcb
    seg_pcb->tam_data = 8;
    seg_pcb->tipo = PCB;

    memcpy(seg_tarea->data, data.tareas, strlen(data.tareas));//dato de la tarea
    
    memcpy(seg_pcb->data, &data.patota_id, sizeof(uint32_t));
    uint32_t dir_log =  strlen(data.tareas); //0+tamaño de la tarea
    memcpy(seg_pcb->data+sizeof(uint32_t), &dir_log, sizeof(uint32_t));

    list_add(lista_data, seg_tarea);
    list_add(lista_data, seg_pcb);

    for (int i = 0; i < data.cant_tripulantes; i++)
    {
        int offset = 0;
        t_data_segmento * seg_tcb = malloc(sizeof(t_data_segmento));
        seg_tcb->data = malloc(21);
        seg_tcb->tam_data = 21; //tam del tcb
        seg_tcb->tipo = TCB;

        uint32_t tid = data.id_primer_tripulante+i;
        char estado = 'N';
        Posicion pos = get_posicion(data.posiciones,i+1);
        uint32_t prox_tarea = 1;
        uint32_t puntero_pcb= 1+8;//numero de segmento + limite = 1+8

        memcpy(seg_tcb->data,&tid,sizeof(uint32_t));
        offset += sizeof(uint32_t);

        memcpy(seg_tcb->data+offset,&estado,sizeof(char));
        offset += sizeof(char);

        memcpy(seg_tcb->data+offset,&pos.posx,sizeof(int));
        offset += sizeof(int);

        memcpy(seg_tcb->data+offset,&pos.posy,sizeof(int));
        offset += sizeof(int);

        memcpy(seg_tcb->data+offset,&prox_tarea,sizeof(uint32_t));
        offset += sizeof(uint32_t);

        memcpy(seg_tcb->data+offset,&puntero_pcb,sizeof(uint32_t));

        list_add(lista_data, seg_tcb);
    }

    return lista_data;
    
}
