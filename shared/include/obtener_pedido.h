/*
 * obtener_pedido.h
 *
 *  Created on: 27 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Obtener Pedido"
 * Recibe [Restaurante, ID de pedido]
 * Retorna: {estado, [{comida1, cantTotal1, cantLista1}, {comida2, cantTotal2, cantLista2}, ...]}
 */


#ifndef OBTENER_PEDIDO_H
#define OBTENER_PEDIDO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"
#include "serializadorAnexo.h"
#include "deserializadorAnexo.h"

t_paquete* serializar_I_OBTENER_PEDIDO(t_pedidoID_With_Restaurant* datos);
t_pedidoID_With_Restaurant* deserializar_I_OBTENER_PEDIDO(t_paquete* paquete);


t_paquete* serializar_output_pedido(t_pedido* datos);
t_pedido* deserializar_output_pedido(t_paquete* paquete);

#endif /* OBTENER_PEDIDO_H */