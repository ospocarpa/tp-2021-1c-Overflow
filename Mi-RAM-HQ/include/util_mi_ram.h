#ifndef UTIL_MI_RAM_H
#define UTIL_MI_RAM_H

#include <stdlib.h>
#include <stdio.h>
#include "TAD.h"
#include "tad_mi_ram_hq.h"
#include <commons/bitarray.h>
#include <commons/string.h> 
#include <commons/collections/list.h>


t_info_tarea get_tarea(char* lista_tareas,int n_tarea);
Posicion get_posicion_STR(char *posicion, int indice);
char map_estado(status_tripulante status);
bool esta_Llena_Memoria(t_bitarray* bitmap);
int get_timestamp_number(char* timestamp);
t_list* list_slice(t_list* lista, int inicio, int fin);
bool existe_memoria_disponible_paginacion(t_bitarray* bitmap_memoria_real, t_bitarray* bitmap_memoria_virtual, int tamanio_total);
bool existe_memoria_real_disponible(t_bitarray* bitmap_memoria_real);
char* get_label_presencia(bool presencia);
bool esta_Llena_Memoria(t_bitarray* bitmap);
int cantidad_disponible(t_bitarray* bitmap);
void limpiar_bit_map(t_bitarray* bitmap);

#endif