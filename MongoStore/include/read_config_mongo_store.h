#ifndef READ_CONFIG_MONGO_STORE_H
#define READ_CONFIG_MONGO_STORE_H

#include <commons/config.h>
#include <stdlib.h>
#include "TAD.h"

void cfg_create(char * path_config);
char* get_punto_de_montaje();
char* get_ip();
int get_puerto();
int get_tiempo_sincronizacion();
t_list* get_posiciones_sabotaje();
void cfg_free();

#endif