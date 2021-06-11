#ifndef DISCORDIADOR_H
#define DISCORDIADOR_H

#include <stdio.h>
#include <stdbool.h>
#include "log_utils.h"
#include "config_utils.h"
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

t_log *logger;
t_config_discordiador *config;
// pthread_mutex_t MXMENSAJE;
int numeroTripulante = 0;
int numeroPatota = 0;
pthread_mutex_t SEM_PAUSAR_PLANIFICACION;
sem_t listos;
sem_t grado_multiprocesamiento;
//t_list *lista_NEW;
t_list *lista_tripulantes;
t_list *lista_EXIT;
//_Bool planificacion_activa = false;

void iniciar_servidor_main();
void ejecutar_operacion(int cliente_fd);

#define PATH_CONFIG "cfg/discordiador.config"

#endif