#ifndef READ_CONFIG_MI_RAM_HQ_H
#define READ_CONFIG_MI_RAM_HQ_H

#include <commons/config.h>
#include <stdlib.h>

void cfg_create(char * path_config);
int get_tamanio_memoria();
int get_puerto();
char * get_ip();
void cfg_free();

#endif