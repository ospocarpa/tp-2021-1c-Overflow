#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "log_utils.h"
#include <string.h>

void iniciar_memoria_principal(int tam_memoria);
void liberar_memoria_principal();
void liberar_tabla_huecos();
void set_algoritmo_ubicacion(char * algoritmo);


void cargar_informacion_PCB_a_MP(t_PCB pcb,int base);
void cargar_informacion_TCB_a_MP(t_TCB tcb,int base);
void cargar_informacion_tareas_a_MP(char *tareas,int base);

t_PCB leer_info_PCB(int base);
t_TCB leer_info_TCB(int base);
char * leer_info_tareas(int base,int tam);

#endif