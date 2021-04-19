#include "obtener_pedido.h"


t_paquete* serializar_I_OBTENER_PEDIDO(t_pedidoID_With_Restaurant* datos){
    t_paquete* paquete = serializar_pedido_ID_With_Restaurant(datos,I_OBTENER_PEDIDO);
	paquete->codigo_operacion = I_OBTENER_PEDIDO;
    paquete->from_client = false;
	return paquete;
}

t_pedidoID_With_Restaurant* deserializar_I_OBTENER_PEDIDO(t_paquete* paquete){
    t_pedidoID_With_Restaurant* respuesta = deserializar_pedido_ID_With_Restaurant(paquete);
    return respuesta;
}

t_paquete* serializar_output_pedido(t_pedido* datos){
    t_paquete* paquete = serializar_pedido(datos,O_OBTENER_PEDIDO);
    paquete->codigo_operacion = O_OBTENER_PEDIDO;
    paquete->from_client = false;
	return paquete;
}

t_pedido* deserializar_output_pedido(t_paquete* paquete){
    t_pedido* respuesta = deserializar_pedido(paquete);
    return respuesta;
}