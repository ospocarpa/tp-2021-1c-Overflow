#ifndef SEGMENTACION_PURA_H
#define SEGMENTACION_PURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"



/* ****************** */
void liberar_tabla_huecos();
void set_algoritmo_ubicacion(char * algoritmo);
void iniciar_lista_tabla_segmento();
void iniciar_tabla_huecos(int tam_memoria);

#endif