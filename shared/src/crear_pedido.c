#include "crear_pedido.h"


t_paquete* serializar_O_CREAR_PEDIDO(t_pedidoID* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = sizeof(uint32_t);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

	memcpy(stream + offset, &datos->pedidoID, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = O_CREAR_PEDIDO;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
	return paquete;
}

t_pedidoID* deserializar_O_CREAR_PEDIDO(t_paquete* paquete){
    t_pedidoID* respuesta = malloc(sizeof(t_pedidoID));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->pedidoID, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

    return respuesta;
}

t_paquete* serializar_I_CREAR_PEDIDO(){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size =1;
    void* stream = malloc(new_buffer->size);
    new_buffer->stream = stream;
    paquete->buffer = new_buffer;
    paquete->codigo_operacion = I_CREAR_PEDIDO;
    paquete->from_client = false;
}