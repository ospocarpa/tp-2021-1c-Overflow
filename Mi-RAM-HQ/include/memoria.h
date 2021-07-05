#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "log_utils.h"

void iniciar_memoria_principal(int tam_memoria);
void liberar_memoria_principal();


void cargar_informacion_PCB_a_MP(t_PCB pcb,int base);
void cargar_informacion_TCB_a_MP(t_TCB tcb,int base);

#endif