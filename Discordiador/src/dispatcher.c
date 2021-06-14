#include "dispatcher.h"


void init_dispatcher(){
    while(1){
        sem_wait(&listos);
        Tripulante* tripulante_seleccionado = busqueda_algoritmo(FIFO);
        sem_wait(&grado_multiprocesamiento);
        sem_post(&tripulante_seleccionado->seleccionado); //mutex
    }
}

Tripulante* busqueda_algoritmo(alg_planificacion tipo_planificacion){
    //t_list* tripulantes = 
    return NULL;
}