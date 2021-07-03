#ifndef TAD_MI_RAM_HQ_H
#define TAD_MI_RAM_HQ_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <netdb.h>

typedef struct 
{
    uint32_t pid;
    uint32_t tareas;//direccion logica
}t_PCB;

typedef struct 
{
    uint32_t tid;
    char estado;
    int posx;
    int posy;
    uint32_t prox_tarea;
    uint32_t puntero_pcb;
}t_TCB;

typedef struct 
{
    int base;
    int desplazamiento;
} t_hueco;

#endif