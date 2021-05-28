#ifndef SD_EXPULSAR_TRIPULANTE_H
#define SD_EXPULSAR_TRIPULANTE_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>


t_paquete * serializar_expulsar_tripulante(t_expulsar_tripulante data_buffer);
t_expulsar_tripulante deserializar_expulsar_tripulante(t_paquete * paquete);


#endif  