#include "../include/sd_sabotaje.h"

t_paquete* serializar_I_SABOTAJE(Sabotaje* input){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

	new_buffer->size = input->mensaje_length + sizeof(uint32_t) * 3;
	void* stream = malloc(new_buffer->size);
	int offset = 0; // Desplazamiento


	memcpy(stream + offset, &input->mensaje_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, input->mensaje, input->mensaje_length);
	offset += input->mensaje_length;

	memcpy(stream + offset, &input->posicion->posx, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &input->posicion->posy, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = SABOTAJE;
	paquete->buffer = new_buffer;
	return paquete;
}

Sabotaje* deserializar_I_SABOTAJE(t_paquete* paquete){
	//preguntar lo de Sarea 
	Sabotaje* respuesta = malloc(sizeof(Sabotaje));
	t_buffer* buffer = paquete->buffer;

	memcpy(&respuesta->mensaje_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->mensaje = malloc(respuesta->mensaje_length);
	memcpy(respuesta->mensaje, buffer->stream, respuesta->mensaje_length);
	respuesta->mensaje[respuesta->mensaje_length] = '\0';
	buffer->stream += respuesta->mensaje_length;


	respuesta->posicion = malloc(sizeof(Posicion));
	memcpy(&respuesta->posicion->posx, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	memcpy(&respuesta->posicion->posy, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	free(buffer);
    return respuesta;
}

void mostrarSabotaje(Sabotaje* sabotaje){
    printf("Description: %s\n", sabotaje->mensaje);
    printf("Description length: %d\n", sabotaje->mensaje_length);
    printf("Posicion x: %d\n", sabotaje->posicion->posx);
    printf("Posicion y: %d\n", sabotaje->posicion->posy);
}
