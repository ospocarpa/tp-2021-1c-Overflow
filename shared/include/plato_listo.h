/*
 * plato_listo.h
 *
 *  Created on: 28 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Plato Listo"
 * Recibe [Restaurante, ID de pedido, Plato]
 * Retorna: OK/Fail (respuesta_bool)
 */


#ifndef PLATO_LISTO_H
#define PLATO_LISTO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"



t_paquete* serializar_I_PLATO_LISTO(t_I_PLATO_LISTO* datos);
t_I_PLATO_LISTO* deserializar_I_PLATO_LISTO(t_paquete* paquete);



#endif /* PLATO_LISTO_H */