#include "discordiador.h"

int main(){

    logger_create("cfg/discordiador.log", "DISCORDIADOR");
    logger_info("Iniciando módulo DISCORDIADOR");
    
    // Libero el log al final 
    logger_free();

    return 1;
}