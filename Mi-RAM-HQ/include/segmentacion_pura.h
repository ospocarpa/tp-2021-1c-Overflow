#ifndef SEGMENTACION_PURA_H
#define SEGMENTACION_PURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "memoria.h"



/* ****************** */
void liberar_tabla_huecos();
void set_algoritmo_ubicacion(char * algoritmo);
void iniciar_lista_tabla_segmento();
void iniciar_tabla_huecos(int tam_memoria);
bool se_puede_escribir(int tam_info);
void agregar_tabla_de_segmento(t_tabla_segmentos * tabla);
void liberar_lista_de_tablas_segmentos();
t_TCB get_TCB_segmentacion_pura(int patota_id, int tripulante_id);

/* --------FUNCIONES QUE SE UTILIZAN EN LOS TEST ----- */
int cantidad_de_tablas_de_segmento_test();
int cantidad_huecos_test();
t_tabla_segmentos * get_tabla_segmento_segun_indice_test(int indice);

#endif