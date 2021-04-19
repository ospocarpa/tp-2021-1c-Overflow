/*
 * seleccionar_restaurante.h
 *
 *  Created on: 22 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Seleccionar Restaurante"
 */


#ifndef GUARDAR_PEDIDO_H
#define GUARDAR_PEDIDO_H

#include "TAD.h"
#include <stdlib.h>
#include <string.h>

    typedef struct
	{
        uint32_t idPedido;
		char* restaurante;
        uint32_t restaurante_length;
	} t_I_GUARDAR_PEDIDO;  // GP es por GuardarPedido


	t_paquete* serializar_I_GUARDAR_PEDIDO(t_I_GUARDAR_PEDIDO* datos);
    t_I_GUARDAR_PEDIDO* deserializar_I_GUARDAR_PEDIDO(t_paquete* paquete);

#endif /* GUARDAR_PEDIDO_H */