#ifndef DISCORDIADOR_H
#define DISCORDIADOR_H

#include <stdio.h>
#include <stdbool.h>
#include "log_utils.h"
#include "../include/config_utils.h"
#include <commons/config.h>
#include <commons/collections/list.h>
#include "socket_client.h"
#include <sys/socket.h>
#include <TAD.h>

#include "shared_utils.h"
#include "RecepcionMensajes.h"
#include <consola.h>
#include <semaphore.h>
#include "tests.h"
#include "dispatcher.h"
#include "global_discordiador.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define PATH_CONFIG "./cfg/discordiador.config"

t_log *logger;
t_config_discordiador *config;

//por ahora booleano para el sabotaje
bool hay_sabotaje = false;
bool planificacion_activa = false;
int numeroTripulante = 2;
int numeroPatota = 1;
int cantidad_activos = 0;

t_sabotaje* sabotaje_a_resolver;

//Semáforos
pthread_mutex_t SEM_PAUSAR_PLANIFICACION;
sem_t listos;
sem_t bloqueados;
sem_t grado_multiprocesamiento;
sem_t activados; //Incluye a los tripulantes que se encuentran en exec, ready y bloqueado por I/O
pthread_mutex_t MXTRIPULANTE;
pthread_mutex_t mutex_bloqueado;

//Listas de estados
t_list *lista_tripulantes; //[Tripulante]
//t_list *lista_NEW;
t_list *lista_EXEC;
t_list *lista_BLOCKIO;
t_list *lista_BLOCKEMERGENCIA;
t_list *lista_EXIT;

// pthread_mutex_t MXMENSAJE;

void iniciar_servidor_main();
void ejecutar_operacion(int cliente_fd);
void inicializacion_recursos();

#endif