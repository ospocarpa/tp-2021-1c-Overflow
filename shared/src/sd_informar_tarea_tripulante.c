#include "../include/sd_informar_tarea_tripulante.h"

/* ******* DISCORDIADOR ******* */
// es el mensaje que envia discordiador a mi ram
t_paquete * ser_cod_informar_tarea_tripulante(int patota_id, int tripulante_id)
{

    t_paquete * paquete =malloc(sizeof(t_paquete));
    
    int tam_buffer = sizeof(int) * 2; 
    paquete->buffer =malloc(sizeof(t_buffer));
    paquete->buffer->stream = malloc(tam_buffer);
    paquete->codigo_operacion= INFORMAR_TAREA_TRIPULANTE;
    int offset = 0;

    memcpy(paquete->buffer->stream + offset, &patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete->buffer->stream + offset, &tripulante_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);
  
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
void des_cod_informar_tarea_tripulante(t_paquete* paquete, int * patota_id, int * tripulante_id)
{
    memcpy(patota_id, paquete->buffer->stream, sizeof(uint32_t));
    paquete->buffer->stream += sizeof(uint32_t);

    memcpy(tripulante_id, paquete->buffer->stream, sizeof(uint32_t));
    paquete->buffer->stream += sizeof(uint32_t);
}