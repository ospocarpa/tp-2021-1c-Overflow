#ifndef READ_CONFIG_MI_RAM_HQ_H
#define READ_CONFIG_MI_RAM_HQ_H

#include <commons/config.h>
#include <stdlib.h>

void cfg_create(char * path_config);
int get_tamanio_memoria();
int get_puerto();
char * get_ip();
int get_tamanio_swap();
int get_tamanio_tamanio_pagina();
char * get_path_swap();
char *get_esquema_memoria();
char * get_algoritmo_de_remplazo();
char * get_criterio_de_seleccion();
void cfg_free();

#endif