/*
 * seleccionar_restaurante.h
 *
 *  Created on: 2 octubre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "COnfirmar pedido"
 */


#ifndef CONFIRMAR_PEDIDO_H
#define CONFIRMAR_PEDIDO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"
#include "TAD_Restaurante.h"


t_paquete* serializar_I_CONFIRMAR_PEDIDO(t_pedidoID_With_Restaurant* datos);
t_pedidoID_With_Restaurant* deserializar_CONFIRMAR_PEDIDO(t_paquete* paquete);

#endif /* CONSULTAR_PLATOH */