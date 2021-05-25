#include "mongo_store.h"

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    {
        run_tests();
        return 1;
    }

    signal(SIGUSR1, method_sigusr1);
    t_config *g_config = leer_config_file("./cfg/mongo_store.config");
    config = leer_config_mongo_store(g_config);
   
    //Iniciar Log
    logger = iniciar_logger(config->ARCHIVO_LOG, "SERVIDOR");
    log_info(logger, "Iniciando módulo i-Mongo-Store");
    
    pthread_t thread_init_mongo_store;
    pthread_create(&thread_init_mongo_store, NULL, (void *)init_mongo_store, NULL);
    pthread_detach(thread_init_mongo_store);

    int puerto = config->PUERTO;
    server_mongo_store_iniciar(puerto);

    return 1;
}