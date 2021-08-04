#ifndef SEGMENTACION_PURA_H
#define SEGMENTACION_PURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "memoria.h"
#include "TAD.h"

extern void * memoria_principal;

/* ****************** */
void liberar_tabla_huecos();
void set_algoritmo_ubicacion(char * algoritmo);
void iniciar_lista_tabla_segmento();
void iniciar_tabla_huecos(int tam_memoria);
bool se_puede_escribir(int tam_info);
void agregar_tabla_de_segmento(t_tabla_segmentos * tabla);
void liberar_lista_de_tablas_segmentos();
t_TCB get_TCB_segmentacion_pura(int patota_id, int tripulante_id);
t_list* get_todos_los_segmentos();
void compactacion();
void mover_segmento(t_segmento *segmento, int base_pivote);
char* get_tareas_segmentacion(int patota_id);
void set_tripulante_por_segmentacion(t_TCB tcb, int patota_id);
void cargar_informacion_TCB_a_MP(t_TCB tcb,int base);
char* dump_segmentacion_pura();
void eliminar_segmento_tripulante(t_expulsar_tripulante tripulante);

/* -------- ACCESO A LA MEMORIA ----- */
char * leer_info_tareas(int base,int tam);

/* -------- FUNCIONES QUE SE UTILIZAN EN LOS TEST ----- */
int cantidad_de_tablas_de_segmento_test();
int cantidad_huecos_test();
t_tabla_segmentos * get_tabla_segmento_segun_indice_test(int indice);

#endif