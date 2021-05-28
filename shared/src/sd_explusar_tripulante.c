#include "../include/sd_expulsar_tripulante.h"

t_paquete* serializar_expulsar_tripulante(t_expulsar_tripulante data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    int tam_buffer = sizeof(int);
    paquete->buffer = malloc(sizeof(t_buffer));
    paquete->buffer->stream = malloc(tam_buffer);
    paquete->codigo_operacion= EXPULSAR_TRIPULANTE;
    int offset = 0;

    memcpy(paquete->buffer->stream + offset, &data_buffer.cant_tripulantes, sizeof(int));
	offset += sizeof(int);
    
    return paquete;

}

t_expulsar_tripulante deserializar_expulsar_tripulante(t_paquete * paquete){
    t_expulsar_tripulante data;
    memcpy(&data.cant_tripulantes,paquete->buffer->stream, sizeof(uint32_t) );

    return data;
}