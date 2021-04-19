#include "desearilizador.h"

t_restaurante *deserializar_restaurante(t_paquete *paquete)
{
	t_restaurante *restaurante = malloc(sizeof(t_restaurante));
	t_buffer *buffer = paquete->buffer;

	memcpy(&(restaurante->nombre_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	restaurante->nombre = malloc(restaurante->nombre_length);
	memcpy(restaurante->nombre, buffer->stream, restaurante->nombre_length);
	restaurante->nombre[restaurante->nombre_length] = '\0';
	buffer->stream += restaurante->nombre_length;

	memcpy(&(restaurante->cantCocineros), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	memcpy(&(restaurante->cantHornos), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	memcpy(&(restaurante->cantPedidos), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	restaurante->posicion = malloc(sizeof(t_posicion));
	memcpy(&(restaurante->posicion->pos_x), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	memcpy(&(restaurante->posicion->pos_y), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	memcpy(&(restaurante->cantPlatos), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	restaurante->platos = list_create();

	for (int c = 0; c < restaurante->cantPlatos; c++)
	{
		t_plato *plato = malloc(sizeof(t_plato));
		memcpy(&(plato->nombre_length), buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);

		plato->nombre = malloc(plato->nombre_length);
		memcpy(plato->nombre, buffer->stream, plato->nombre_length);
		plato->nombre[plato->nombre_length] = '\0';
		buffer->stream += plato->nombre_length;
		memcpy(&(plato->precio), buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);
		list_add(restaurante->platos, plato);
	}

	memcpy(&(restaurante->cantAfinidad), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	restaurante->afinidadCocineros = list_create();

	for (int c = 0; c < restaurante->cantAfinidad; c++)
	{
		t_afinidad *afinidad = malloc(sizeof(t_afinidad));
		memcpy(&(afinidad->nombre_length), buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);

		afinidad->nombre = malloc(afinidad->nombre_length);
		memcpy(afinidad->nombre, buffer->stream, afinidad->nombre_length);
		buffer->stream += afinidad->nombre_length;
		buffer->stream += sizeof(uint32_t);
		list_add(restaurante->afinidadCocineros, afinidad);
	}

	free(buffer);
	return restaurante;
}

t_receta *deserializar_receta(t_paquete *paquete)
{
	t_receta *receta = malloc(sizeof(t_receta));
	t_buffer *buffer = paquete->buffer;

	memcpy(&(receta->nombre_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	receta->nombre = malloc(receta->nombre_length);
	memcpy(receta->nombre, buffer->stream, receta->nombre_length);
	receta->nombre[receta->nombre_length] = '\0';
	buffer->stream += receta->nombre_length;

	memcpy(&(receta->cantPasos), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	receta->pasos = list_create();
	for (int c = 0; c < receta->cantPasos; c++)
	{
		t_paso *paso = malloc(sizeof(t_paso));
		memcpy(&paso->nombre_length, buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);
		paso->nombre = malloc(paso->nombre_length);
		memcpy(paso->nombre, buffer->stream, paso->nombre_length);
		paso->nombre[paso->nombre_length] = '\0';
		buffer->stream += paso->nombre_length;

		memcpy(&paso->tiempo, buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);

		list_add(receta->pasos, paso);
	}
	return receta;
}

t_respuesta_bool *deserializar_respuesta_bool(t_paquete *paquete)
{
	t_respuesta_bool *respuesta = malloc(sizeof(t_respuesta_bool));
	t_buffer *buffer = paquete->buffer;

	// Tomo largo de la respuesta para tomar despues la respuesta del buffer.
	memcpy(&(respuesta->estado_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->estado = malloc(respuesta->estado_length);
	memcpy(respuesta->estado, buffer->stream, respuesta->estado_length);
	respuesta->estado[respuesta->estado_length] = '\0';

	
	buffer->stream += respuesta->estado_length;

	return respuesta;
}
