#ifndef RECEPCION_MENSAJES_H
#define RECEPCION_MENSAJES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include "anadir_plato.h"
#include "config_utils.h"
#include "consultar_pedido.h"
#include "consultar_plato.h"
#include "consultar_restaurantes.h"
#include "crear_pedido.h"
#include "desearilizador.h"
#include "deserializadorAnexo.h"
#include "finalizar_pedido.h"
#include "guardar_pedido.h"
#include "guardar_plato.h"
#include "handshake.h"
#include "obtener_pedido.h"
#include "obtener_restaurantes.h"
#include "plato_listo.h"
#include "seleccionar_restaurante.h"
#include "serializadorAnexo.h"
#include "serializador.h"
#include "server_utils.h"
#include "shared_utils.h"
#include "TADAnexo.h"
#include "TAD.h"
#include "TAD_Restaurante.h"
#include "terminar_pedido.h"
#include "entidad_util.h"
#include "util.h"

int conexionCliente;
extern bool tengoHandshake;
extern t_handshake_input *handshake;
void *recepcionMensaje(t_paquete *paquete, t_log *logger);

#endif
