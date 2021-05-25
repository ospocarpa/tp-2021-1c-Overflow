#include "../include/sd_listar_tripulantes"

t_paquete* serializar_listar_tripulantes(t_listar_tripulantes* data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    int tam_buffer = sizeof(int) * 3 
    t_buffer * new_buffer =malloc(sizeof(t_buffer));
    void * stream = malloc(tam_buffer);
    int offset = 0;
    new_buffer ->size = tam_buffer;

    paquete->codigo_operacion= LISTAR_TRIPULANTES;
    paquete->buffer =new_buffer;
    
    return paquete;

}

t_listar_tripulantes deserializar_listar_tripulantes(t_paquete* paquete){
    t_listar_tripulante data;

    return data;
}