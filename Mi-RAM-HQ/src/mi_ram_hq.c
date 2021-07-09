#include "mi_ram_hq.h"

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    {
        run_tests();
    }
    else
    {
        cfg_create("cfg/mi_ram_hq.config");
        logger_create("cfg/mi_ram_hq.log", "MI_RAM_HQ");
        logger_info("Iniciando módulo Mi-RAM-HQ");

        int puerto = get_puerto();
        /*  char *ip = get_ip();
        printf("ip :%s  puerto:%d\n", ip, puerto); */
        server_mi_ram_iniciar(puerto);

        // Libero el log y config al final
        cfg_free();
        logger_free();

        return 1;
    }
}