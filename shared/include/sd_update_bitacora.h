#ifndef SD_UPDATE_BITACORA_H
#define SD_UPDATE_BITACORA_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>
#include "sd_get_file.h"

    t_package ser_update_bitacora(t_file data_buffer);
    t_file des_update_bitacora(t_package paquete);
    void mostrar_update_bitacora(t_file data);

#endif  