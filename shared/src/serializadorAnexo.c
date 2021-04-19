#include "../include/serializadorAnexo.h"

t_paquete* serializar_pedido_ID(t_pedidoID* datos, int opcode){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = sizeof(uint32_t);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento
	memcpy(stream + offset, &datos->pedidoID, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    
    new_buffer->stream = stream;
    paquete->codigo_operacion = opcode;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
    return paquete;
}

t_paquete* serializar_pedido_ID_With_Restaurant(t_pedidoID_With_Restaurant* datos, int opcode){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size = sizeof(uint32_t)*2 //longitud del idPedido y restaurante_length
                        + strlen(datos->nombreDeRes) +1;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento
    memcpy(stream + offset, &datos->pedidoID, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(stream + offset, &datos->nombreDeRes_length, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(stream + offset, datos->nombreDeRes, strlen(datos->nombreDeRes) +1);
    
    new_buffer->stream = stream;
    paquete->codigo_operacion = opcode;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
	return paquete;
}

t_paquete* serializar_pedido(t_pedido* datos, int opcode){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    uint32_t lengthNombres = 0;
	for(int c=0; c< datos->cantPlatos; c++){
		t_plato* plato_item = list_get(datos->platos, c);
        char* plato = plato_item->nombre;
		lengthNombres += strlen(plato);
	}

    new_buffer->size = 
                sizeof(uint32_t) //estado_pedido
                + lengthNombres//lista_Platos
                + datos->restaurante_nombre_length//lista_Platos
                + datos->cantPlatos * 1 * sizeof(uint32_t)//cantidad_Platos tlist
                + datos->cantCantPlatos * 1 * sizeof(uint32_t)//cantidad_Platos tlist
                + datos->cantCantLista * 1 * sizeof(uint32_t)//cantidad_Lista
                + sizeof(uint32_t)*5//precio_Total+cantPlatos+cantCantPlatos+cantCantLista+restaurante_nombre_length
    ;
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

    memcpy(stream + offset, &datos->restaurante_nombre_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    memcpy(stream + offset, datos->restaurante_nombre, datos->restaurante_nombre_length);
	offset += datos->restaurante_nombre_length;

	memcpy(stream + offset, &datos->estado_Actual, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &datos->cantPlatos, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    //ListaPlatos
    //uint32_t cantPlatos;
    //t_list* platos;					// list [t_plato] pero usando solo el nombre
    for(int c=0; c< datos->cantPlatos; c++){
		t_plato* plato = list_get(datos->platos, c);
		memcpy(stream + offset, &plato->nombre_length, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, plato->nombre, plato->nombre_length);
		offset += plato->nombre_length;

	}

    memcpy(stream + offset, &datos->cantCantPlatos, sizeof(uint32_t));
	offset += sizeof(estado_pedido);
    //Cantidad Cantidad Platos
    //uint32_t cantCantPlatos;
    //t_list* cantidad_Platos; 		// list [int]

    for(int c=0; c< datos->cantCantPlatos; c++){
		int cantPlato = list_get(datos->cantidad_Platos, c);

		memcpy(stream + offset, &cantPlato, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		
	}

    memcpy(stream + offset, &datos->cantCantLista, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    //Cantidad Lista
    //uint32_t cantCantLista;
	//t_list* cantidad_Lista;			// list [int]
	
    for(int c=0; c< datos->cantCantLista; c++){
        int cantLista = list_get(datos->cantidad_Lista, c);

		memcpy(stream + offset, &cantLista, sizeof(uint32_t));
		offset += sizeof(uint32_t);
	}

    //	uint32_t precio_Total;
    memcpy(stream + offset, &datos->precio_Total, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = opcode;
	paquete->buffer = new_buffer;
    paquete->from_client = false;
	return paquete;
}