#include "discordiador.h"

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
        return EXIT_FAILURE;
    }
    else
    {
        logger_info("Conexion con Mi-RAM-HQ exitosa");
    }
    

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