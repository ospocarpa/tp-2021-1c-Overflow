#include "../include/sd_fcsk.h"

t_package ser_fcsk(t_aviso_fsck data_buffer){
    t_package paquete;
    int tam_buffer = 0;
    paquete.buffer = malloc(tam_buffer); 
    paquete.cod_operacion = INICIO_FSCK;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    return paquete;
}

t_aviso_fsck des_fcsk(t_package paquete){
    t_aviso_fsck data;
    return data;
}

void mostrar_fsck(t_aviso_fsck data){
}