#include "read_config_mi_ram_hq.h"

static t_config * config = NULL;

void cfg_create(char * path_config){
    if(config == NULL)
        config = config_create(path_config);

}

int get_tamanio_memoria(){
    return config_get_int_value(config, "TAMANIO_MEMORIA");
}

int get_puerto(){
    return config_get_int_value(config, "PUERTO");
}

char * get_ip(){
    return config_get_string_value(config, "IP_MI_RAM");
}

void cfg_free(){
    config_destroy(config);
}