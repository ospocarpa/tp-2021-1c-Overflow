#ifndef SD_FCSK_H
#define SD_FCSK_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

    t_package ser_fcsk(t_aviso_fsck data_buffer);
    t_package ser_fin_fcsk(t_aviso_fsck data_buffer);
    t_aviso_fsck des_fcsk(t_package paquete);
    void mostrar_fsck(t_aviso_fsck data);

#endif  