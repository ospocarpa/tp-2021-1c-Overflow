#include "Cliente_Sindicato.h"




void terminarPedido(){
    /*
    typedef struct
	{
		uint32_t pedidoID;
		uint32_t nombreDeRes_length;
		char* nombreDeRes;
	} t_pedidoID_With_Restaurant;
    */
    int pedidoId;
    char *restaurante = malloc(100);

    t_pedidoID_With_Restaurant* datos = malloc(sizeof(t_pedidoID_With_Restaurant));
    t_paquete* paquete = malloc(sizeof(t_paquete));

   
    //Lo serializo

    log_info(logger,"Terminar Pedido Elegido");
    printf("\t Ingrese Id Pedido: ");
    scanf("%d", &pedidoId);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->pedidoID = pedidoId;
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(restaurante);

    paquete =  serializar_I_TERMINAR_PEDIDO(datos);
    paquete->from_client = true;
    //sendMessage(paquete, cCon);
    //Va para el Sindicato, pero mando al restaurante para testing
    sendMessage(paquete, cCon);
}

void obtenerReceta(){
    t_I_OBTENER_RECETA* nombre_receta = malloc(sizeof(t_I_OBTENER_RECETA));
    nombre_receta->plato = malloc(100);

    printf("\t Ingrese nombre de receta: ");
    scanf("%s", nombre_receta->plato);

    
    //nombre_receta->plato = plato;
    nombre_receta->plato_length = strlen(nombre_receta->plato);

    t_paquete* paquete = serializar_I_OBTENER_RECETA(nombre_receta);
    paquete->from_client = true;
    log_info(logger,"Obtener Receta Elegido");

    sendMessage(paquete, cCon);

}