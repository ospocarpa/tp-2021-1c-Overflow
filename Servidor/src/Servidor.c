#include "controller.h"
#include "Servidor.h"

int main(int argc, char **argv)
{
    //Carga de los archivos de configuracion
    t_config *g_config = leer_config_file("./cfg/servidor.config");
    config = leerConfigTemplate(g_config);
    
    //Iniciar Log
    logger = iniciar_logger(config->ARCHIVO_LOG, "SERVIDOR");
    log_info(logger, "CONFIGURACION CARGADA!");
    
    
    //Iniciar Server
    int server_fd = iniciar_servidor(config->IP_SERVIDOR, string_itoa(config->PUERTO_ESCUCHA), logger);
    log_info(logger, "INICIANDO SERVIDOR");

    pthread_t threadMessage;
    pthread_create(&threadMessage, NULL, (void *)init_message, NULL);
    pthread_detach(threadMessage);

    int cliente_fd;
    while (1)
    {
        cliente_fd = esperar_cliente(server_fd, logger);

        pthread_t threadEscucha;
        pthread_create(&threadEscucha,NULL,(void*)ejecutar_operacion, cliente_fd);
        pthread_detach(threadEscucha);

    }
}

void init_message(){
    //Inicio de otra acción
}

void ejecutar_operacion(int cliente_fd)
{
    while (1)
    {
        t_paquete *paquete = recibir_mensaje(cliente_fd);
        if (paquete->codigo_operacion > 0 && paquete->codigo_operacion < 100)
        {

            recepcionMensaje(paquete, cliente_fd, logger);
            if (paquete->codigo_operacion == 0) exit;
        }
        else
        {
            break;
        }
    }
}