#include "../include/sd_informar_tarea_tripulante.h"

/* ******* DISCORDIADOR ******* */
// es el mensaje que envia discordiador a mi ram
t_package ser_cod_informar_tarea_tripulante(t_short_info_tripulante info)
{

    t_package paquete;
    int tam_buffer = sizeof(int) * 2;
    paquete.buffer =malloc(tam_buffer);
    paquete.cod_operacion= INFORMAR_TAREA_TRIPULANTE;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer, &info.patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &info.tripulante_id, sizeof(uint32_t));	
  
    return paquete;
}

// es el mensaje que recibe discordiador de mi ram
t_info_tarea des_res_informacion_tarea_tripulante(t_package paquete){
    t_info_tarea data;

    memcpy(&data.tarea, paquete.buffer, sizeof(type_task));
    paquete.buffer += sizeof(type_task);

    memcpy(&data.parametro, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    memcpy(&data.posicion.posx, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    memcpy(&data.posicion.posy, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    memcpy(&data.tiempo, paquete.buffer, sizeof(int));

    return data;
}


/* ******* MI RAM HQ ******* */
// es la serializacion de la respuesta de mi ram al mensaje de discordiador
t_package ser_res_informar_tarea_tripulante(t_info_tarea data_buffer)
{
    int tam_buffer = sizeof(type_task) + sizeof(int) * 2+ sizeof(Posicion);
    t_package paquete;
    paquete.buffer = malloc(tam_buffer);
    int offset = 0;
    paquete.cod_operacion = INFORMAR_TAREA_TRIPULANTE;
    paquete.tam_buffer = tam_buffer;

    memcpy(paquete.buffer, &data_buffer.tarea, sizeof(type_task));
    offset += sizeof(type_task);

    memcpy(paquete.buffer+offset, &data_buffer.parametro, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete.buffer+offset, &data_buffer.posicion.posx, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete.buffer+offset, &data_buffer.posicion.posy, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete.buffer+offset, &data_buffer.tiempo, sizeof(int));

    return paquete;
}

// es la deserializacion del mensaje enviado por discordiador a mi ram
t_short_info_tripulante des_cod_informar_tarea_tripulante(t_package paquete)
{
    t_short_info_tripulante info;
    memcpy(&info.patota_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&info.tripulante_id, paquete.buffer, sizeof(uint32_t));

    return info;
}