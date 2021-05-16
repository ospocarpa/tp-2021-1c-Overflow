#include "mongo_store.h"

int main()
{
    printf("Hola mundo\n");

    cfg_create("cfg/mongo_store.config");
    logger_create("cfg/mongo_store.log", "MONGO_STORE");
    logger_info("Iniciando módulo i-Mongo-Store");
    
    int puerto = get_puerto();
    server_mongo_store_iniciar(puerto);


    cfg_free();
    logger_free();

    return 1;
}