#include "entidad_util.h"

void mostrar_platos(t_list *platos, int cant_platos, t_log* logger){
    char* information = string_new();
    //printf("Cant. platos: %d\n", cant_platos);
    string_append_with_format(&information, "Cant. platos: %d\n", cant_platos);
    //printf("\nPlatos:\n");
    string_append_with_format(&information, "Platos:\n");
    for(int c=0; c<cant_platos; c++){
        t_plato* plato = list_get(platos, c);
        //printf("Nombre: %s Precio: %d\n", plato->nombre, plato->precio);
        string_append_with_format(&information, "Nombre: %s Precio: %d\n", plato->nombre, plato->precio);
    }
    log_info(logger, "%s\n", information);
}

void mostrar_restaurante(t_restaurante* restaurante, t_log* logger){
    char* information = string_new();

    //printf("Nombre: %s\n", restaurante->nombre);
    string_append_with_format(&information, "Nombre: %s\n", restaurante->nombre);
    //printf("Cant. cocineros: %d\n", restaurante->cantCocineros);
    string_append_with_format(&information, "Cant. cocineros: %d\n", restaurante->cantCocineros);
    //printf("Posicion: %d-%d\n", restaurante->posicion->pos_x, restaurante->posicion->pos_y);
    string_append_with_format(&information, "Posicion: %d-%d\n", restaurante->posicion->pos_x, restaurante->posicion->pos_y);
    //printf("Cant. afinidad: %d\n", restaurante->cantAfinidad);
    string_append_with_format(&information, "Cant. afinidad: %d\n", restaurante->cantAfinidad);    
    //printf("Afinidades: ");
    string_append_with_format(&information, "Afinidades: ");
    for(int c=0; c<restaurante->cantAfinidad; c++){
        t_afinidad* afinidad = list_get(restaurante->afinidadCocineros, c);
        //printf("%s ", afinidad->nombre);
        string_append_with_format(&information, "%s ", afinidad->nombre);
    }
    mostrar_platos(restaurante->platos, restaurante->cantPlatos, logger);
    //printf("\nCant. hornos: %d\n", restaurante->cantHornos);
    string_append_with_format(&information, "\nCant. hornos: %d\n", restaurante->cantHornos);
    log_info(logger, "%s\n", information);
}

void mostrar_receta(t_receta* receta, t_log* logger){
    char* information = string_new();
    //printf("Nombre: %s\n", receta->nombre);
    string_append_with_format(&information, "Nombre: %s\n", receta->nombre);
    //printf("Cant. pasos: %d\n", receta->cantPasos);
    string_append_with_format(&information, "Cant. pasos: %d\n", receta->cantPasos);
    //printf("\nPasos:\n");
    string_append_with_format(&information, "Pasos:\n"); 
    for(int c=0; c<receta->cantPasos; c++){
        t_paso* paso = list_get(receta->pasos, c);
        //printf("Nombre: %s Tiempo: %d\n", paso->nombre, paso->tiempo);
        string_append_with_format(&information, "Nombre: %s Tiempo: %d\n", paso->nombre, paso->tiempo);
    }

    log_info(logger, "%s\n", information);
}

void mostrar_pedido(t_pedido* pedido, t_log* logger){
    t_dictionary* estados = dictionary_create();
    dictionary_put(estados, string_itoa(CREADO), "");
    dictionary_put(estados, string_itoa(PENDIENTE), "PENDIENTE");
    dictionary_put(estados, string_itoa(TERMINADO), "TERMINADO");
    dictionary_put(estados, string_itoa(CONFIRMADO), "CONFIRMADO");

    char* information = string_new();

    char* estado_descripcion = dictionary_get(estados, string_itoa(pedido->estado_Actual));
    string_append_with_format(&information, "Estado actual: %s\n", estado_descripcion);
    //printf("Estado actual: %s\n", estado_descripcion);
    string_append_with_format(&information, "Cant. platos: %d\n", pedido->cantPlatos);
    ///printf("Cant. platos: %d\n", pedido->cantPlatos);
    for(int c=0; c<pedido->cantPlatos; c++){
        t_plato* plato = list_get(pedido->platos, c);
        int item = list_get(pedido->cantidad_Platos, c);
        int item_listos = list_get(pedido->cantidad_Lista, c);
        //printf("Plato %d. Nombre: %s Precio: %d Cantidad: %d Listos: %d\n", c+1, plato->nombre, plato->precio, item, item_listos);
        string_append_with_format(&information, "Plato %d. Nombre: %s Precio: %d Cantidad: %d Listos: %d\n", c+1, plato->nombre, plato->precio, item, item_listos);
    }
    //printf("Precio total: %d\n", pedido->precio_Total);
    string_append_with_format(&information, "Precio total: %d\n", pedido->precio_Total);

    log_info(logger, "%s\n", information);
    free(estados);
}

t_receta* receta_default(){
    t_receta* receta = malloc(sizeof(t_receta));
    receta->nombre = "default";
	receta->nombre_length = strlen(receta->nombre);
	receta->pasos = list_create();
    receta->cantPasos = list_size(receta->pasos);
    return receta;
}

