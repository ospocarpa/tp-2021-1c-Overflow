#ifndef SD_TAREA_H
#define SD_TAREA_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

    Tarea* deserializar_I_TAREA(t_paquete* paquete);
    t_paquete* serializar_I_TAREA(Tarea* input);

#endif