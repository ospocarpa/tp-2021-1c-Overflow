// #ifndef RECEPCION_MENSAJES_H
// #define RECEPCION_MENSAJES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <commons/collections/list.h>
#include "config_utils.h"
#include "server_utils.h"
#include "shared_utils.h"
#include "TAD.h"

void *recepcionMensaje(t_package paquete, int cliente_fd, t_log *logger);

// #endif
