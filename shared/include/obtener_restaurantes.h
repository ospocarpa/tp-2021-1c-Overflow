/*
 * seleccionar_restaurante.h
 *
 *  Created on: 25 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Obtener Restaurante"
 * Para el input. el output ya esta armado en TAD.h, serializador y deserializador
 */


#ifndef OBTENER_RESTAURANTES_H
#define OBTENER_RESTAURANTES_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TAD_Restaurante.h"




t_paquete* serializar_I_OBTENER_RESTAURANTE(t_nombreDeRes* datos);
t_nombreDeRes* deserializar_I_OBTENER_RESTAURANTE(t_paquete* paquete);

#endif /* OBTENER_RESTAURANTES_H */