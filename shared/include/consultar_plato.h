/*
 * seleccionar_restaurante.h
 *
 *  Created on: 2 octubre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Consultar Plato"
 */


#ifndef CONSULTAR_PLATO_H
#define CONSULTAR_PLATO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TAD_Restaurante.h"

typedef struct
{
	uint32_t cantPlatos;
	t_list *platos; // list [t_plato]
} t_platos;


t_paquete* serializar_I_CONSULTAR_PLATOS(t_nombreDeRes* datos);
t_nombreDeRes* deserializar_I_CONSULTAR_PLATOS(t_paquete* paquete);

t_paquete* serializar_O_CONSULTAR_PLATOS(t_platos *datos);
t_platos* deserializar_O_CONSULTAR_PLATOS(t_paquete* paquete);

#endif /* CONSULTAR_PLATOH */