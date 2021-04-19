/*
 * seleccionar_restaurante.h
 *
 *  Created on: 22 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Seleccionar Restaurante"
 */


#ifndef CONSULTAR_RESTAURANTES_H
#define CONSULTAR_RESTAURANTES_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TAD_Restaurante.h"



typedef struct
	{
        uint32_t cantNombreDeRes;
		t_list* t_nombreDeRes;			// list [t_nombreDeRes*]
    } t_O_CONSULTAR_RESTAURANTE;


t_paquete* serializar_O_CONSULTAR_RESTAURANTE(t_O_CONSULTAR_RESTAURANTE* datos);
t_O_CONSULTAR_RESTAURANTE* deserializar_O_CONSULTAR_RESTAURANTE(t_paquete* paquete);

#endif /* CONSULTAR_RESTAURANTES_H */