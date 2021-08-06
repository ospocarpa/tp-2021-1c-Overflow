#ifndef PAGINACION
#define PAGINACION

#include <stdio.h>
#include <stdlib.h>
#include <commons/bitarray.h>
#include <commons/string.h> 
#include <commons/bitarray.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "util_mi_ram.h"
#include "memoria.h"
#include "TAD.h"

void iniciar_tabla_paginacion();
int get_primer_bit_disponible(t_bitarray* bitarray);

extern void * memoria_principal;
    extern void * memoria_virtual;

    typedef struct{
        t_list* pages_filtradas;                      //[t_page]
        int offset;                      
    } t_paginacion_temporal;                          //Usado para el get y set de TCB en paginación

char* dump_paginacion();
void iniciar_tabla_paginacion();

//Crea un bitmap nuevo a partir de la cantidad de bits
t_bitarray* inicializar_bitmap(int cant_bits);

//Recibe una lista de tipo [t_page], y devuelve la información del conj. de páginas que recibe
void* dame_todo_el_stream(t_list* pages);
void* get_info(t_page* page);

//Realiza transferencia de memoria virtual a memoria real y lo devuelve
void* transferencia_de_swap_a_memoria_real(t_page* page, int frame);
void* get_info_virtual(t_page* page);

//Realiza transferencia de memoria real a memoria virtual
void transferencia_de_memoria_real_a_swap(t_page* page);

//Obtiene el primer bit disponible del bitmap
int get_first_frame_disponible(t_bitarray* bitmap);         //TODO
bool esta_memoria_real_llena();

//Algoritmo de reemplazo
t_page* obtener_pagina_candidato_por_algoritmo_de_reemplazo();
t_page* obtener_pagina_por_LRU();
t_page* obtener_pagina_por_Clock();
t_list* obtener_todas_las_paginas();
t_table_page* get_tabla_pagina_segun_indice(int indice);

//Getters
t_TCB get_TCB_paginacion(int patota_id, int tripulante_id);
char* get_tareas_paginacion(int patota_id);
t_paginacion_temporal get_paginacion_temporal(int patota_id, int tripulante_id);

//Setters
void set_TCB_paginacion(t_TCB tcb, int patota_id);

//Acceso al bitmap
void clean_indice_bitmap(t_bitarray* bitmap, int indice);
void set_indice_bitmap(t_bitarray* bitmap, int indice);

//Acceso a la memoria
void* leer_memoria_real(int marco, int desplazamiento);
void* leer_memoria_virtual(int marco, int desplazamiento);
void escribir_memoria_real(void *stream, int base, int desplazamiento);
void escribir_memoria_virtual(void *stream, int base, int desplazamiento);

//Últimos métodos
void expulsar_tripulante_paginacion(t_expulsar_tripulante tripulante);

#endif