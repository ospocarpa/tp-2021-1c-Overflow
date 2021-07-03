#ifndef SD_GET_FILE_H
#define SD_GET_FILE_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

    t_package ser_get_file_recurso(t_file data_buffer);
    t_package ser_get_file_bitacora(t_file data_buffer);
    t_package ser_get_file(t_file data_buffer, op_code codigo_operacion);
    t_file des_get_file(t_package paquete);
    void mostrar_file(t_file data);

#endif  