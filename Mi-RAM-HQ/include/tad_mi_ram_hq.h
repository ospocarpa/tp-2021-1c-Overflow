#ifndef TAD_MI_RAM_HQ_H
#define TAD_MI_RAM_HQ_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <netdb.h>

typedef enum
{
    TAREAS,
    PCB,
    TCB
} type_data_seg;

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
} t_TCB;

typedef struct 
{
    int base;
    int desplazamiento;
} t_hueco;

typedef struct 
{
    uint32_t id;
    int base;
    int desplazamiento;
} t_segmento;

typedef struct 
{
    uint32_t pid;
    t_list * segmentos;//lista de t_segmento
}t_tabla_segmentos;

typedef struct 
{
    void * data;
    int tam_data;
    type_data_seg tipo;
}t_data_segmento;

//--------------------- Paginacion ----------------------
	

typedef struct {
    char *pages;
    int cantCaracteresTarea;
	int cant_tripulantes;
	int patotaid;
}t_lista_paginas;

typedef struct {
	int page;
	int frame;
    bool presencia; 	//Con SWAP
    bool uso;  		//Con CLOCK
    char* timestamp; 	//LRU
}t_page;


typedef struct {		// Usemos otro struct
    void* stream;
    int tam;
    int cantTripulantes;
}t_segmentos_paginacion;

#endif