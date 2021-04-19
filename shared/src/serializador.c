#include "serializador.h"

t_paquete *serializar_restaurante(t_restaurante *restaurante)
{
	/*
	char *nombre;
	uint32_t nombre_length;
	uint32_t cantCocineros;
	uint32_t cantHornos;
	t_posicion *posicion; 2x uint32_t
	uint32_t cantAfinidad;
	t_list *afinidadCocineros; // list [t_afinidad]
	uint32_t cantPlatos;
	t_list *platos; // list [t_plato]
   */
	uint32_t lengthNombres = 0;
	for (int c = 0; c < restaurante->cantPlatos; c++)
	{
		t_plato *plato = list_get(restaurante->platos, c);
		lengthNombres += plato->nombre_length;
	}
	for (int c = 0; c < restaurante->cantAfinidad; c++)
	{
		t_afinidad *afinidad = list_get(restaurante->afinidadCocineros, c);
		lengthNombres += afinidad->nombre_length;
	}
	t_buffer *new_buffer = malloc(sizeof(t_buffer));
	new_buffer->size = sizeof(uint32_t) * 7 + sizeof(uint32_t) * 2 //posicion
					   + restaurante->nombre_length 
					   + lengthNombres 
					   + restaurante->cantPlatos * 2 * sizeof(uint32_t) 
					   + restaurante->cantAfinidad * 1 * sizeof(uint32_t);

	void *stream = malloc(new_buffer->size);
	int offset = 0;
	memcpy(stream + offset, &restaurante->nombre_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, restaurante->nombre, restaurante->nombre_length);
	offset += restaurante->nombre_length;
	memcpy(stream + offset, &restaurante->cantCocineros, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &restaurante->cantHornos, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &restaurante->cantPedidos, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &restaurante->posicion->pos_x, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &restaurante->posicion->pos_y, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &restaurante->cantPlatos, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	
	for (int c = 0; c < restaurante->cantPlatos; c++)
	{
		t_plato *plato = list_get(restaurante->platos, c);

		memcpy(stream + offset, &plato->nombre_length, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, plato->nombre, plato->nombre_length);
		offset += plato->nombre_length;
		memcpy(stream + offset, &plato->precio, sizeof(uint32_t));
		offset += sizeof(uint32_t);
	}
	
	memcpy(stream + offset, &restaurante->cantAfinidad, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	for (int c = 0; c < restaurante->cantAfinidad; c++)
	{
		t_afinidad *afinidad = list_get(restaurante->afinidadCocineros, c);

		memcpy(stream + offset, &afinidad->nombre_length, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, afinidad->nombre, afinidad->nombre_length);
		offset += afinidad->nombre_length;
	}
	new_buffer->stream = stream;
	t_paquete *paquete = malloc(sizeof(t_paquete));
	paquete->codigo_operacion = O_OBTENER_RESTAURANTE;
	paquete->buffer = new_buffer;
	paquete->from_client = false;

	return paquete;
}

t_paquete *serializar_receta(t_receta *receta)
{
	uint32_t lengthNombres = 0;
	for (int c = 0; c < receta->cantPasos; c++)
	{
		t_paso *paso = list_get(receta->pasos, c);
		lengthNombres += paso->nombre_length;
	}

	t_buffer *new_buffer = malloc(sizeof(t_buffer));
	new_buffer->size = sizeof(uint32_t) * 2 + lengthNombres + receta->cantPasos * 2 * sizeof(uint32_t) + receta->nombre_length;
	void *stream = malloc(new_buffer->size);
	int offset = 0;

	memcpy(stream + offset, &receta->nombre_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, receta->nombre, receta->nombre_length);
	offset += receta->nombre_length;
	memcpy(stream + offset, &receta->cantPasos, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	for (int c = 0; c < receta->cantPasos; c++)
	{
		t_paso *paso = list_get(receta->pasos, c);

		memcpy(stream + offset, &paso->nombre_length, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, paso->nombre, paso->nombre_length);
		offset += paso->nombre_length;
		memcpy(stream + offset, &paso->tiempo, sizeof(uint32_t));
		offset += sizeof(uint32_t);
	}

	new_buffer->stream = stream;
	t_paquete *paquete = malloc(sizeof(t_paquete));
	//paquete->codigo_operacion = RECETA;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}

t_paquete *serializar_respuesta_bool(t_respuesta_bool *respuesta)
{
	t_paquete *paquete = malloc(sizeof(t_paquete));
	t_buffer *new_buffer = malloc(sizeof(t_buffer));
	new_buffer->size = sizeof(uint32_t) * 1 //longitud del estado_length
					   + strlen(respuesta->estado) + 1;
	void *stream = malloc(new_buffer->size);
	int offset = 0; // Desplazamiento
	memcpy(stream + offset, &respuesta->estado_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, respuesta->estado, strlen(respuesta->estado) + 1);
	new_buffer->stream = stream;
	paquete->codigo_operacion = RESPUESTA_BOOL;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}
