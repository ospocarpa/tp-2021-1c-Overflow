#include "../include/sd_get_file.h"

t_package ser_get_file_recurso(t_file data_buffer){
    t_package paquete = ser_get_file(data_buffer, GET_RECURSO);
    return paquete;
}

t_package ser_get_file_bitacora(t_file data_buffer){
    t_package paquete = ser_get_file(data_buffer, GET_BITACORA);
    return paquete;
}

t_package ser_get_file(t_file data_buffer, op_code codigo_operacion){
    t_package paquete;
    int tam_buffer = sizeof(uint32_t)*2 + data_buffer.long_nombre_file + data_buffer.long_contenido;
    paquete.buffer = malloc(tam_buffer); 
    paquete.cod_operacion = codigo_operacion;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer + offset, &data_buffer.long_contenido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    
    memcpy(paquete.buffer + offset, data_buffer.contenido, data_buffer.long_contenido);
	offset += data_buffer.long_contenido;
    
    memcpy(paquete.buffer + offset, &data_buffer.long_nombre_file, sizeof(uint32_t));
	offset += sizeof(uint32_t);

    memcpy(paquete.buffer + offset, data_buffer.nombre_file, data_buffer.long_nombre_file);
	offset += data_buffer.long_nombre_file;

    return paquete;
}

t_file des_get_file(t_package paquete){
    t_file data;
    void *buffer = paquete.buffer;
    memcpy( &data.long_contenido, buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t);
    data.contenido = malloc(data.long_contenido + 1);
    memcpy( data.contenido, buffer, data.long_contenido);
    data.contenido[data.long_contenido] = '\0';

    buffer += data.long_contenido;
    memcpy( &data.long_nombre_file, buffer, sizeof(uint32_t));
    buffer += sizeof(uint32_t);
    data.nombre_file = malloc(data.long_nombre_file + 1);
    memcpy( data.nombre_file, buffer, data.long_nombre_file);
    data.nombre_file[data.long_nombre_file] = '\0';
    buffer += data.long_nombre_file;
    return data;
}

void mostrar_file(t_file data){
    printf("Long_contenido: %d\n", data.long_contenido);
    printf("Contenido: %s\n", data.contenido);
    printf("Long nombre de archivo: %d\n", data.long_nombre_file);
    printf("Nombre de archivo: %s\n\n", data.nombre_file);
}