/*
 * finalizar_pedido.h
 *
 *  Created on: 2 octubre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Finalizar Pedido"
 * Recibe [Restaurante, ID de pedido]
 */


#ifndef FINALIZAR_PEDIDO_H
#define FINALIZAR_PEDIDO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"
#include "serializadorAnexo.h"
#include "deserializadorAnexo.h"

t_paquete* serializar_I_FINALIZAR_PEDIDO(t_pedidoID_With_Restaurant* datos);
t_pedidoID_With_Restaurant* deserializar_I_FINALIZAR_PEDIDO(t_paquete* paquete);



#endif /* FINALIZAR_PEDIDO_H */