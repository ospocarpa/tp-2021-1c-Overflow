#include "mi_ram_hq.h"

int main()
{

    cfg_create("cfg/mi_ram_hq.config");
    logger_create("cfg/mi_ram_hq.log", "MI_RAM_HQ");
    logger_info("Iniciando módulo Mi-RAM-HQ");

    char *ip = get_ip();
    int puerto = get_puerto();
    t_log *log = get_logger();

    logger_info("IP: %s", ip);
    logger_info("PUERTO: %d", puerto);

    server_mi_ram_iniciar(puerto, ip, log);

    // Libero el log y config al final
    cfg_free();
    logger_free();

    return 1;
}