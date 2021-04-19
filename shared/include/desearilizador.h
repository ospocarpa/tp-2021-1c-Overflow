#ifndef DESEARILIZADOR_H_
#define DESEARILIZADOR_H_
#include "TAD.h"
#include <stdlib.h>
#include <string.h>

	t_restaurante* deserializar_restaurante(t_paquete* paquete);
	t_receta* deserializar_receta(t_paquete* paquete);
	t_respuesta_bool* deserializar_respuesta_bool(t_paquete* paquete);

#endif /* DESEARILIZADOR_H_ */
