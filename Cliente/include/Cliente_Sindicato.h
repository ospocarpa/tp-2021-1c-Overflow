#ifndef CLIENTE_SINDICATO_H
#define CLIENTE_SINDICATO_H

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
#include "terminar_pedido.h"
#include "obtener_receta.h"


//Terminar Pedido(SINDICATO)
void terminarPedido();
void obtenerReceta();


#endif