#ifndef SD_INFORMAR_TAREA_TRIPULANTE_H
#define SD_INFORMAR_TAREA_TRIPULANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/config.h>
#include <string.h>
#include <TAD.h>
#include <sd_posicion.h>

/* ******* DISCORDIADOR ******* */
t_package ser_cod_informar_tarea_tripulante(t_short_info_tripulante data);
t_info_tarea des_res_informacion_tarea_tripulante(t_package paquete);

/* ******* MI RAM HQ ******* */
t_package ser_res_informar_tarea_tripulante(t_info_tarea data_buffer);
t_short_info_tripulante des_cod_informar_tarea_tripulante(t_package paquete);

#endif