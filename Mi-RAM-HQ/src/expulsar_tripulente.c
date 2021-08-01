#include "expulsar_tripulante.h"

/* **************************** */
void expulsar_tripulante_segmentacion(t_expulsar_tripulante tripulante);

/* ************************************ */

void expulsar_tripulante_segmentacion(t_expulsar_tripulante tripulante){

    eliminar_segmento_tripulante(tripulante);
}

void expulsar_tripulante(t_expulsar_tripulante tripulante){
    
    char * tipo_memoria = get_esquema_memoria();

    if(tipo_memoria == "SEGMENTACION")
    {
        expulsar_tripulante_segmentacion(tripulante);
    }
    else
    {
        /* code */
    }
    
}