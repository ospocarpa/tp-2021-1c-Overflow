#include "../include/sd_operation_file_recurso.h"

t_package ser_agregar_recurso(t_operation_file_recurso data_buffer){
    t_package paquete = ser_operation_file_recurso(data_buffer, AGREGAR_RECURSO);
    return paquete;
}

t_package ser_retirar_recurso(t_operation_file_recurso data_buffer){
    t_package paquete = ser_operation_file_recurso(data_buffer, RETIRAR_RECURSO);
    return paquete;
}

t_package ser_eliminar_recurso(t_operation_file_recurso data_buffer){
    t_package paquete = ser_operation_file_recurso(data_buffer, ELIMINAR_RECURSO);
    return paquete;
}

t_package ser_operation_file_recurso(t_operation_file_recurso data_buffer, op_code codigo_operacion){
    t_package paquete;
    int tam_buffer = sizeof(uint32_t)*2 + sizeof(char) + data_buffer.long_nombre_file;
    paquete.buffer = malloc(tam_buffer); 
    paquete.cod_operacion = codigo_operacion;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer + offset, &data_buffer.cantidad, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, &data_buffer.caracter, sizeof(char));
	offset += sizeof(char);

    memcpy(paquete.buffer + offset, &data_buffer.long_nombre_file, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    
    memcpy(paquete.buffer + offset, data_buffer.nombre_file, data_buffer.long_nombre_file);
	offset += data_buffer.long_nombre_file;

    return paquete;
}

t_operation_file_recurso des_operation_file_recurso(t_package paquete){
    t_operation_file_recurso data;
    void *buffer = paquete.buffer;
    memcpy( &data.cantidad, buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t);
    memcpy( &data.caracter, buffer, sizeof(char));
    buffer += sizeof(char);
    memcpy( &data.long_nombre_file, buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t);

    data.nombre_file = malloc(data.long_nombre_file + 1);
    memcpy( data.nombre_file, buffer, data.long_nombre_file);
    data.nombre_file[data.long_nombre_file] = '\0';

    return data;
}

void mostrar_operation_file_recurso(t_operation_file_recurso data){
    printf("Cantidad: %d\n", data.cantidad);
    printf("Caracter: %c\n", data.caracter);
    printf("Long nombre de archivo: %d\n", data.long_nombre_file);
    printf("Nombre de archivo: %s\n\n", data.nombre_file);
}