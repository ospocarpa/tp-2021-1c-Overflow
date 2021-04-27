#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "config_utils.h"
//#include "TAD.h"
//#include "TAD_Restaurante.h"
//#include "handshake.h"
//#include "Restaurante_Starter.h"
//#include "RecepcionMensajes.h"
#include <commons/collections/queue.h>
#include <semaphore.h>

t_config_template* config;
t_log* logger;


void ejecutar_operacion(int cliente_fd);
void init_message();

#endif