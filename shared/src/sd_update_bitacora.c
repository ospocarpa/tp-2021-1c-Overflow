#include "../include/sd_update_bitacora.h"

t_package ser_update_bitacora(t_file data_buffer){
    t_package paquete = ser_get_file(data_buffer, UPDATE_BITACORA);
    return paquete;
}


t_file des_update_bitacora(t_package paquete){
    t_file data = des_get_file(paquete);
    return data;
}

void mostrar_update_bitacora(t_file data){
    mostrar_file(data);
}