/*
 * serializador.h
 *
 *  Created on: 14 may. 2020
 *      Author: utnso
 */

#ifndef SOCKETS_SERIALIZADOR_H_
#define SOCKETS_SERIALIZADOR_H_
#include "TAD.h"
#include <stdlib.h>
#include <string.h>

	t_paquete* serializar_restaurante(t_restaurante* restaurante);
	t_paquete* serializar_receta(t_receta* receta);
	t_paquete* serializar_respuesta_bool(t_respuesta_bool* respuesta);

#endif /* SOCKETS_SERIALIZADOR_H_ */
