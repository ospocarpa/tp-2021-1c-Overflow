#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "log_utils.h"
#include <string.h>
#include "segmentacion_pura.h"
#include "paginacion.h"

void iniciar_memoria_principal(int tam_memoria);
void liberar_memoria_principal();
void iniciar_memoria_virtual(int tam_memoria);
void liberar_memoria_virtual();

void cargar_informacion_PCB_a_MP(t_PCB pcb,int base);
void cargar_informacion_tareas_a_MP(char *tareas,int base);
void cargar_data_segmento(t_data_segmento * data_segmento, int base);
void set_tripulante(t_TCB tcb, int patotaid);
t_TCB get_TCB(int patota_id, int tripulante_id);
char* get_tareas(int patota_id);

t_PCB leer_info_PCB(int base);
t_TCB leer_info_TCB(int base);
t_TCB leer_info_TCB_generico(void* stream);
void* get_stream_tcb(t_TCB tcb);

void mostrar_tcb(t_TCB tcb_encontrado);
void method_sigusr1();

//Acciones del servidor
bool iniciar_patota(t_iniciar_patota init_patota);

#endif