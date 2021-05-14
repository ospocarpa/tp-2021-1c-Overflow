#ifndef SD_SABOTAJE.H
#define SD_SABOTAJE.H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

    Sabotaje* deserializar_I_SABOTAJE(t_paquete* paquete);
    t_paquete* serializar_I_SABOTAJE(Sabotaje* input);

#endif
