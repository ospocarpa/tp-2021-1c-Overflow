#include "conexion_modulos.h"

/*
char* IP_COMANDA;
    int PUERTO_COMANDA;
    char* IP_RESTAURANTE;
    int PUERTO_RESTAURANTE;
    char* IP_SINDICATO;
    int PUERTO_SINDICATO;
    char* IP_APP;
    int PUERTO_APP;
    char* ARCHIVO_LOG;
    int POCISION_X;
    int POCISION_Y;
*/

int conectarOtroModulo(t_config_cliente *config, t_log *logger)
{
    char *ip = config->IP;
    char *puerto = config->PUERTO;
    printf("%s %d\n", config->IP, config->PUERTO);
    int conexion = crear_conexion(ip, puerto, logger);
}

void *recibirNotificaciones(void *args)
{
    while (1)
    {
        //log_info(logger, "Paso 6");
        //INPUT_HANDSHAKE=20,			//Input HandShake
        //OUTPUT_HANDSHAKE=21         //Output HandShake
        t_paquete *paquete = recibir_mensaje(cliente_fd);
        if (paquete->codigo_operacion > 0)
        {
             recepcionMensaje(paquete, logger);
        }
    }

    return NULL;
}

/*
int conectarApp(t_config_cliente * config, t_log* logger){
    char *ip = config->IP_APP;
    char *puerto = config->PUERTO_APP;
    return crear_conexion(ip, puerto, logger);
}
int conectarComanda(t_config_cliente * config, t_log* logger){
    char *ip = config->IP_COMANDA;
    char *puerto = config->PUERTO_COMANDA;
    return crear_conexion(ip, puerto, logger);
}
int conectarRestaurante(t_config_cliente * config, t_log* logger){
    char *ip = config->IP_RESTAURANTE;
    char *puerto = config->PUERTO_RESTAURANTE;
    return crear_conexion(ip, puerto, logger);
}
int conectarSindicato(t_config_cliente * config, t_log* logger){
    char *ip = config->IP_SINDICATO;
    char *puerto = config->PUERTO_SINDICATO;
    return crear_conexion(ip, puerto, logger);
}
*/