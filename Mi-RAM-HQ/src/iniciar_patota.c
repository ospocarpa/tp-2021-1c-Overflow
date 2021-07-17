#include "iniciar_patota.h"

bool iniciar_patota_segmentacion(t_iniciar_patota init_patota){

    bool res_iniciar_patota;
    //genero ids de tripulantes
    uint32_t arr_pid[init_patota.cant_tripulantes];

    for (size_t i = 0; i < init_patota.cant_tripulantes; i++)
    {
        arr_pid[i]= init_patota.id_primer_tripulante + i;
    }
    //

    int tam_info = 8 + strlen(init_patota.tareas) + init_patota.cant_tripulantes* 21;//8 tam de PCB y 21 tam TCB

    t_list * data_segmentos = list_create(); // una lista de t_data_segmento

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
    
    
    return true;
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
