/*
 * crear_pedido.h
 *
 *  Created on: 25 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Crear Pedido"
 * Para el output. No Tiene Input
 */


#ifndef CREAR_PEDIDO_H
#define CREAR_PEDIDO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"



t_paquete* serializar_O_CREAR_PEDIDO(t_pedidoID* datos);
t_pedidoID* deserializar_O_CREAR_PEDIDO(t_paquete* paquete);

#endif /* CREAR_PEDIDO_H */