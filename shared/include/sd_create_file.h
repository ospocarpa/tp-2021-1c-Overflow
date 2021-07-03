#ifndef SD_CREATE_FILE_H
#define SD_CREATE_FILE_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

t_package ser_create_file_recurso(t_create_file data_buffer);
t_package ser_create_file_bitacora(t_create_file data_buffer);
t_package ser_create_file(t_create_file data_buffer, op_code codigo_operacion);
t_create_file des_create_file(t_package paquete);
void mostrar_create_file(t_create_file data);

#endif  