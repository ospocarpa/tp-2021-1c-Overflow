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
#include <math.h>
#include <ctype.h>
#include <consola.h>
#include <pthread.h>
#include <semaphore.h>
#include <commons/process.h>
#include "../include/TAD.h"
#include "../include/sd_informar_tarea_tripulante.h"    /*  */
#include "../include/sd_informar_posicion_tripulante.h" /*  */
#include "../include/server_utils.h"
#include "config_utils.h"
#include "sd_fcsk.h"
#include "sd_update_bitacora.h"
#include "global_discordiador.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

extern bool hay_sabotaje;
extern pthread_mutex_t MXTRIPULANTE;
extern pthread_mutex_t mutex_bloqueado;

extern int numeroTripulante;
extern int numeroPatota;
extern pthread_mutex_t SEM_PAUSAR_PLANIFICACION;
extern sem_t listos;
extern sem_t bloqueados;
extern sem_t grado_multiprocesamiento;
//extern t_list *lista_NEW;
extern t_list *lista_tripulantes; //Dentro van a estar los tripulantes en estado READY/EXEC/BLOCKED
extern t_list *lista_BLOCKIO;
extern t_list *lista_EXEC;
extern t_list *lista_BLOCKEMERGENCIA;
extern t_list *lista_EXIT;

extern int cantidad_activos;
extern t_config_discordiador *config;

extern t_sabotaje* sabotaje_a_resolver;

void crearHilosTripulantes(Patota *);
void leerConfighilo_tripulante(Tripulante *);

void cargarTripulante(t_iniciar_patota *, char **, int);
int mover_tripulante_a_tarea(Tripulante *);
void invocar_fsck();
void cambiar_estado(Tripulante *, status_tripulante);
Tripulante *buscar_el_mas_cercano(t_sabotaje *sabotaje);
void update_bitacora(int conexion_servidor, char *filename, char *contenido);
void chequear_sabotaje(Tripulante* tripulante);
void chequear_planificacion_activa(Tripulante* tripulante);
void desbloquear_tripulantes();
void inicio_sabotaje(t_sabotaje *sabotaje);
void chequear_activados();
void enviar_posicion_mi_ram(Tripulante *tripulante);

#endif
