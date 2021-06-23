#include "dispatcher.h"


void init_dispatcher(){
    while(1){
        sem_wait(&listos);
        Tripulante* tripulante_seleccionado = busqueda_algoritmo();
        sem_wait(&grado_multiprocesamiento);
        pthread_mutex_unlock(&tripulante_seleccionado->seleccionado);
    }
}

Tripulante* busqueda_algoritmo(){
    //printf("Config dispatcher: %d\n", config->ALGORITMO);
    //Retornar la cola de listos
    int indice = list_size(lista_READY)-1;
    list_remove(lista_READY, indice);
    Tripulante* tripulante = list_find(lista_READY, indice);
    return tripulante;
}