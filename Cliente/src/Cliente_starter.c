#include "Cliente_starter.h"

char* cIP = "127.0.0.1";
int PUERTO = 4242;
int moduloActual = 0;
int cliente_fd =0;
t_handshake_output* handshake_regreso = NULL;
void enviarHandshake(t_config_cliente * config,char* IP, int Puerto, int conexion, t_log* logger){

    log_info(logger,"Enviando Handshake a modulo destino");

    t_handshake_input* datos =  malloc(sizeof(t_handshake_input));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    printf("%s\n", config->IP_CLIENTE);
    datos->IP = config->IP_CLIENTE;
    datos->IP_length = strlen(datos->IP);
    //printf("ip1 %s\n",datos->IP);

    //printf("ip2 %s\n",IP);
    //printf("%d",strlen(datos->IP));
    
    datos->Puerto = Puerto;
    datos->Modulo = "Cliente";
    datos->Modulo_length = strlen(datos->Modulo);
    datos->POS_X = config->POSICION_X;
    datos->POS_Y = config->POSICION_Y;
    datos->Id_modulo = config->ID_CLIENTE;
    datos->Id_modulo_length = strlen(config->ID_CLIENTE);

/*
    log_warning(logger,"IP %s",datos->IP);
    log_warning(logger,"IP l %d",datos->IP_length);
    log_warning(logger,"Puerto %d",datos->Puerto);
    log_warning(logger,"PosX %d",datos->POS_X);
    log_warning(logger,"PosY %d",datos->POS_Y);
    log_warning(logger,"Mod %s",datos->Modulo);
    log_warning(logger,"Mod l %d",datos->Modulo_length);
    log_warning(logger,"Id %s",datos->Id_modulo);
    log_warning(logger,"Id l %d",datos->Id_modulo_length);
 */    
    log_info(logger, "enviando HandShake");
    //FALTA CONFIRMAR PEDIDO
    paquete =  serializar_handshake_input(datos);
    paquete->from_client = true;

    log_info(logger,"Codigo que mando %d",paquete->codigo_operacion);
    sendMessage(paquete, cCon);

}