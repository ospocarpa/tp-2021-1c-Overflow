#include "guardar_plato.h"


/*
	typedef struct
	{
		uint32_t pedidoID;
		uint32_t nombreDeRes_length;
		char* nombreDeRes;
		uint32_t plato_length;
		char* plato;
		uint32_t cantidad;
	} t_I_GUARDAR_PLATO;
*/

t_paquete* serializar_I_GUARDAR_PLATO(t_I_GUARDAR_PLATO* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = datos->nombreDeRes_length +1 + datos->plato_length +1 + sizeof(uint32_t)*4;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

	memcpy(stream + offset, &datos->pedidoID, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(stream + offset, &datos->nombreDeRes_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->nombreDeRes, datos->nombreDeRes_length+1 );
	offset += datos->nombreDeRes_length+1 ;

	memcpy(stream + offset, &datos->plato_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->plato, datos->plato_length+1 );
	offset += datos->plato_length+1 ;

	memcpy(stream + offset, &datos->cantidad, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = I_GUARDAR_PLATO;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}

t_I_GUARDAR_PLATO* deserializar_I_GUARDAR_PLATO(t_paquete* paquete){
    t_I_GUARDAR_PLATO* respuesta = malloc(sizeof(t_I_GUARDAR_PLATO));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->pedidoID, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

    memcpy(&respuesta->nombreDeRes_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	respuesta->nombreDeRes = malloc(respuesta->nombreDeRes_length+1 );
	memcpy(respuesta->nombreDeRes, buffer->stream, respuesta->nombreDeRes_length+1 );
	buffer->stream += respuesta->nombreDeRes_length+1 ;
    memcpy(&respuesta->plato_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	respuesta->plato = malloc(respuesta->plato_length+1 );
	memcpy(respuesta->plato, buffer->stream, respuesta->plato_length+1 );
	buffer->stream += respuesta->plato_length+1 ;

    memcpy(&respuesta->cantidad, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	free(buffer);
    return respuesta;
}
