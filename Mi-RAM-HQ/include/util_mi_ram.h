#ifndef UTIL_MI_RAM_H
#define UTIL_MI_RAM_H

#include <stdlib.h>
#include <stdio.h>
#include "TAD.h"
#include "tad_mi_ram_hq.h"
#include <commons/string.h> 
#include <commons/collections/list.h>

t_info_tarea get_tarea(char* lista_tareas,int n_tarea);
char map_estado(status_tripulante status);

#endif