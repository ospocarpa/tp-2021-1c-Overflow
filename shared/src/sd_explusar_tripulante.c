#include "../include/sd_expulsar_tripulante.h"

/* ******* DISCORDIADOR ******* */
t_package ser_cod_expulsar_tripulante(t_expulsar_tripulante data_buffer){

    t_package paquete;
    int tam_buffer = sizeof(uint32_t)*2;
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion = EXPULSAR_TRIPULANTE;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer + offset, &data_buffer.patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &data_buffer.tripulante_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    
    return paquete;
}

/* ******* MI RAM HQ ******* */
t_expulsar_tripulante des_cod_expulsar_tripulante(t_package paquete){
    t_expulsar_tripulante data;
    int offset=0;

    memcpy(&data.patota_id,paquete.buffer, sizeof(uint32_t) );
    offset = sizeof(uint32_t);
    memcpy(&data.tripulante_id,paquete.buffer+offset, sizeof(uint32_t) );

    return data;
}