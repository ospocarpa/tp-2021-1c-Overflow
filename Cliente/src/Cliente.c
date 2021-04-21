#include "Cliente.h"

/*
typedef struct {
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
} t_config_cliente;
*/
int main(int argc, char **argv)
{
    printf(test());printf("\n");
    return 0;
    /*if (argc > 1 && strcmp(argv[1], "-test") == 0)
        run_tests();
    else
    {
        handshake_regreso = malloc(sizeof(t_handshake_output));

        g_config = leer_config_file("./cfg/cliente.config");
        config_cliente = leerConfigCliente(g_config);
        logger = log_create("./cfg/Cliente1.log", "CLIENTE", 1, LOG_LEVEL_INFO);
        //logger = log_create("./cfg/Cliente1.log", "CLIENTE", 0, LOG_LEVEL_INFO);   //Es el que va
        
        int server_fd = iniciar_servidor(cIP, string_itoa(PUERTO), logger);
        log_info(logger, "INICIANDO SERVIDOR %d", server_fd);

        //printf("%s %s\n", cIP, string_itoa(PUERTO));
        cCon = conectarOtroModulo(config_cliente, logger);

        if (cCon == -1)
        {
            log_error(logger, "Error Conectando al otro Modulo");
            return -1;
        }
        enviarHandshake(config_cliente, cIP, PUERTO, cCon, logger);
        cliente_fd = esperar_cliente(server_fd, logger);
        while (1)
        {
            t_paquete *paquete = recibir_mensaje(cliente_fd);
            if (paquete->codigo_operacion > 0)
            {
                log_info(logger, "codigo %d", paquete->codigo_operacion);
                if (paquete->codigo_operacion == OUTPUT_HANDSHAKE)
                {
                    log_info(logger, "Recibo respuesta Handshake");
                    handshake_regreso = deserializar_handshake_output(paquete);
                    printf("Mod %s \n", handshake_regreso->Modulo);
                    break;
                }
            }
            else
            {
                break;
            }
        }

        pthread_t thread2_notificaciones;

        pthread_create(&thread2_notificaciones, NULL, &recibirNotificaciones, NULL);

        pthread_t thread1_id;

        pthread_create(&thread1_id, NULL, &iniciarConsola, NULL);
        pthread_join(thread1_id, NULL);

        liberar_conexion(cCon);

        return 1;
        return EXIT_SUCCESS;
    }*/
}