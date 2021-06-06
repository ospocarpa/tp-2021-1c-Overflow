#ifndef SERVER_H
#define SERVER_H

#include <global.h>
#include <pthread.h>
#include <string.h>
#include "log_utils.h"
#include "server_utils.h"
#include <stdlib.h>
#include "controller.h"

void *recepcionMensaje(t_paquete *paquete, int cliente_fd, t_log *logger);
void server_mongo_store_iniciar(int puerto);
void ejecutar_operacion(int cliente_fd);

#endif