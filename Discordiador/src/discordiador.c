#include "discordiador.h"

void iniciar_servidor_main(){
    //Carga de los archivos de configuracion
    t_config *g_config = leer_config_file("./cfg/discordiador.config");
    t_config_discordiador* config = leerConfigDiscordiador(g_config);
    
    //Iniciar Log
    logger = iniciar_logger(config->ARCHIVO_LOG, "SERVIDOR");
    log_info(logger, "CONFIGURACION CARGADA!");
    
    //Iniciar Server
    int server_fd = iniciar_servidor(config->IP_MODULO, string_itoa(config->PUERTO_MODULO), logger);
    log_info(logger, "INICIANDO SERVIDOR");

    pthread_t threadConsola;
    pthread_create(&threadConsola, NULL, (void *)mostrar_consola, NULL);
    pthread_detach(threadConsola);
    int cliente_fd;
    while (1)
    {
        cliente_fd = esperar_cliente(server_fd, logger);

        pthread_t threadEscucha;
        pthread_create(&threadEscucha,NULL,(void*)ejecutar_operacion, cliente_fd);
        pthread_detach(threadEscucha);

    }
    //run_tests();
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

int main(){
    iniciar_servidor_main();
    return 1;
}