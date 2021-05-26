#include "../include/sd_informar_tarea_tripulante.h"

t_paquete* serializar_informar_tarea_tripulante(t_informar_tarea_tripulante data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    /* 
    int tam_buffer = sizeof(int) * 3 
    t_buffer * new_buffer =malloc(sizeof(t_buffer));
    void * stream = malloc(tam_buffer);
    int offset = 0;
    memcpy(stream + offset, &input->patota_id, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    memcpy(stream + offset, &input->numero_tripulante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    new_buffer ->size = tam_buffer;
    memcpy(stream + offset, &input->posicion->posx, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &input->posicion->posy, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    paquete->codigo_operacion= INFORMAR_TAREA_TRIPULANTE;
    paquete->buffer =new_buffer;
    */
    
    return paquete;

}

t_informar_tarea_tripulante  deserializar_informar_tarea_tripulante(t_paquete* paquete){
    t_informar_tarea_tripulante respuesta ;
    /* 
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->patota_id, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    */
    return respuesta;
}