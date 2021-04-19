#include "confirmar_pedido.h"

t_paquete* serializar_I_CONFIRMAR_PEDIDO(t_pedidoID_With_Restaurant* datos){
    t_paquete* paquete = serializar_pedido_ID_With_Restaurant(datos, I_CONFIRMAR_PEDIDO);
    return paquete;
}

t_pedidoID_With_Restaurant* deserializar_CONFIRMAR_PEDIDO(t_paquete* paquete){
    t_pedidoID_With_Restaurant* datos = deserializar_pedido_ID_With_Restaurant(paquete);
    return datos;
}