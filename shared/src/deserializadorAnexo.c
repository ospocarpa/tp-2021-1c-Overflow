#include "../include/deserializadorAnexo.h"

t_pedidoID* deserializar_pedido_ID(t_paquete* paquete){
	t_pedidoID* respuesta = malloc(sizeof(t_pedidoID));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->pedidoID, buffer->stream, sizeof(uint32_t));
    free(buffer);
    return respuesta;
}

t_pedidoID_With_Restaurant* deserializar_pedido_ID_With_Restaurant(t_paquete* paquete){
    t_pedidoID_With_Restaurant* I_GUARDAR_PEDIDO = malloc(sizeof(t_pedidoID_With_Restaurant));
    t_buffer* buffer = paquete->buffer;

    //tomo el largo del nombre del cliente, asigno en memoria y tomo ese largo para el cliente
    
    memcpy(&(I_GUARDAR_PEDIDO->pedidoID), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);


    //tomo el largo del nombre del restaurante, asigno en memoria y tomo ese largo para el restaurante
    memcpy(&(I_GUARDAR_PEDIDO->nombreDeRes_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    
	I_GUARDAR_PEDIDO->nombreDeRes = malloc(I_GUARDAR_PEDIDO->nombreDeRes_length +1);
	memcpy((I_GUARDAR_PEDIDO->nombreDeRes), buffer->stream, I_GUARDAR_PEDIDO->nombreDeRes_length +1);
    I_GUARDAR_PEDIDO->nombreDeRes[I_GUARDAR_PEDIDO->nombreDeRes_length] = '\0';
    //buffer->stream += I_GUARDAR_PEDIDO->restaurante_length;
    free(buffer);

    return I_GUARDAR_PEDIDO;
}

t_pedido* deserializar_pedido(t_paquete* paquete){
    t_pedido* respuesta = malloc(sizeof(t_pedido));
    t_buffer* buffer = paquete->buffer;

    memcpy(&respuesta->restaurante_nombre_length, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    respuesta->restaurante_nombre = malloc(respuesta->restaurante_nombre_length);
    memcpy(respuesta->restaurante_nombre, buffer->stream, respuesta->restaurante_nombre_length);
	buffer->stream += respuesta->restaurante_nombre_length;
    respuesta->restaurante_nombre[respuesta->restaurante_nombre_length] = '\0';

    memcpy(&respuesta->estado_Actual, buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

    memcpy(&(respuesta->cantPlatos), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    
    //uint32_t cantPlatos;
    //t_list* platos;					// list [t_plato] pero usando solo el nombre
	respuesta->platos = list_create();
	for(int c=0; c<respuesta->cantPlatos; c++){
        t_plato* plato = malloc(sizeof(t_plato));
		memcpy(&plato->nombre_length, buffer->stream, sizeof(uint32_t));
		buffer->stream += sizeof(uint32_t);

		plato->nombre = malloc(plato->nombre_length);
		memcpy(plato->nombre, buffer->stream, plato->nombre_length);
        plato->nombre[plato->nombre_length] = '\0';
        buffer->stream += plato->nombre_length;
        plato->precio = 0;

		list_add(respuesta->platos, plato);
    }

    memcpy(&(respuesta->cantCantPlatos), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //uint32_t cantCantPlatos;
    //t_list* cantidad_Platos; 		// list [int]
    respuesta->cantidad_Platos = list_create();
	for(int c=0; c<respuesta->cantCantPlatos; c++){
        int plato = 0;
        memcpy(&(plato), buffer->stream, sizeof(uint32_t));
	    buffer->stream += sizeof(uint32_t);

        list_add(respuesta->cantidad_Platos, plato);       
    }

    memcpy(&(respuesta->cantCantLista), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //uint32_t cantCantLista;
    //t_list* cantidad_Lista;			// list [int]
    respuesta->cantidad_Lista = list_create();
	for(int c=0; c<respuesta->cantCantLista; c++){
        int lista = 0;
        memcpy(&(lista), buffer->stream, sizeof(uint32_t));
	    buffer->stream += sizeof(uint32_t);

        list_add(respuesta->cantidad_Lista, lista);       

    }

    //uint32_t precio_Total;
    memcpy(&(respuesta->precio_Total), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    free(buffer);

    return respuesta;
}