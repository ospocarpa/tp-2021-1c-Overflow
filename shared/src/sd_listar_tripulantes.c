#include "../include/sd_listar_tripulantes.h"

// lo que envia mi ram
t_paquete* serializar_listar_tripulantes(t_listar_tripulantes data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    int tam_tripulante = sizeof(t_tripulante);
    int tam_buffer = list_size(data_buffer.tripulantes) * tam_tripulante;
    t_buffer * new_buffer =malloc(sizeof(t_buffer));
    void * stream = malloc(tam_buffer);
    int offset = 0;
    new_buffer->size = tam_buffer;

    void agregar_tripulante_a_stream(t_tripulante tripulante){
        memcpy(stream, &tripulante.patota_id, sizeof(int));
        offset+= sizeof(int);

        memcpy(stream+offset, &tripulante.tripulante_id, sizeof(int));
        offset+= sizeof(int);

        memcpy(stream+offset, &tripulante.posicion.posx, sizeof(int));
        offset+= sizeof(int);

        memcpy(stream+offset, &tripulante.posicion.posy, sizeof(int));
        offset+= sizeof(int);

        memcpy(stream+offset, &tripulante.status, sizeof(status_tripulante));
        offset+= sizeof(status_tripulante);

    }

    list_iterate(data_buffer.tripulantes,agregar_tripulante_a_stream);
    
    new_buffer->stream = stream;
    paquete->codigo_operacion= LISTAR_TRIPULANTES;
    paquete->buffer =new_buffer;
    
    return paquete;

}

//lo utiliza discordiador cuando resive la respuesta
t_listar_tripulantes deserializar_listar_tripulantes(t_paquete* paquete){
    t_listar_tripulantes data;

    


    return data;
}