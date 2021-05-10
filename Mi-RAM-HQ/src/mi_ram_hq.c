#include "mi_ram_hq.h"

int main()
{

    cfg_create("cfg/mi_ram_hq.config");
    logger_create("cfg/mi_ram_hq.log", "MI_RAM_HQ");
    logger_info("Iniciando módulo Mi-RAM-HQ");

    int puerto = get_puerto();

    server_mi_ram_iniciar(puerto);

    // Libero el log y config al final
    cfg_free();
    logger_free();

    return 1;
}