#include "read_config_mi_ram_hq.h"

static t_config *config = NULL;

void cfg_create(char *path_config)
{
    if (config == NULL)
        config = config_create(path_config);
}

char* get_esquema_memoria()
{
    return config_get_string_value(config, "ESQUEMA_MEMORIA");
}

int get_tamanio_memoria()
{
    return config_get_int_value(config, "TAMANIO_MEMORIA");
}

int get_tamanio_swap()
{
    return config_get_int_value(config, "TAMANIO_SWAP");
}

int get_tamanio_tamanio_pagina()
{
    return config_get_int_value(config, "TAMANIO_PAGINA");
}

char * get_path_swap()
{
    return config_get_string_value(config, "PATH_SWAP");
}

int get_puerto()
{
    return config_get_int_value(config, "PUERTO");
}

char *get_ip()
{
    return config_get_string_value(config, "IP_MI_RAM");
}

char *get_esquema_memoria()
{
    return config_get_string_value(config, "ESQUEMA_MEMORIA");
}

char * get_algoritmo_de_remplazo()
{
    return config_get_string_value(config, "ALGORITMO_REEMPLAZO");
}

char * get_criterio_de_seleccion()
{
    return config_get_string_value(config, "CRITERIO_SELECCION");
}

void cfg_free()
{
    config_destroy(config);
}