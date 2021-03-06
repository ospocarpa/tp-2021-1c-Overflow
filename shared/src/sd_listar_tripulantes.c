#include "../include/sd_listar_tripulantes.h"

/* ******* MI RAM HQ ******* */
// lo que responde mi ram a discordiador
t_package ser_res_listar_tripulantes(t_listar_tripulantes data_buffer){

    t_package paquete;
    int tam_tripulante = 20;
    int tam_buffer = data_buffer.cant_tripulantes * tam_tripulante + sizeof(int);
    paquete.buffer = malloc(tam_buffer);
    paquete.tam_buffer = tam_buffer;
    paquete.cod_operacion= LISTAR_TRIPULANTES;
    int offset = 0;

    memcpy(paquete.buffer, &data_buffer.cant_tripulantes, sizeof(int));
    offset+= sizeof(int);

    void agregar_tripulante_a_stream(t_tripulante * tripulante){

        uint32_t patotaid = tripulante->patota_id;
        memcpy(paquete.buffer+offset, &patotaid, sizeof(uint32_t));
        offset+= sizeof(uint32_t);

        uint32_t tripulanteid = tripulante->tripulante_id;
        memcpy(paquete.buffer+offset, &tripulanteid, sizeof(uint32_t));
        offset+= sizeof(uint32_t);

        int posx = tripulante->posicion.posx;
        memcpy(paquete.buffer+offset, &posx, sizeof(int));
        offset+= sizeof(int);

        int posy = tripulante->posicion.posy;
        memcpy(paquete.buffer+offset, &posy, sizeof(int));
        offset+= sizeof(int);

        status_tripulante estado = tripulante->status;
        memcpy(paquete.buffer+offset, &estado, sizeof(int));
        offset+= sizeof(int);

    }

    list_iterate(data_buffer.tripulantes,agregar_tripulante_a_stream);
  
    return paquete;

}

/* ******* DISCORDIADOR ******* */
//lo utiliza discordiador cuando resive la respuesta de mi ram
t_listar_tripulantes des_res_listar_tripulantes(t_package paquete){
    t_listar_tripulantes data;
    int long_tripulante; //tamaño de un tripulante

    memcpy(&data.cant_tripulantes,paquete.buffer, sizeof(int) );
    paquete.buffer += sizeof(int);

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

        tripulante = get_tripulante(paquete.buffer);
        list_add(data.tripulantes, tripulante);
        paquete.buffer += 20;
    }
    
    return data;
}