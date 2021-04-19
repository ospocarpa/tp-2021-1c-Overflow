#include "Cliente_MultiModulo.h"

/*
void seleccionarRestaurante(){
        /*
        RECIBE 
        Cliente
        Restaurante
        */

       /*
       typedef struct
	{
		char* cliente;
        uint32_t cliente_length;
		char* restaurante;
        uint32_t restaurante_length;
	} t_I_SELECCIONAR_RESTAURANTE;
        * /
    char* cliente,restaurante;
    t_I_SELECCIONAR_RESTAURANTE* datos = malloc(sizeof(t_I_SELECCIONAR_RESTAURANTE));;

    log_info(logger,"Seleccionar Restaurante Elegido");
    printf("\t Ingrese Cliente: ");
    scanf("%s", &cliente);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", &restaurante);
    datos->cliente = &cliente;
    datos->cliente_length =strlen(&cliente);
    datos->nombreDeRes= &restaurante;
    datos->nombreDeRes_length =strlen(&restaurante);

    t_paquete* paquete = malloc(sizeof(t_paquete));
    paquete = serializar_I_SELECCIONAR_RESTAURANTE(datos);
    //sendMessage(paquete, cCon);
    //Va para la app, pero mando al restaurante para testing
sendMessage(paquete, cCon);

    //t_paquete* serializar_I_SELECCIONAR_RESTAURANTE(t_I_SELECCIONAR_RESTAURANTE* datos);
    //output es respuesta bool


};

*/

//Consultar Platos(APP,Restaurante,SINDICATO)
void consultarPlatos(){
    /*
    Recibe: Restaurante (en el caso de que se envíe del Restaurante al Sindicato).
    */

    char* restaurante = malloc(100);
    t_nombreDeRes* datos = malloc(sizeof(t_nombreDeRes));

    log_info(logger,"Consultar Platos Elegido");
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(restaurante);

    t_paquete* paquete = malloc(sizeof(t_paquete));
    paquete = serializar_I_CONSULTAR_PLATOS(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);

}

