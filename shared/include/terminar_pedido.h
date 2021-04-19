/*
 * seleccionar_restaurante.h
 *
 *  Created on: 22 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Terminar pedido"
 */


#ifndef TERMINAR_PEDIDO_H
#define TERMINAR_PEDIDO_H

#include "TAD.h"
#include <stdlib.h>
#include <string.h>
#include "serializadorAnexo.h"
#include "deserializadorAnexo.h"

	t_paquete* serializar_I_TERMINAR_PEDIDO(t_pedidoID_With_Restaurant* datos);
    t_pedidoID_With_Restaurant* deserializar_I_TERMINAR_PEDIDO(t_paquete* paquete);

#endif /* TERMINAR_PEDIDO_H */