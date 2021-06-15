#include "../include/sd_informar_tarea_tripulante.h"

/* ******* DISCORDIADOR ******* */
// es el mensaje que envia discordiador a mi ram
t_package ser_cod_informar_tarea_tripulante(int patota_id, int tripulante_id)
{

    t_package paquete;
    int tam_buffer = sizeof(int) * 2;
    //void * stream = malloc(tam_buffer);
    paquete.buffer =malloc(tam_buffer);
    paquete.cod_operacion= INFORMAR_TAREA_TRIPULANTE;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer, &patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &tripulante_id, sizeof(uint32_t));
	
  
    return paquete;
}

// es el mensaje que recibe discordiador de mi ram
t_info_tarea des_res_informacion_tarea_tripulante(t_paquete * paquete){
    t_info_tarea data;

    memcpy(&data.tarea, paquete->buffer->stream, sizeof(type_task));
    paquete->buffer->stream+= sizeof(type_task);

    memcpy(&data.parametro, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    memcpy(&data.posicion.posx, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    memcpy(&data.posicion.posy, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    memcpy(&data.tiempo, paquete->buffer->stream, sizeof(int));

    return data;
}


/* ******* MI RAM HQ ******* */
// es la serializacion de la respuesta de mi ram al mensaje de discordiador
t_paquete* ser_res_informar_tarea_tripulante(t_info_tarea data_buffer)
{
    int tam_buffer = sizeof(type_task) + sizeof(int) * 2+ sizeof(Posicion);
    t_paquete * paquete = malloc(sizeof(t_paquete));
    paquete->buffer = malloc(sizeof(t_buffer));
    paquete->buffer->stream = malloc(tam_buffer);
    int offset = 0;
    paquete->codigo_operacion = INFORMAR_TAREA_TRIPULANTE;

    memcpy(paquete->buffer->stream, &data_buffer.tarea, sizeof(type_task));
    offset += sizeof(type_task);

    memcpy(paquete->buffer->stream+offset, &data_buffer.parametro, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete->buffer->stream+offset, &data_buffer.posicion.posx, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete->buffer->stream+offset, &data_buffer.posicion.posy, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete->buffer->stream+offset, &data_buffer.tiempo, sizeof(int));

    return paquete;
}

// es la deserializacion del mensaje enviado por discordiador a mi ram
void des_cod_informar_tarea_tripulante(void * buffer, uint32_t * patota_id, uint32_t * tripulante_id)
{
    memcpy(patota_id, buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t);

    memcpy(tripulante_id, buffer, sizeof(uint32_t));
}