/*
 * obtener_pedido.h
 *
 *  Created on: 27 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Obtener Receta"
 * Recibe: Nombre del plato
 * Retorna: Receta
 */


#ifndef OBTENER_RECETA_H
#define OBTENER_RECETA_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"

    typedef struct
	{
		char* plato;
        uint32_t plato_length;
	} t_I_OBTENER_RECETA; 

t_paquete* serializar_I_OBTENER_RECETA(t_I_OBTENER_RECETA* datos);
t_I_OBTENER_RECETA* deserializar_I_OBTENER_RECETA(t_paquete* paquete);

#endif /* OBTENER_RECETA_H */