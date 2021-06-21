#include "../include/sd_expulsar_tripulante.h"

/* ******* DISCORDIADOR ******* */
t_package ser_cod_expulsar_tripulante(t_expulsar_tripulante data_buffer)
{

    t_package paquete;
    int tam_buffer = sizeof(int);
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion = EXPULSAR_TRIPULANTE;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer + offset, &data_buffer.id_tripulante, sizeof(int));
    offset += sizeof(int);

    return paquete;
}

/* ******* MI RAM HQ ******* */
t_expulsar_tripulante des_cod_expulsar_tripulante(t_package paquete)
{
    t_expulsar_tripulante data;
    memcpy(&data.id_tripulante, paquete.buffer, sizeof(int));

    return data;
}