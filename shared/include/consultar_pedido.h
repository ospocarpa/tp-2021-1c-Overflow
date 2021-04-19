/*
 * crear_pedido.h
 *
 *  Created on: 25 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Consultar Pedido"
 * Para el output e input
 */
/*
 * consultar_pedido.h
 *
 * Description: Serializador y Deserializador para usar con el comando "Consultar pedido"
 * Para el input y el output 
 */

#ifndef CONSULTAR_PEDIDO_H
#define CONSULTAR_PEDIDO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"
#include "serializadorAnexo.h"
#include "deserializadorAnexo.h"

    t_paquete* serializar_input_Consultar_Pedido(t_pedidoID* datos);
    t_pedidoID* deserializar_input_Consultar_Pedido(t_paquete* paquete);

    t_paquete* serializar_output_Consultar_Pedido(t_pedido* datos);
    t_pedido* deserializar_output_Consultar_Pedido(t_paquete* paquete);

#endif /* CONSULTAR_PEDIDO_H */