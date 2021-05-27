#include "../include/sd_expulsar_tripulante.h"

t_paquete* serializar_expulsar_tripulante(t_expulsar_tripulante data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    
    int tam_buffer = sizeof(int) 
    t_buffer * new_buffer =malloc(sizeof(t_buffer));
    void * stream = malloc(tam_buffer);
    int offset = 0;
    new_buffer ->size = tam_buffer;

    memcpy(stream + offset, &input->cant_tripulante, sizeof(uint32_t));
	offset += sizeof(int);
    
    
    new_buffer->stream = stream;
    paquete->codigo_operacion= EXPULSAR_TRIPULANTE;
    paquete->buffer =new_buffer;
    
    return paquete;

}

t_expulsar_tripulante deserializar_expulsar_tripulante(t_paquete* paquete){
    t_expulsar_tripulante data;
    return data;
}