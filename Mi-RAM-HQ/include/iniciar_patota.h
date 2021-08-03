#ifndef INICIAR_PATOTA_H
#define INICIAR_PATOTA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "memoria.h"
#include "TAD.h"
#include "segmentacion_pura.h"
#include "util_mi_ram.h"

extern t_bitarray* bitmap_memoria_real;
extern t_bitarray* bitmap_memoria_virtual;

bool iniciar_patota_segmentacion(t_iniciar_patota init_patota);
bool iniciar_patota_paginacion(t_iniciar_patota init_patota);
void* get_stream_pcb(t_iniciar_patota data);
void* get_stream_tcbs(t_iniciar_patota data);

#endif