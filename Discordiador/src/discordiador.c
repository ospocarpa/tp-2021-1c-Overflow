#include "discordiador.h"

void iniciar_servidor_main()
{
    //Iniciar dispatcher
    pthread_t threadDispatcher;
    pthread_create(&threadDispatcher, NULL, (void *)init_dispatcher, NULL);
    pthread_detach(threadDispatcher);
    //Iniciar init_bloqueados()
    pthread_t threadDispatcher_bloq;
    pthread_create(&threadDispatcher_bloq, NULL, (void *)init_bloqueados, NULL);
    pthread_detach(threadDispatcher_bloq);

    //Iniciar Server
    int server_fd = iniciar_servidor(config->PUERTO_MODULO);
    log_info(logger, "INICIANDO SERVIDOR");
    pthread_t threadConsola;
    pthread_create(&threadConsola, NULL, (void *)leer_consola, NULL);
    pthread_detach(threadConsola);
    int cliente_fd;

    while (1)
    {

        cliente_fd = esperar_cliente(server_fd);

        pthread_t threadEscucha;
        pthread_create(&threadEscucha, NULL, (void *)ejecutar_operacion, cliente_fd);
        pthread_detach(threadEscucha); //corregir esto
        //mandar a este hilo a ejecutar las accione pertinentes
        //consola debe ser mas de mostrar mensajes
    }
}

void ejecutar_operacion(int cliente_fd)
{
    while (1)
    {
        t_package paquete = recibir_mensaje(cliente_fd);
        if (paquete.cod_operacion > 0 && paquete.cod_operacion < 100)
        {

            recepcionMensaje(paquete, cliente_fd, logger);
            if (paquete.cod_operacion == 0)
                exit; //exit sin efecto
        }
        else
        {
            break;
        }
    }
}

void inicializacion_recursos()
{
    // Inicializo semaforo
    pthread_mutex_init(&MXTRIPULANTE, NULL);    //Usado en la insercción del tripulante
    pthread_mutex_init(&mutex_bloqueado, NULL); //Usado porque solo tengo un i/o

    //mejorar en metodo la iniciliazicion del semaforo
    pthread_mutex_init(&SEM_PAUSAR_PLANIFICACION, 0);
    //printf(" sem : %d\n", SEM_PAUSAR_PLANIFICACION);
    sem_init(&listos, 0, 0);     // contador de listos =0
    sem_init(&bloqueados, 0, 0); // contador de bloqueados =0
    sem_init(&grado_multiprocesamiento, 0, config->GRADO_MULTITAREA);
    sem_init(&activados, 0, 0);
    cantidad_activos = 0;
    hay_sabotaje = false;
    // mutex_unlock (semafor) --> 0
    /* pthread_mutex_unlock(&SEM_PAUSAR_PLANIFICACION);
    printf("%d\n", SEM_PAUSAR_PLANIFICACION);
    pthread_mutex_lock(&SEM_PAUSAR_PLANIFICACION);
    printf("%d\n", SEM_PAUSAR_PLANIFICACION); */
    // pthread_mutex_init(&MXMENSAJE, NULL);
    // pthread_mutex_lock(&MXMENSAJE);

    //Iniciando listas
    //list_create(lista_NEW);
    lista_tripulantes = list_create();
    lista_READY = list_create();
    lista_EXEC = list_create();
    lista_BLOCKIO = list_create();
    lista_BLOCKEMERGENCIA = list_create();
    lista_EXIT = list_create();
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    { //Carga de los archivos de configuracion
        t_config *g_config = leer_config_file(PATH_CONFIG);
        config = leerConfigDiscordiador(g_config);
        run_tests();
    }
    else
    {
        //Carga de los archivos de configuracion
        t_config *g_config = leer_config_file(PATH_CONFIG);
        config = leerConfigDiscordiador(g_config);

        /*init_dispatcher();
        return 1;*/

        //Iniciar Log
        logger = iniciar_logger(config->ARCHIVO_LOG, "SERVIDOR");
        log_info(logger, "CONFIGURACION CARGADA!");
        inicializacion_recursos();

        int conexion_mi_ram = crear_conexion(config->IP_MI_RAM_HQ, config->PUERTO_MI_RAM_HQ);
        // printf("ip mi ram :%s  puerto:%d\n", config->IP_MI_RAM_HQ, config->PUERTO_MI_RAM_HQ);
        if (conexion_mi_ram < 0)
        {
            log_error(logger, "Conexion Mi-RAM fallida");
            liberar_conexion(conexion_mi_ram);
            // return EXIT_FAILURE; //despues descomitear
        }
        else
        {
            log_info(logger, "Conexion con Mi-RAM-HQ exitosa");
        }

        iniciar_servidor_main();

        printf("sali de  inciar servidor\n");

        // Libero el log y config al final
        logger_free();

        liberar_conexion(conexion_mi_ram);
        printf("termino la ejecucion de discordiador\n");
        config_destroy(config);
        config_destroy(g_config);
        return 1;
    }
}