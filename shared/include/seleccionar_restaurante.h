/*
 * seleccionar_restaurante.h
 *
 *  Created on: 22 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Seleccionar Restaurante"
 */


#ifndef SELECCIONAR_RESTAURANTE_H
#define SELECCIONAR_RESTAURANTE_H

#include "TAD.h"
#include <stdlib.h>
#include <string.h>

    typedef struct
	{
		char* cliente;
        uint32_t cliente_length;
		char* restaurante;
        uint32_t restaurante_length;
	} t_I_SELECCIONAR_RESTAURANTE;  // SR es por Seleccionar Restaurante


	t_paquete* serializar_I_SELECCIONAR_RESTAURANTE(t_I_SELECCIONAR_RESTAURANTE* datos);
    t_I_SELECCIONAR_RESTAURANTE* deserializar_I_SELECCIONAR_RESTAURANTE(t_paquete* paquete);

#endif /* SELECCIONAR_RESTAURANTE_H */