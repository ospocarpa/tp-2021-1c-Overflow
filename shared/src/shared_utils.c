#include "../include/shared_utils.h"
#include <string.h>

//Funcion de ejemplo del git de VSCODE
char* mi_funcion_compartida(){
    return "Hice uso de la shared!";
}

t_log* iniciar_logger(char* logfile, char* logtag) {
	return log_create(logfile, logtag, 1, LOG_LEVEL_INFO);
}

void escribir_log_info(t_log* logger, char* textoppal, char* variable){
    log_info(logger, textoppal, variable);
}
void escribir_log_warning(t_log* logger, char* textoppal, char* variable){
    log_warning(logger,textoppal,variable);
}
void escribir_log_error(t_log* logger, char* textoppal, char* variable){
     log_error(logger,textoppal,variable);
}

void borrar_log(t_log* logger){
    log_destroy(logger);
}
