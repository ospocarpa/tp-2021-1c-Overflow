#include "guardar_pedido.h"

t_paquete* serializar_I_GUARDAR_PEDIDO(t_I_GUARDAR_PEDIDO* datos){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size = sizeof(uint32_t)*2 //longitud del idPedido y restaurante_length
                        + datos->restaurante_length;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento
  
    memcpy(stream + offset, &datos->idPedido, sizeof(uint32_t));
    offset += sizeof(uint32_t);  
    memcpy(stream + offset, &datos->restaurante_length, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(stream + offset, datos->restaurante, datos->restaurante_length);

    new_buffer->stream = stream;
    paquete->codigo_operacion = I_GUARDAR_PEDIDO;
    paquete->buffer = new_buffer;
    paquete->from_client = false;

  	return paquete;
}


t_I_GUARDAR_PEDIDO* deserializar_I_GUARDAR_PEDIDO(t_paquete* paquete){
    t_I_GUARDAR_PEDIDO* I_GUARDAR_PEDIDO = malloc(sizeof(t_I_GUARDAR_PEDIDO));
    t_buffer* buffer = paquete->buffer;

    //tomo el largo del nombre del restaurante, asigno en memoria y tomo ese largo para el restaurante
    memcpy(&(I_GUARDAR_PEDIDO->idPedido), buffer->stream, sizeof(uint32_t));
	  buffer->stream += sizeof(uint32_t);
  
    memcpy(&(I_GUARDAR_PEDIDO->restaurante_length), buffer->stream, sizeof(uint32_t));
	  buffer->stream += sizeof(uint32_t);
    
  	I_GUARDAR_PEDIDO->restaurante = malloc(I_GUARDAR_PEDIDO->restaurante_length);
	  memcpy((I_GUARDAR_PEDIDO->restaurante), buffer->stream, I_GUARDAR_PEDIDO->restaurante_length);
    I_GUARDAR_PEDIDO->restaurante[I_GUARDAR_PEDIDO->restaurante_length] = '\0';

    free(buffer);

    return I_GUARDAR_PEDIDO;
}