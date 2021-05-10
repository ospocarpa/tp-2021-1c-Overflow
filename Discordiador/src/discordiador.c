#include "discordiador.h"

void iniciar_servidor_main(){
    //Carga de los archivos de configuracion
    t_config *g_config = leer_config_file("./cfg/discordiador.config");
    t_config_discordiador* config = leerConfigDiscordiador(g_config);
    
    //Iniciar Log
    logger = iniciar_logger(config->ARCHIVO_LOG, "SERVIDOR");
    log_info(logger, "CONFIGURACION CARGADA!");
    
    //Iniciar Server
    int server_fd = iniciar_servidor(config->PUERTO_MODULO);
    log_info(logger, "INICIANDO SERVIDOR");

    pthread_t threadConsola;
    pthread_create(&threadConsola, NULL, (void *)mostrar_consola, NULL);
    pthread_detach(threadConsola);
    int cliente_fd;
    while (1)
    {
        cliente_fd = esperar_cliente(server_fd);

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
    // t_config * config = leer_config_file("cfg/discordiador.config");
    // t_config_discordiador* cfg_discordiador = leerConfigDiscordiador(config);
    logger_create("cfg/discordiador.log", "DISCORDIADOR");
    logger_info("Iniciando módulo DISCORDIADOR");
    
    t_log * log = get_logger();

    int conexion_mi_ram = crear_conexion("127.0.0.1", 5002); 

    if(conexion_mi_ram < 0)
    {
        logger_error("Conexion Mi-RAM fallida");
        liberar_conexion(conexion_mi_ram);
        //return EXIT_FAILURE;
    }
    else
    {
        logger_info("Conexion con Mi-RAM-HQ exitosa");
    }
    

    iniciar_servidor_main();

    while (1)
    {
        //aca van los mensaje a enviar a mi-ram
        send(conexion_mi_ram,"Hola",4,0);//ejemplo, luego eliminar
    }
    
    // Libero el log y config al final 
    logger_free();
    liberar_conexion(conexion_mi_ram);


    run_tests();
    return 1;
}