#include "consultar_restaurantes.h"


t_paquete* serializar_O_CONSULTAR_RESTAURANTE(t_O_CONSULTAR_RESTAURANTE* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));
	
    
    uint32_t lengthNombres = 0;
	for(int c=0; c< datos->cantNombreDeRes; c++){
		t_nombreDeRes* t_nombreDeRes = list_get(datos->t_nombreDeRes, c);
		lengthNombres += t_nombreDeRes->nombreDeRes_length;
	}

    new_buffer->size = lengthNombres + datos->cantNombreDeRes * 2 * sizeof(uint32_t) + sizeof(uint32_t);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

    memcpy(stream + offset, &datos->cantNombreDeRes, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    
    for(int c=0; c< datos->cantNombreDeRes; c++){
		t_nombreDeRes* nombreDeRes = list_get(datos->t_nombreDeRes, c);
		memcpy(stream + offset, &nombreDeRes->nombreDeRes_length, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, nombreDeRes->nombreDeRes, nombreDeRes->nombreDeRes_length);
		offset += nombreDeRes->nombreDeRes_length;
	}
    
    new_buffer->stream = stream;
    paquete->codigo_operacion = O_CONSULTAR_RESTAURANTE;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}

t_O_CONSULTAR_RESTAURANTE* deserializar_O_CONSULTAR_RESTAURANTE(t_paquete* paquete){
    t_O_CONSULTAR_RESTAURANTE* respuesta = malloc(sizeof(t_O_CONSULTAR_RESTAURANTE));
    t_buffer* buffer = paquete->buffer;

    memcpy(&(respuesta->cantNombreDeRes), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

    respuesta->t_nombreDeRes = list_create();
	for(int c=0; c<respuesta->cantNombreDeRes; c++){
		t_nombreDeRes* nombreDeRes = malloc(sizeof(t_nombreDeRes));
		memcpy(&nombreDeRes->nombreDeRes_length, buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);
		nombreDeRes->nombreDeRes = malloc(nombreDeRes->nombreDeRes_length);
		memcpy(nombreDeRes->nombreDeRes, buffer->stream, nombreDeRes->nombreDeRes_length);
		nombreDeRes->nombreDeRes[nombreDeRes->nombreDeRes_length] = '\0';
		buffer->stream += nombreDeRes->nombreDeRes_length;

        list_add(respuesta->t_nombreDeRes, nombreDeRes);
    }


    return respuesta;
}