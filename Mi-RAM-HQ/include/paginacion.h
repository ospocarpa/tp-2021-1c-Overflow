#ifndef PAGINACION
#define PAGINACION

#include <stdio.h>
#include <stdlib.h>
#include <commons/string.h> 
#include <commons/bitarray.h>
#include <commons/collections/list.h>

    t_list * list_tablas_paginacion;        //[t_table_page]
    t_list * tablas_pag_libre;         //?
    t_bitarray* bitmap_memoria_real;
    t_bitarray* bitmap_memoria_virtual;

    //Estructura
    typedef struct{
        t_list* pages;                      //[t_page]
        int cant_caracteres_tarea;
        int cant_tripulantes;
        int patota_id;                      //Es el conjunto de bloques}
    } t_table_page;

    typedef struct{
        int page;
        int frame;
        bool presencia;
        bool uso;
        char* timestamp;
    } t_page;

    typedef struct{
        void* stream;
        int tamanio;
        int cantTripulantes;
    } t_page_auxiliar;

void dump_paginacion();

#endif