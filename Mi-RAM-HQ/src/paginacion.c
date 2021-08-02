#include "paginacion.h"

void iniciar_tabla_paginacion(){
    list_tablas_paginacion = list_create();
}

void dump_paginacion(){
    char *format = "%d/%m/%y %H:%M:%S";
    char *timestamp = temporal_get_string_time(format);
    
    char* contenido = string_new();
    string_append_with_format(&contenido, "Dump: %s\n", timestamp);
    
    /*int cant_tablas = list_size(list_tablas_paginacion);
    int proceso_id;
    for(int c=0; c<cant_tablas; c++){
        //t_tabla_segmentos* tabla_segmento = get_tabla_segmento_segun_indice_test(c);
        t_list* segmentos_de_tabla = tabla_segmento->segmentos;
        proceso_id = tabla_segmento->pid;

        for(int d=0; d<list_size(segmentos_de_tabla);d++){
            t_segmento* segmento = list_get(segmentos_global, d);
            string_append_with_format(&contenido, "Proceso: %d Segmento: %d Inicio: %d Tamaño: %d\n", proceso_id, segmento->id, segmento->base, segmento->desplazamiento);
        }
    }
    //TODO: pasar a hexadecimal
    
    printf("%s\n", contenido);*/
}