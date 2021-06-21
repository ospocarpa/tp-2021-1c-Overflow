#include "../include/sd_informar_posicion_tripulante.h"


/* ******* DISCORDIADOR ******* */
// es el mensaje que envia discordiador a mi ram
t_package ser_cod_informar_posicion_tripulante(t_short_info_tripulante data){
    t_package paquete;
    int tam_buffer = sizeof(int)*4;
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion = INFORMAR_POSICION_TRIPULANTE;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer, &data.patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &data.tripulante_id, sizeof(uint32_t));

    return paquete;
}
// es el mensaje que recibe discordiador de mi ram
t_informar_posicion_tripulante des_res_informar_posicion_tripulante(t_package paquete){
    t_informar_posicion_tripulante data;


    memcpy(&data.patota_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&data.tripulante_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&data.posicion.posx, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    memcpy(&data.posicion.posy, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    return data;
}

/* ******* MI RAM HQ ******* */
// es la serializacion de la respuesta de mi ram al mensaje de discordiador
t_package ser_res_informar_posicion_tripulante(t_informar_posicion_tripulante data_buffer){
    int tam_buffer = sizeof(int) * 4;
    t_package paquete;
    paquete.buffer = malloc(tam_buffer);
    paquete.tam_buffer = tam_buffer;
    paquete.cod_operacion = INFORMAR_POSICION_TRIPULANTE;
    int offset = 0;

    memcpy(paquete.buffer, &data_buffer.patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &data_buffer.tripulante_id, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(paquete.buffer+offset, &data_buffer.posicion.posx, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete.buffer+offset, &data_buffer.posicion.posy, sizeof(int));
    offset += sizeof(int);

    return paquete;

}
// es la deserializacion del mensaje enviado por discordiador a mi ram
t_short_info_tripulante des_cod_informar_posicion_tripulante(t_package paquete){
    
    t_short_info_tripulante info;
    memcpy(&info.patota_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&info.tripulante_id, paquete.buffer, sizeof(uint32_t));

    return info;
}