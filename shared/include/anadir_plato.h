/*
 * anadir_plato.h
 *
 *  Created on: 25 septiembre 2020
 *      Author: jloffredo
 * Description: Serializador y Deserializador para usar con el comando "Añadir Plato"
 * Para el output. No Tiene Input
 */


#ifndef ANADIR_PLATO_H
#define ANADIR_PLATO
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"



t_paquete* serializar_I_ANADIR_PLATO(t_I_ANADIR_PLATO* datos);
t_I_ANADIR_PLATO* deserializar_I_ANADIR_PLATO(t_paquete* paquete);

#endif /* ANADIR_PLATO */