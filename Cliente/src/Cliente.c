#include "Cliente.h"

int main(int argc, char **argv)
{
    t_config *g_config = leer_config_file("./cfg/cliente.config");
    t_config_cliente *config = leerConfigCliente(g_config);
    
    printf("%s\n", config->ARCHIVO_LOG);
    t_log* logger = iniciar_logger(config->ARCHIVO_LOG, "CLIENTE");
    int conexion_servidor = crear_conexion(config->IP_CLIENTE, config->PUERTO, logger);

    t_nombreDeRes *solicitud = malloc(sizeof(t_nombreDeRes));
    solicitud->nombreDeRes = "Ejemplo";
    solicitud->nombreDeRes_length = strlen(solicitud->nombreDeRes);
    t_paquete *paquete = serializar_I_OBTENER_RESTAURANTE(solicitud);
    sendMessage(paquete, conexion_servidor);
    return 0;
}