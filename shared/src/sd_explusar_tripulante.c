#include "../include/sd_expulsar/tripulante"

t_paquete* serializar_expulsar_tripulante(t_expulsar_tripulante* data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    int tam_buffer = sizeof(int) * 3 
    t_buffer * new_buffer =malloc(sizeof(t_buffer));
    void * stream = malloc(tam_buffer);
    int offset = 0;
    memcpy(stream + offset, &input->numero_tripulante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    new_buffer ->size = tam_buffer;
    

    paquete->codigo_operacion= EXPULSAR_TRIPULANTE;
    paquete->buffer =new_buffer;
    
    return paquete;

}

t_listar_tripulantes deserializar_expulsar_tripulante(t_paquete* paquete){

    return data;
}