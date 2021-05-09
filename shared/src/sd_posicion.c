#include "../include/sd_posicion.h"

t_paquete* serializar_I_Posicion(Posicion* input){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = sizeof(uint32_t) * 2;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

	memcpy(stream + offset, &input->posx, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &input->posy, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = -1;
	paquete->buffer = new_buffer;
	return paquete;
}

Posicion* deserializar_I_Posicion(t_paquete* paquete){
	Posicion* respuesta = malloc(sizeof(Posicion));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->posx, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	memcpy(&respuesta->posy, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	free(buffer);
    return respuesta;
}
