#include "obtener_restaurantes.h"


t_paquete* serializar_I_OBTENER_RESTAURANTE(t_nombreDeRes* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));


    new_buffer->size = datos->nombreDeRes_length +1 +  sizeof(uint32_t);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento


	memcpy(stream + offset, &datos->nombreDeRes_length , sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->nombreDeRes, datos->nombreDeRes_length +1);
	//offset += datos->nombreDeRes_length;
   
    
    new_buffer->stream = stream;
    paquete->codigo_operacion = I_OBTENER_RESTAURANTE;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
	return paquete;
}

t_nombreDeRes* deserializar_I_OBTENER_RESTAURANTE(t_paquete* paquete){
    t_nombreDeRes* respuesta = malloc(sizeof(t_nombreDeRes));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->nombreDeRes_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	respuesta->nombreDeRes = malloc(respuesta->nombreDeRes_length +1);
	memcpy(respuesta->nombreDeRes, buffer->stream, respuesta->nombreDeRes_length +1);
    buffer->stream += respuesta->nombreDeRes_length +1;
    free(buffer);

    return respuesta;
}