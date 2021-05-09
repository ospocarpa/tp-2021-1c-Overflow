#include "Cliente.h"

int main(int argc, char **argv)
{
    t_config *g_config = leer_config_file("./cfg/discordiador.config");
    t_config_discordiador *config = leerConfigDiscordiador(g_config);
    
    printf("%s\n", config->ARCHIVO_LOG);
    t_log* logger = iniciar_logger(config->ARCHIVO_LOG, "CLIENTE");
    int conexion_servidor = crear_conexion(config->IP_MODULO, config->PUERTO_MODULO, logger);

    Tarea* tarea = malloc(sizeof(Tarea));
    tarea->patota_id = 1;
    tarea->description = "test";
    tarea->description_length = strlen(tarea->description);
    tarea->parametros = "test 2";
    tarea->parametros_length = strlen(tarea->parametros);
    tarea->tiempo = 3;
    tarea->posicion = malloc(sizeof(Posicion));
    tarea->posicion->posx=1;
    tarea->posicion->posy=2;

    t_paquete *paquete = serializar_I_TAREA(tarea);
    sendMessage(paquete, conexion_servidor);
    return 0;
}