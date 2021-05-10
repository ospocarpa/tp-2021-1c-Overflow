#include "../include/sd_tarea.h"

t_paquete* serializar_I_TAREA(Tarea* input){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = input->description_length + input->parametros_length + sizeof(uint32_t) * 6;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

	memcpy(stream + offset, &input->patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &input->description_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, input->description, input->description_length);
	offset += input->description_length;

	memcpy(stream + offset, &input->parametros_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, input->parametros, input->parametros_length);
	offset += input->parametros_length;

	memcpy(stream + offset, &input->tiempo, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &input->posicion->posx, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &input->posicion->posy, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = TAREA;
	paquete->buffer = new_buffer;
	return paquete;
}

Tarea* deserializar_I_TAREA(t_paquete* paquete){
	Tarea* respuesta = malloc(sizeof(Tarea));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->patota_id, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	memcpy(&respuesta->description_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->description = malloc(respuesta->description_length);
	memcpy(respuesta->description, buffer->stream, respuesta->description_length);
	respuesta->description[respuesta->description_length] = '\0';
	buffer->stream += respuesta->description_length;

	memcpy(&respuesta->parametros_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->parametros = malloc(respuesta->parametros_length);
	memcpy(respuesta->parametros, buffer->stream, respuesta->parametros_length);
	respuesta->parametros[respuesta->parametros_length] = '\0';
	buffer->stream += respuesta->parametros_length;

	memcpy(&respuesta->tiempo, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->posicion = malloc(sizeof(Posicion));
	memcpy(&respuesta->posicion->posx, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	memcpy(&respuesta->posicion->posy, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	free(buffer);
    return respuesta;
}

void mostrarTarea(Tarea* tarea){
    printf("Patota id: %d\n", tarea->patota_id);
    printf("Description: %s\n", tarea->description);
    printf("Description length: %d\n", tarea->description_length);
    printf("Parametros: %s\n", tarea->parametros);
    printf("Parametros length: %d\n", tarea->parametros_length);
    printf("Tiempo: %d\n", tarea->tiempo);
    printf("Posicion x: %d\n", tarea->posicion->posx);
    printf("Posicion y: %d\n", tarea->posicion->posy);
}