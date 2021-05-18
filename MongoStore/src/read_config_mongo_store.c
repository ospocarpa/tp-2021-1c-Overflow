#include "read_config_mongo_store.h"

static t_config *config = NULL;

void cfg_create(char *path_config)
{
    if (config == NULL)
        config = config_create(path_config);
}

char* get_punto_de_montaje()
{
    return config_get_string_value(config, "PUNTO_MONTAJE");
}

char* get_ip()
{
    return "127.0.0.1";
}

int get_puerto()
{
    return config_get_int_value(config, "PUERTO");
}

int get_tiempo_sincronizacion()
{
    return config_get_int_value(config, "TIEMPO_SINCRONIZACION");
}

t_list* get_posiciones_sabotaje()
{
    return config_get_array_value(config, "POSICIONES_SABOTAJE");
}

void cfg_free()
{
    config_destroy(config);
}