#include "dispatcher.h"


void init_dispatcher(){
    //printf("Inicio\n");
    while(1){
        //printf("Ejecución\n");
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
    Tripulante* tripulante = list_get(lista_READY, indice);
    list_remove(lista_READY, indice);
    //printf("ID: %d\n", tripulante->id);
    return tripulante;
}