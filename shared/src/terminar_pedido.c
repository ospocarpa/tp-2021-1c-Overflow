#include "terminar_pedido.h"

t_paquete* serializar_I_TERMINAR_PEDIDO(t_pedidoID_With_Restaurant* datos){
	t_paquete* paquete = serializar_pedido_ID_With_Restaurant(datos,I_TERMINAR_PEDIDO);
    paquete->codigo_operacion = I_TERMINAR_PEDIDO;
    paquete->from_client = false;
	return paquete;
}

t_pedidoID_With_Restaurant* deserializar_I_TERMINAR_PEDIDO(t_paquete* paquete){
    t_pedidoID_With_Restaurant* datos = deserializar_pedido_ID_With_Restaurant(paquete);
    return datos;
}