t_restaurante* restaurante_default(){
    t_posicion* posicion = malloc(sizeof(t_posicion));
    posicion->pos_x = 0;
    posicion->pos_y = 0;

    t_restaurante* restaurante = malloc(sizeof(t_restaurante));
    restaurante->nombre = "default";
    restaurante->nombre_length = strlen(restaurante->nombre);
    restaurante->cantCocineros = 0;
    restaurante->posicion = posicion;
    restaurante->afinidadCocineros = list_create();
    restaurante->cantAfinidad = list_size(restaurante->afinidadCocineros);
    restaurante->platos = list_create();
    restaurante->cantPlatos = list_size(restaurante->platos);
    restaurante->cantHornos = 0;
    restaurante->cantPedidos = 0;
}

t_pedido* pedido_default(){
    t_pedido* pedido = get_new_pedido();
    pedido->precio_Total = -1;
    return pedido;
}

t_pedido* get_new_pedido(){
    t_pedido* new_pedido = malloc(sizeof(t_pedido));
    new_pedido->estado_Actual = PENDIENTE;
    new_pedido->platos = list_create();
    new_pedido->cantPlatos = list_size(new_pedido->platos);
    new_pedido->cantidad_Platos = list_create();
    new_pedido->cantCantPlatos = list_size(new_pedido->cantidad_Platos);
    new_pedido->cantidad_Lista = list_create();
    new_pedido->cantCantLista = list_size(new_pedido->cantidad_Lista);
    new_pedido->precio_Total = 0;
    return new_pedido;
}

char* get_op_code(int op_code){
    t_dictionary* op_codes = dictionary_create();
    dictionary_put(op_codes, string_itoa(I_CONSULTAR_RESTAURANTE), "Input consultar restaurante");
    dictionary_put(op_codes, string_itoa(O_CONSULTAR_RESTAURANTE), "Output consultar restaurante");
    dictionary_put(op_codes, string_itoa(I_SELECCIONAR_RESTAURANTE), "Input seleccionar restaurante");
    dictionary_put(op_codes, string_itoa(O_SELECCIONAR_RESTAURANTE), "Output seleccionar restaurante");
    dictionary_put(op_codes, string_itoa(O_SELECCIONAR_RESTAURANTE), "Output seleccionar restaurante");
    dictionary_put(op_codes, string_itoa(I_OBTENER_RESTAURANTE), "Input obtener restaurante");
    dictionary_put(op_codes, string_itoa(O_OBTENER_RESTAURANTE), "Output obtener restaurante");
    dictionary_put(op_codes, string_itoa(I_CONSULTAR_PLATOS), "Input consultar platos");
    dictionary_put(op_codes, string_itoa(O_CONSULTAR_PLATOS), "Output consultar platos");
    dictionary_put(op_codes, string_itoa(I_CREAR_PEDIDO), "Input crear pedido");
    dictionary_put(op_codes, string_itoa(O_CREAR_PEDIDO), "Output crear pedido");
    dictionary_put(op_codes, string_itoa(I_GUARDAR_PEDIDO), "Input guardar pedido");
    dictionary_put(op_codes, string_itoa(O_GUARDAR_PEDIDO), "Output guardar pedido");
    dictionary_put(op_codes, string_itoa(I_ANADIR_PLATO), "Input añadir plato");
    dictionary_put(op_codes, string_itoa(O_ANADIR_PLATO), "Output añadir plato");
    dictionary_put(op_codes, string_itoa(I_GUARDAR_PLATO), "Input guardar plato");
    dictionary_put(op_codes, string_itoa(O_GUARDAR_PLATO), "Output guardar plato");
    dictionary_put(op_codes, string_itoa(I_CONFIRMAR_PEDIDO), "Input confirmar pedido");
    dictionary_put(op_codes, string_itoa(O_CONFIRMAR_PEDIDO), "Output confirmar pedido");
    dictionary_put(op_codes, string_itoa(I_PLATO_LISTO), "Input plato listo");
    dictionary_put(op_codes, string_itoa(O_PLATO_LISTO), "Output plato listo");
    dictionary_put(op_codes, string_itoa(I_CONSULTAR_PEDIDO), "Input consultar pedido");
    dictionary_put(op_codes, string_itoa(O_CONSULTAR_PEDIDO), "Output consultar pedido");
    dictionary_put(op_codes, string_itoa(I_OBTENER_PEDIDO), "Input obtener pedido");
    dictionary_put(op_codes, string_itoa(O_OBTENER_PEDIDO), "Output obtener pedido");
    dictionary_put(op_codes, string_itoa(I_FINALIZAR_PEDIDO), "Input consultar pedido");
    dictionary_put(op_codes, string_itoa(O_FINALIZAR_PEDIDO), "Output consultar pedido");
    dictionary_put(op_codes, string_itoa(I_TERMINAR_PEDIDO), "Input terminar pedido");
    dictionary_put(op_codes, string_itoa(O_TERMINAR_PEDIDO), "Output terminar pedido");
    dictionary_put(op_codes, string_itoa(I_OBTENER_RECETA), "Input obtener receta");
    dictionary_put(op_codes, string_itoa(O_OBTENER_RECETA), "Output obtener receta");
    dictionary_put(op_codes, string_itoa(RESPUESTA_BOOL), "Respuesta booleana");
    dictionary_put(op_codes, string_itoa(INPUT_HANDSHAKE), "Input handshake");
    dictionary_put(op_codes, string_itoa(OUTPUT_HANDSHAKE), "Output handshake");
    dictionary_put(op_codes, string_itoa(RESTAURANTE_TO_APP), "Restaurante a App");

    char* descripcion = dictionary_get(op_codes, string_itoa(op_code));
    free(op_codes);
    return descripcion;
}