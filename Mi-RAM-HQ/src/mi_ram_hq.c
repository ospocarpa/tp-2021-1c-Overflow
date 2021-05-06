#include "mi_ram_hq.h"

int main(){

    logger_create("cfg/mi_ram_hq.log", "MI_RAM_HQ");
    logger_info("Iniciando módulo Mi-RAM-HQ");
    
    // Libero el log al final 
    logger_free();

    return 1;
}