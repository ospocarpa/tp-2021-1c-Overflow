#include "../include/sd_informar_estado.h"

/* ******* DISCORDIADOR ******* */
t_package ser_cod_informar_estado(t_estado_tripulante info)
{
    t_package paquete;
    int tam_buffer = sizeof(uint32_t) * 2 + sizeof(status_tripulante);
    paquete.tam_buffer = tam_buffer;
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion= INFORMAR_ESTADO_TRIPULANTE;
    int offset = 0;

    memcpy(paquete.buffer, &info.patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &info.tripulante_id, sizeof(uint32_t));	
    offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &info.status, sizeof(status_tripulante));	
    offset += sizeof(status_tripulante);

    return paquete;
}

/* ******* MI RAM HQ ******* */
t_estado_tripulante des_cod_informar_estado(t_package paquete)
{
    t_estado_tripulante info;

    memcpy(&info.patota_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&info.tripulante_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&info.status, paquete.buffer, sizeof(status_tripulante));

    return info;
}