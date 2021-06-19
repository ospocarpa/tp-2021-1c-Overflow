#include "../include/sd_listar_tripulantes.h"

// lo que envia mi ram
t_paquete* serializar_listar_tripulantes(t_listar_tripulantes data_buffer){

    t_paquete * paquete =malloc(sizeof(t_paquete));
    int tam_tripulante = 20;
    int tam_buffer = data_buffer.cant_tripulantes * tam_tripulante;
    paquete->buffer= malloc(sizeof(t_buffer));
    paquete->buffer->stream = malloc(tam_buffer);

    paquete->codigo_operacion= LISTAR_TRIPULANTES;
    int offset = 0;
    memcpy(paquete->buffer->stream+offset, &data_buffer.cant_tripulantes, sizeof(int));
    offset+= sizeof(int);

    void agregar_tripulante_a_stream(t_tripulante * tripulante){
        memcpy(paquete->buffer->stream+offset, &tripulante->patota_id, sizeof(int));
        offset+= sizeof(int);

        memcpy(paquete->buffer->stream+offset, &tripulante->tripulante_id, sizeof(int));
        offset+= sizeof(int);

        memcpy(paquete->buffer->stream+offset, &tripulante->posicion.posx, sizeof(int));
        offset+= sizeof(int);

        memcpy(paquete->buffer->stream+offset, &tripulante->posicion.posy, sizeof(int));
        offset+= sizeof(int);

        memcpy(paquete->buffer->stream+offset, &tripulante->status, sizeof(status_tripulante));
        offset+= sizeof(status_tripulante);

    }

    list_iterate(data_buffer.tripulantes,agregar_tripulante_a_stream);
  
    return paquete;

}

//lo utiliza discordiador cuando resive la respuesta
t_listar_tripulantes deserializar_listar_tripulantes(t_paquete* paquete){
    t_listar_tripulantes data;
    int long_tripulante; //tamaño de un tripulante

    memcpy(&data.cant_tripulantes,paquete->buffer->stream, sizeof(int) );
    paquete->buffer->stream+=sizeof(int);

    data.tripulantes = list_create();

    t_tripulante * get_tripulante(void * byte_tripulante){
        t_tripulante * un_tripulante = malloc(sizeof(t_tripulante));

        memcpy(&un_tripulante->patota_id, byte_tripulante, sizeof(int));
        memcpy(&un_tripulante->tripulante_id, byte_tripulante+sizeof(int), sizeof(int));
        memcpy(&un_tripulante->posicion.posx, byte_tripulante+sizeof(int)+sizeof(int), sizeof(int));
        memcpy(&un_tripulante->posicion.posy, byte_tripulante+sizeof(int)+sizeof(int)+sizeof(int), sizeof(int));
        memcpy(&un_tripulante->status, byte_tripulante+sizeof(int)+sizeof(int)+sizeof(int)+sizeof(int), sizeof(int));

        return un_tripulante;
    }

    for (size_t i = 0; i < data.cant_tripulantes; i++)
    {
        t_tripulante * tripulante;

        tripulante = get_tripulante(paquete->buffer->stream);
        list_add(data.tripulantes, tripulante);
        paquete->buffer->stream+=20;
    }
    

    return data;
}