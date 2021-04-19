#include "obtener_receta.h"

t_paquete* serializar_I_OBTENER_RECETA(t_I_OBTENER_RECETA* datos){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = datos->plato_length + sizeof(uint32_t);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

	memcpy(stream + offset, &datos->plato_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, datos->plato, datos->plato_length);
	offset += datos->plato_length;

    new_buffer->stream = stream;
    paquete->codigo_operacion = I_OBTENER_RECETA;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}

t_I_OBTENER_RECETA* deserializar_I_OBTENER_RECETA(t_paquete* paquete){
	t_I_OBTENER_RECETA* respuesta = malloc(sizeof(t_I_OBTENER_RECETA));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->plato_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->plato = malloc(respuesta->plato_length);
	memcpy(respuesta->plato, buffer->stream, respuesta->plato_length);
	respuesta->plato[respuesta->plato_length] = '\0';

	free(buffer);
    return respuesta;
}
