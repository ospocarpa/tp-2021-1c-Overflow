#include "consultar_plato.h"

t_paquete *serializar_I_CONSULTAR_PLATOS(t_nombreDeRes *datos){

    t_paquete *paquete = malloc(sizeof(t_paquete));
    t_buffer *new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = datos->nombreDeRes_length + sizeof(uint32_t)+1;
    void *stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

    memcpy(stream + offset, &datos->nombreDeRes_length, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(stream + offset, datos->nombreDeRes, datos->nombreDeRes_length+1);
    offset += datos->nombreDeRes_length;

    new_buffer->stream = stream;
    paquete->codigo_operacion = I_CONSULTAR_PLATOS;
    paquete->buffer = new_buffer;
    paquete->from_client = false;
    return paquete;
}

t_nombreDeRes *deserializar_I_CONSULTAR_PLATOS(t_paquete *paquete)
{
    t_nombreDeRes *respuesta = malloc(sizeof(t_nombreDeRes));
    t_buffer *buffer = paquete->buffer;

    memcpy(&respuesta->nombreDeRes_length, buffer->stream, sizeof(uint32_t));
    buffer->stream += sizeof(uint32_t);
    respuesta->nombreDeRes = malloc(respuesta->nombreDeRes_length);
    memcpy(respuesta->nombreDeRes, buffer->stream, respuesta->nombreDeRes_length);
    respuesta->nombreDeRes[respuesta->nombreDeRes_length] = '\0';

    free(buffer);
    return respuesta;
}

t_paquete *serializar_O_CONSULTAR_PLATOS(t_platos *datos)
{
    uint32_t lengthNombres = 0;
	int cant_platos = 0;
    int auxiliar = datos->cantPlatos;
    if(auxiliar > -1 && auxiliar < 99){
        cant_platos = datos->cantPlatos;
    }
    for(int c=0; c< cant_platos; c++){
		t_plato* plato = list_get(datos->platos, c);
		lengthNombres += plato->nombre_length;
	}

    t_buffer *new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size = sizeof(uint32_t) * 1 + lengthNombres + cant_platos * 2 * sizeof(uint32_t);
    void *stream = malloc(new_buffer->size);
    int offset = 0;

    memcpy(stream + offset, &datos->cantPlatos, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    for (int c = 0; c < cant_platos; c++)
    {
        t_plato *plato = list_get(datos->platos, c);

        memcpy(stream + offset, &plato->nombre_length, sizeof(uint32_t));
        //printf("Length: %d\n", plato->nombre_length);
        offset += sizeof(uint32_t);
        memcpy(stream + offset, plato->nombre, plato->nombre_length);
        //printf("Nombre: %s\n", plato->nombre);
        offset += plato->nombre_length;
        memcpy(stream + offset, &plato->precio, sizeof(uint32_t));
        //printf("Precio: %d\n", plato->precio);
        offset += sizeof(uint32_t);
    }

    new_buffer->stream = stream;
    t_paquete *paquete = malloc(sizeof(t_paquete));
    paquete->codigo_operacion = O_CONSULTAR_PLATOS;
    paquete->buffer = new_buffer;
    paquete->from_client = false;
    return paquete;
}
t_platos *deserializar_O_CONSULTAR_PLATOS(t_paquete *paquete)
{
    t_platos *platos = malloc(sizeof(t_platos));
    t_buffer *buffer = paquete->buffer;

    memcpy(&(platos->cantPlatos), buffer->stream, sizeof(uint32_t));
    buffer->stream += sizeof(uint32_t);

    int cant_platos = 0;
    int auxiliar = platos->cantPlatos;
    if(auxiliar >-1 && auxiliar < 99){
        cant_platos = platos->cantPlatos;
    }

    platos->platos = list_create();
    for (int c = 0; c < cant_platos; c++)
    {
        t_plato *plato = malloc(sizeof(t_plato));
        memcpy(&plato->nombre_length, buffer->stream, sizeof(uint32_t));
        buffer->stream += sizeof(uint32_t);
        plato->nombre = malloc(plato->nombre_length);
        memcpy(plato->nombre, buffer->stream, plato->nombre_length);
        plato->nombre[plato->nombre_length] = '\0';
        buffer->stream += plato->nombre_length;

        memcpy(&plato->precio, buffer->stream, sizeof(uint32_t));
        buffer->stream += sizeof(uint32_t);

        list_add(platos->platos, plato);
    }

    return platos;
}