#ifndef SD_SABOTAJE_H
#define SD_SABOTAJE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/config.h>
#include <string.h>
#include <TAD.h>
#include <sd_posicion.h>

t_sabotaje *deserializar_I_SABOTAJE(t_package paquete);
t_package serializar_I_SABOTAJE(t_sabotaje *input);
void mostrarSabotaje(t_sabotaje *sabotaje);

#endif
