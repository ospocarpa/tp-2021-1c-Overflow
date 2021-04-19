#include "consultar_pedido.h"

t_paquete* serializar_input_Consultar_Pedido(t_pedidoID* datos){
    t_paquete* paquete = serializar_pedido_ID(datos,I_CONSULTAR_PEDIDO);
    paquete->codigo_operacion = I_CONSULTAR_PEDIDO;
	return paquete;
}

t_pedidoID* deserializar_input_Consultar_Pedido(t_paquete* paquete){
    t_pedidoID* respuesta = deserializar_pedido_ID(paquete);
    return respuesta;
}

t_paquete* serializar_output_Consultar_Pedido(t_pedido* datos){
    t_paquete* paquete = serializar_pedido(datos,O_CONSULTAR_PEDIDO);
    paquete->codigo_operacion = O_CONSULTAR_PEDIDO;
	return paquete;
}

t_pedido* deserializar_output_Consultar_Pedido(t_paquete* paquete){
    t_pedido* respuesta = deserializar_pedido(paquete);
    return respuesta;
}