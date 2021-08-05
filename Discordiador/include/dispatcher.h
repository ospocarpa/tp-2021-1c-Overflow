#ifndef DISPATCHER_H
#define DISPATCHER_H

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

extern t_list *lista_READY;
void init_dispatcher();
void init_bloqueados();
Tripulante *busqueda_algoritmo();
Tripulante *elegir_tripulante_bloqueado();

#endif