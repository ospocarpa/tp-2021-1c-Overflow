#include "../include/sd_create_file.h"

t_package ser_create_file_recurso(t_create_file data_buffer){
    t_package paquete = ser_create_file(data_buffer, CREAR_RECURSO);
    return paquete;
}

t_package ser_create_file_bitacora(t_create_file data_buffer){
    t_package paquete = ser_create_file(data_buffer, CREAR_BITACORA);
    return paquete;
}

t_package ser_create_file(t_create_file data_buffer, op_code codigo_operacion){
    t_package paquete;
    int tam_buffer = sizeof(char) + sizeof(int) + data_buffer.long_nombre_file;
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion = codigo_operacion;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer + offset, &data_buffer.caracter, sizeof(char));
	offset += sizeof(char);
    
    memcpy(paquete.buffer + offset, &data_buffer.long_nombre_file, sizeof(int));
	offset += sizeof(int);

    memcpy(paquete.buffer + offset, data_buffer.nombre_file, data_buffer.long_nombre_file);
	offset += data_buffer.long_nombre_file;
    
    return paquete;
}

t_create_file des_create_file(t_package paquete){
    t_create_file data;
    void *buffer = paquete.buffer;
    memcpy( &data.caracter, buffer, sizeof(char));
    buffer += sizeof(char);
    memcpy( &data.long_nombre_file, buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t);
    data.nombre_file = malloc(data.long_nombre_file + 1);
    memcpy( data.nombre_file, buffer, data.long_nombre_file);
    buffer += data.long_nombre_file;

    data.nombre_file[data.long_nombre_file] = '\0';

    return data;
}

void mostrar_create_file(t_create_file data){
    printf("Caracter: %c\n", data.caracter);
    printf("Longitud: %d\n", data.long_nombre_file);
    printf("Nombre de archivo: %s\n\n", data.nombre_file);
}