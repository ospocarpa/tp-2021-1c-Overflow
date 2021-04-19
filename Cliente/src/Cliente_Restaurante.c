#include "Cliente_Restaurante.h"




void consultarRestaurante(){

    log_info(logger,"Consultar Restaurante Elegido");
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));
    new_buffer->size = 1;
    void* stream = malloc(new_buffer->size);
    new_buffer->stream = stream;
    paquete->buffer = new_buffer;
    paquete->codigo_operacion = I_CONSULTAR_RESTAURANTE;
    paquete->from_client = true;
    sendMessage(paquete, cCon);
    //t_paquete* serializar_O_CONSULTAR_RESTAURANTE(t_O_CONSULTAR_RESTAURANTE* datos);
    //t_O_CONSULTAR_RESTAURANTE* deserializar_O_CONSULTAR_RESTAURANTE(t_paquete* paquete);
};


//Obtener Restaurante
void obtenerRestaurante(){

    char restaurante[100];
    t_nombreDeRes* datos = malloc(sizeof(t_nombreDeRes));;

    log_info(logger,"Obtener Restaurante Elegido");
    printf("\t Ingrese Restaurante: ");
    scanf("%s", restaurante);
    datos->nombreDeRes= restaurante;
    datos->nombreDeRes_length =strlen(restaurante);

    t_paquete* paquete = malloc(sizeof(t_paquete));
    paquete = serializar_I_OBTENER_RESTAURANTE(datos);
    paquete->from_client = true;
    sendMessage(paquete, cCon);
}