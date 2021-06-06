#ifndef SD_INFORMAR_TAREA_TRIPULANTE_H
#define SD_INFORMAR_TAREA_TRIPULANTE_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

/* ******* DISCORDIADOR ******* */
t_paquete * ser_cod_informar_tarea_tripulante(int patota_id, int tripulante_id);
t_info_tarea des_res_informacion_tarea_tripulante(t_paquete * paquete);

/* ******* MI RAM HQ ******* */
t_paquete* ser_res_informar_tarea_tripulante(t_info_tarea data_buffer);
void des_cod_informar_tarea_tripulante(t_paquete* paquete, int * patota_id, int * tripulante_id);


#endif  