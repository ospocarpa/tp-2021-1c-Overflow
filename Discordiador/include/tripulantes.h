#ifndef TRIPULANTES_H
#define TRIPULANTES_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <TAD.h>
#include <sd_posicion.h>
#include <consola.h>
#include <tad_discordiador.h>
#include <commons/string.h>
#include <ctype.h>
#include <consola.h>
#include <pthread.h>
#include <semaphore.h>
#include <commons/process.h>
#include "../include/TAD.h"
#include "../include/sd_informar_tarea_tripulante.h"    /*  */
#include "../include/sd_informar_posicion_tripulante.h" /*  */
#include "../include/server_utils.h"

extern int numeroTripulante;
extern int numeroPatota;
pthread_mutex_t MXTRIPULANTE;
extern pthread_mutex_t SEM_PAUSAR_PLANIFICACION;
extern sem_t listos;
extern sem_t grado_multiprocesamiento;
//extern t_list *lista_NEW;
extern t_list *lista_tripulantes; //Dentro van a estar los tripulantes en estado READY/EXEC/BLOCKED
extern t_list *lista_READY;
extern t_list *lista_EXIT;

extern sem_t activados;

void crearHilosTripulantes(Patota *);
void leerConfighilo_tripulante(Tripulante *);

void cargarTripulante(t_iniciar_patota *, char **, int);
void mover_tripulante_a_tarea(Tripulante *, int);

#endif
