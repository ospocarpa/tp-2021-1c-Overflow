// #ifndef RECEPCION_MENSAJES_H
// #define RECEPCION_MENSAJES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <commons/collections/list.h>
#include "config_utils.h"
#include "desearilizador.h"
#include "deserializadorAnexo.h"
#include "handshake.h"
#include "serializadorAnexo.h"
#include "serializador.h"
#include "server_utils.h"
#include "shared_utils.h"
#include "TADAnexo.h"
#include "TAD.h"
#include "Servidor.h"

// int conexionCliente;
// extern bool tengoHandshake;
// extern t_handshake_input *handshake;
void *recepcionMensaje(t_paquete *paquete, int cliente_fd, t_log *logger);

// #endif
