#include "seleccionar_restaurante.h"



t_paquete* serializar_I_SELECCIONAR_RESTAURANTE(t_I_SELECCIONAR_RESTAURANTE* datos){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size = sizeof(uint32_t)*2 //longitud del cliente_length y restaurante_length
                        + strlen(datos->cliente)
                        + strlen(datos->restaurante)
                        ;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento
    memcpy(stream + offset, &datos->cliente_length, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(stream + offset, datos->cliente, strlen(datos->cliente));
    offset += datos->cliente_length;
    memcpy(stream + offset, &datos->restaurante_length, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(stream + offset, datos->restaurante, strlen(datos->restaurante) + 1);
    
    new_buffer->stream = stream;
    paquete->codigo_operacion = I_SELECCIONAR_RESTAURANTE;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
	return paquete;
}


t_I_SELECCIONAR_RESTAURANTE* deserializar_I_SELECCIONAR_RESTAURANTE(t_paquete* paquete){
    t_I_SELECCIONAR_RESTAURANTE* I_SELECCIONAR_RESTAURANTE = malloc(sizeof(t_I_SELECCIONAR_RESTAURANTE));
    t_buffer* buffer = paquete->buffer;

    //tomo el largo del nombre del cliente, asigno en memoria y tomo ese largo para el cliente
    
    memcpy(&(I_SELECCIONAR_RESTAURANTE->cliente_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	I_SELECCIONAR_RESTAURANTE->cliente = malloc(I_SELECCIONAR_RESTAURANTE->cliente_length);
	memcpy(I_SELECCIONAR_RESTAURANTE->cliente, buffer->stream, I_SELECCIONAR_RESTAURANTE->cliente_length);
	I_SELECCIONAR_RESTAURANTE->cliente[I_SELECCIONAR_RESTAURANTE->cliente_length] = '\0';
    buffer->stream += I_SELECCIONAR_RESTAURANTE->cliente_length;
    

    //tomo el largo del nombre del restaurante, asigno en memoria y tomo ese largo para el restaurante
    memcpy(&(I_SELECCIONAR_RESTAURANTE->restaurante_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    
	I_SELECCIONAR_RESTAURANTE->restaurante = malloc(I_SELECCIONAR_RESTAURANTE->restaurante_length);
	memcpy(I_SELECCIONAR_RESTAURANTE->restaurante, buffer->stream, I_SELECCIONAR_RESTAURANTE->restaurante_length);
    I_SELECCIONAR_RESTAURANTE->restaurante[I_SELECCIONAR_RESTAURANTE->restaurante_length] = '\0';
    //buffer->stream += I_SELECCIONAR_RESTAURANTE->restaurante_length;


    return I_SELECCIONAR_RESTAURANTE;
}