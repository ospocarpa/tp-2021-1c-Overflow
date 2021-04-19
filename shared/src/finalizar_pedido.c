#include "finalizar_pedido.h"


t_paquete* serializar_I_FINALIZAR_PEDIDO(t_pedidoID_With_Restaurant* datos){
    t_paquete* paquete = serializar_pedido_ID_With_Restaurant(datos,I_FINALIZAR_PEDIDO);
	paquete->codigo_operacion = I_FINALIZAR_PEDIDO;
	return paquete;
}

t_pedidoID_With_Restaurant* deserializar_I_FINALIZAR_PEDIDO(t_paquete* paquete){
    t_pedidoID_With_Restaurant* respuesta = deserializar_pedido_ID_With_Restaurant(paquete);
    return respuesta;
}
