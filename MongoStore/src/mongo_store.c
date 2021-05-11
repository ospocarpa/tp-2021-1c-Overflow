#include "mongo_store.h"

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    {
        run_tests();
    }
    else
    {
        printf("Hola mundo\n");

        //t_config* config = config_create("cfg/mongoStore.config");

        //t_log* log = iniciar_logger("cfg/mongoStore.log", "MONGO_STORE");
        //log_info(log, "Iniciando módulo i-Mongo-Store");

        //char* ip = get_ip();
        //char *puerto = get_puerto();

        //log_info(log, "IP: %s", ip);
        //log_info(log, "PUERTO: %d", puerto);

        //server_mongo_store_iniciar(puerto, ip, NULL);

        // Libero el log y config al final
        //borrar_log(log);
        //config_destroy(config);

        return 1;
    }
}