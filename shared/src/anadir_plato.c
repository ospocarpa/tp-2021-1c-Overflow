#include "anadir_plato.h"


t_paquete* serializar_I_ANADIR_PLATO(t_I_ANADIR_PLATO* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    /*
    char* nombre;
    uint32_t nombre_length;
    uint32_t precio;
    */


    new_buffer->size = sizeof(uint32_t)*3+strlen(datos->plato->nombre);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

	memcpy(stream + offset, &datos->pedidoID, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    
	memcpy(stream + offset, &datos->plato->precio, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(stream + offset, &datos->plato->nombre_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, datos->plato->nombre, datos->plato->nombre_length);
	offset += datos->plato->nombre_length;

    new_buffer->stream = stream;
    paquete->codigo_operacion = I_ANADIR_PLATO;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
	return paquete;
}

t_I_ANADIR_PLATO* deserializar_I_ANADIR_PLATO(t_paquete* paquete){
    t_I_ANADIR_PLATO* respuesta = malloc(sizeof(t_I_ANADIR_PLATO));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->pedidoID, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

    t_plato* plato = malloc(sizeof(t_plato));
    
    memcpy(&plato->precio, buffer->stream, sizeof(uint32_t));
    buffer->stream += sizeof(uint32_t);

    memcpy(&plato->nombre_length, buffer->stream, sizeof(uint32_t));
    buffer->stream += sizeof(uint32_t);

    plato->nombre = malloc(plato->nombre_length);
    memcpy(plato->nombre, buffer->stream, plato->nombre_length);
    plato->nombre[plato->nombre_length]='\0';

    
    respuesta->plato = plato;

    return respuesta;
}