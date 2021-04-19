/*
 * guardar_plato.h
 *
 *  Created on: 6 octubre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Guardar Plato"
 * Recibe [Restaurante, ID de pedido, Plato, cantidad]
 * Retorna: OK/Fail (respuesta_bool)
 */


#ifndef GUARDAR_PLATO_H
#define GUARDAR_PLATO_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"



t_paquete* serializar_I_GUARDAR_PLATO(t_I_GUARDAR_PLATO* datos);
t_I_GUARDAR_PLATO* deserializar_I_GUARDAR_PLATO(t_paquete* paquete);



#endif /* GUARDAR_PLATO_H */