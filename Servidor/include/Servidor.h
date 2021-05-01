#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "config_utils.h"
#include <semaphore.h>

t_log* logger;


void ejecutar_operacion(int cliente_fd);
void init_message();

#endif