//Guardar Pedido(COMANDA,SINDICATO)
void guardarPedido(){
    /*
    Recibe:
        Nombre del Restaurante
        ID de pedido
    */
    int pedidoId;
    char *restaurante = malloc(100);

    t_I_GUARDAR_PEDIDO* datos =  malloc(sizeof(t_I_GUARDAR_PEDIDO));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    log_info(logger,"Guardar Pedido Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->idPedido = pedidoId;
    datos->restaurante= restaurante;
    datos->restaurante_length = strlen(restaurante);
    printf("%d\n", datos->restaurante_length);
    paquete =  serializar_I_GUARDAR_PEDIDO(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);
}


//Guardar Plato(COMANDA, SINDICATO)
void guardarPlato(){
    /* 
    Recibe:
        Restaurante
        ID de pedido
        Comida
        Cantidad
    */
//t_paquete* serializar_I_GUARDAR_PLATO(t_I_GUARDAR_PLATO* datos);
    int pedidoId,cantidad;
    char *restaurante = malloc(100);
    char* plato = malloc(100);

    t_I_GUARDAR_PLATO* datos =  malloc(sizeof(t_I_GUARDAR_PLATO));

    t_paquete* paquete = malloc(sizeof(t_paquete));
    log_info(logger,"Guardar Plato Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    printf("\t Ingrese Plato: ");
    scanf("%s", plato);
    printf("\t Ingrese Cantidad: ");
    scanf("%d", &cantidad);
    datos->pedidoID = pedidoId;
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(datos->nombreDeRes);
    datos->plato= plato;
    datos->plato_length =strlen(datos->plato);
    datos->cantidad = cantidad;
    paquete =  serializar_I_GUARDAR_PLATO(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);

}


//Crear Pedido(APP,Restaurante)
void crearPedido(){
    /* 
    Recibe:
        nada
    */

    t_paquete* paquete = malloc(sizeof(t_paquete));
    log_info(logger,"Crear Pedido Elegido");

    t_buffer* new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size =1;
    void* stream = malloc(new_buffer->size);
    new_buffer->stream = stream;
    paquete->buffer = new_buffer;
    paquete->codigo_operacion = I_CREAR_PEDIDO;
    paquete->from_client = true;
    sendMessage(paquete, cCon);

}


//Añadir Plato(APP,Restaurante)
void anadirPlato(){
    /* 
    Recibe:
        Plato
        ID de pedido
    */

   /*
   typedef struct
	{
		uint32_t pedidoID;
		t_plato* plato;
	} t_I_ANADIR_PLATO;
    */

    int pedidoId,plato_precio;
    char plato_nombre[100];

    t_I_ANADIR_PLATO* datos =  malloc(sizeof(t_I_ANADIR_PLATO));
    t_plato* plato = malloc(sizeof(t_plato));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    log_info(logger,"Añadir Plato Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Plato: ");
    scanf("%s", plato_nombre);
    plato->precio = 0;
    plato->nombre = plato_nombre;
    plato->nombre_length = strlen(plato_nombre);

    datos->pedidoID = pedidoId;
    datos->plato= plato;
    
    paquete =  serializar_I_ANADIR_PLATO(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);
}


//Confirmar Pedido(APP,Restaurante,COMANDA,SINDICATO)
void confirmarPedido(){
    /* 
    Recibe:
        ID de pedido
        Restaurante (En caso de Comanda y Sindicato)
    */

    int pedidoId;
    char *restaurante = malloc(100);

    t_pedidoID_With_Restaurant* datos =  malloc(sizeof(t_pedidoID_With_Restaurant));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    log_info(logger,"Confirmar Pedido Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->pedidoID = pedidoId;
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(datos->nombreDeRes);

    //FALTA CONFIRMAR PEDIDO
    paquete =  serializar_pedido_ID_With_Restaurant(datos,I_CONFIRMAR_PEDIDO);
    paquete->from_client = true;
    log_info(logger,"aa %d \n",paquete->codigo_operacion);

    sendMessage(paquete, cCon);

}


//Plato Listo(APP,COMANDA,SINDICATO)
void platoListo(){
    /* 
    Recibe:
        Restaurante
        ID de pedido
        Comida
    */
   /*
   	typedef struct
	{
		uint32_t pedidoID;
		uint32_t nombreDeRes_length;
		char* nombreDeRes;
		uint32_t plato_length;
		char* plato;
	} t_I_PLATO_LISTO;
    */

    int pedidoId;
    char *restaurante = malloc(100);
    char* plato = malloc(100);

    //t_paquete* serializar_I_PLATO_LISTO(t_I_PLATO_LISTO* datos);
    //t_I_PLATO_LISTO* deserializar_I_PLATO_LISTO(t_paquete* paquete);
    t_I_PLATO_LISTO* datos =  malloc(sizeof(t_I_PLATO_LISTO));

    t_paquete* paquete = malloc(sizeof(t_paquete));
    log_info(logger,"Plato Listo Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    printf("\t Ingrese Plato: ");
    scanf("%s", plato);
    datos->pedidoID = pedidoId;
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(datos->nombreDeRes);
    datos->plato= plato;
    datos->plato_length =strlen(datos->plato);

    paquete =  serializar_I_PLATO_LISTO(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);
}


//Consultar Pedido(APP,Restaurante)
void consultarPedido(){
    /* 
    Recibe:
        ID de pedido
    */
    int pedidoId;
    t_pedidoID* datos =  malloc(sizeof(t_pedidoID));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    log_info(logger,"Consultar Pedido Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    datos->pedidoID = pedidoId;


    paquete =  serializar_input_Consultar_Pedido(datos);
    paquete->from_client = true;

    sendMessage(paquete, cCon);

}


//Obtener Pedido(COMANDA,SINDICATO)
void obtenerPedido(){
    /* 
    Recibe:
        Restaurante
        ID de pedido

    */

    int pedidoId;
    char *restaurante = malloc(100);

    t_pedidoID_With_Restaurant* datos =  malloc(sizeof(t_pedidoID_With_Restaurant));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    log_info(logger,"Obtener Pedido Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->pedidoID = pedidoId;
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(restaurante);

    paquete =  serializar_I_OBTENER_PEDIDO(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);
}


//Finalizar Pedido(COMANDA,Cliente)
void finalizarPedido(){
    /* 
    Recibe:
        Restaurante
        ID de pedido
    */

    int pedidoId;
    char *restaurante;

    t_pedidoID_With_Restaurant* datos =  malloc(sizeof(t_pedidoID_With_Restaurant));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    log_info(logger,"Finalizar Pedido Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", &restaurante);
    datos->pedidoID = &pedidoId;
    datos->nombreDeRes= &restaurante;
    datos->nombreDeRes_length =strlen(&restaurante);

    paquete =  serializar_I_FINALIZAR_PEDIDO(datos);
    paquete->from_client = true;


    sendMessage(paquete, cCon);

}
