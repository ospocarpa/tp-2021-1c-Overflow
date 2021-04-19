#ifndef CONEXION_MODULOS_H
#define CONEXION_MODULOS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "RecepcionMensajes.h"
#include "shared_utils.h"
#include "config_utils.h"
#include "server_utils.h"
#include "util.h"
#include "Cliente_starter.h"



int conectarOtroModulo(t_config_cliente * config, t_log* logger);
void *recibirNotificaciones(void* args);
/*
int conectarApp(t_config_cliente * config, t_log* logger);
int conectarComanda(t_config_cliente * config, t_log* logger);
int conectarRestaurante(t_config_cliente * config, t_log* logger);
int conectarSindicato(t_config_cliente * config, t_log* logger);
 */
#endif
