#ifndef SD_OPERATION_FILE_RECURSO_H
#define SD_OPERATION_FILE_RECURSO_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

    t_package ser_agregar_recurso(t_operation_file_recurso data_buffer);
    t_package ser_retirar_recurso(t_operation_file_recurso data_buffer);
    t_package ser_eliminar_recurso(t_operation_file_recurso data_buffer);
    t_package ser_operation_file_recurso(t_operation_file_recurso data_buffer, op_code codigo_operacion);
    t_operation_file_recurso des_operation_file_recurso(t_package paquete);
    void mostrar_operation_file_recurso(t_operation_file_recurso data);

#endif  