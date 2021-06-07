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
#include <commons/process.h>

extern int numeroTripulante;
extern int numeroPatota;
pthread_mutex_t MXTRIPULANTE;
pthread_mutex_t SEM_PAUSAR_PLANIFICACION;

void crearHilosTripulantes(Patota *);
void hilo_tripulante(t_tripulante *);

void cargarTripulante(t_iniciar_patota *, char **, int);

#endif
