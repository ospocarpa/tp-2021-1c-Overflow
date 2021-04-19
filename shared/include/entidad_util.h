#ifndef ENTIDAD_UTIL_H
#define ENTIDAD_UTIL_H

#include "TAD.h"
#include <commons/collections/dictionary.h>
#include <stdlib.h>
#include <string.h>

    void mostrar_platos(t_list *platos, int cant_platos, t_log* logger);
	void mostrar_restaurante(t_restaurante* restaurante, t_log* logger);
    void mostrar_receta(t_receta* receta, t_log* logger);
    void mostrar_pedido(t_pedido* pedido, t_log* logger);

    t_receta* receta_default();
    t_restaurante* restaurante_default();
    t_pedido* pedido_default();
    t_pedido* get_new_pedido();
    char* get_op_code(int op_code);

#endif /* ENTIDAD_UTIL_H */