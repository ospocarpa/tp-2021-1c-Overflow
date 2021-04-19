#ifndef CLIENTE_RESTAURANTE_H
#define CLIENTE_RESTAURANTE_H


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "shared_utils.h"
#include "config_utils.h"
#include "server_utils.h"
#include "util.h"
#include "Cliente_starter.h"
#include "consultar_restaurantes.h"
#include "seleccionar_restaurante.h"

void consultarRestaurante();


//Obtener Restaurante
void obtenerRestaurante();


#endif