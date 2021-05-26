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


t_paquete* serializar_informar_tarea_tripulante(t_informar_tarea_tripulante data_buffer);
t_informar_tarea_tripulante deserializar_informar_tarea_tripulante(t_paquete* paquete);


#endif  