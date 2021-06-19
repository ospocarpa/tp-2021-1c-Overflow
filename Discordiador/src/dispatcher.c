#include "dispatcher.h"


void init_dispatcher(){
    busqueda_algoritmo(FIFO);
    /*while(1){
        sem_wait(&listos);
        Tripulante* tripulante_seleccionado = busqueda_algoritmo(FIFO);
        sem_wait(&grado_multiprocesamiento);
        pthread_mutex_unlock(&tripulante_seleccionado->seleccionado);
    }*/
}

Tripulante* busqueda_algoritmo(alg_planificacion tipo_planificacion){
    //printf("Config dispatcher: %d\n", config->ALGORITMO);
    Tripulante* tripulante = NULL;
    switch(config->ALGORITMO){
        case FIFO: 
            //Retornar la cola de listos
            tripulante = NULL;
            break;
        case RR: 
            //Retornar la cola de listos
            tripulante = NULL;
            break;
    } 
    return tripulante;
}