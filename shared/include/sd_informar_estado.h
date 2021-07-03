#ifndef SD_INFORMAR_ESTADO_H
#define SD_INFORMAR_ESTADO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <TAD.h>
#include <commons/string.h>

/* ******* DISCORDIADOR ******* */
t_package ser_cod_informar_estado(t_estado_tripulante data_buffer);

/* ******* MI RAM HQ ******* */
t_estado_tripulante des_cod_informar_estado(t_package paquete);

#endif