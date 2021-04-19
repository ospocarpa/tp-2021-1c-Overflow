#include "Cliente_App.h"


void seleccionarRestaurantes(){
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
        */
    char cliente[100],restaurante[100];
    t_I_SELECCIONAR_RESTAURANTE* datos = malloc(sizeof(t_I_SELECCIONAR_RESTAURANTE));;

    log_info(logger,"Seleccionar Restaurante Elegido");
    printf("\t Ingrese Cliente: ");
    scanf("%s", cliente);
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->cliente = cliente;
    datos->cliente_length =strlen(cliente);
    datos->restaurante= restaurante;
    datos->restaurante_length =strlen(restaurante);

    t_paquete* paquete = malloc(sizeof(t_paquete));
    paquete = serializar_I_SELECCIONAR_RESTAURANTE(datos);
    paquete->from_client = true;
    //sendMessage(paquete, cCon);
    //Va para la app, pero mando al restaurante para testing
    sendMessage(paquete, cCon);

    //t_paquete* serializar_I_SELECCIONAR_RESTAURANTE(t_I_SELECCIONAR_RESTAURANTE* datos);
    //output es respuesta bool


};