#ifndef CLIENTE_MULTIMODULO_H
#define CLIENTE_MULTIMODULO_H

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
#include "consultar_plato.h"
#include "finalizar_pedido.h"
#include "guardar_pedido.h"
#include "anadir_plato.h"
#include "guardar_plato.h"
//Consultar Platos(APP,Restaurante,SINDICATO)
void consultarPlatos();

//Guardar Pedido(COMANDA,SINDICATO)
void guardarPedido();

//Guardar Plato(COMANDA, SINDICATO)
void guardarPlato();

//Crear Pedido(APP,Restaurante)
void crearPedido();

//Añadir Plato(APP,Restaurante)
void anadirPlato();

//Confirmar Pedido(APP,Restaurante,COMANDA,SINDICATO)
void confirmarPedido();

//Plato Listo(APP,COMANDA,SINDICATO)
void platoListo();

//Consultar Pedido(APP,Restaurante)
void consultarPedido();

//Obtener Pedido(COMANDA,SINDICATO)
void obtenerPedido();

//Finalizar Pedido(COMANDA,Cliente)
void finalizarPedido();




#endif