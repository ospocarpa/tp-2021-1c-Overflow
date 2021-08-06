#include "dispatcher.h"

void init_dispatcher()
{
    //printf("Inicio\n");
    while (1)
    {
        //printf("Ejecución\n");
        sem_wait(&listos);
        Tripulante *tripulante_seleccionado = busqueda_algoritmo();
        sem_post(&tripulante_seleccionado->seleccionado);
        sem_wait(&grado_multiprocesamiento);
    }
}
void init_bloqueados()
{
    //printf("Bloqueados\n");
    while (1)
    {
        sem_wait(&bloqueados); // mientras halla bloqueados

        // un semaforo para seleccionado bloqueado ???
        Tripulante *tripulante_seleccionado = elegir_tripulante_bloqueado();
        // un mutex para que solo ejecute un bloqueado
        sem_post(&tripulante_seleccionado->seleccionado_bloqueado);
    }
}

Tripulante *busqueda_algoritmo()
{
    //printf("Config dispatcher: %d\n", config->ALGORITMO);
    //Retornar la cola de listos
    pthread_mutex_lock(&MXTRIPULANTE);
    int indice = list_size(lista_READY) - 1;
    printf("Indice: %d\n", indice);
    Tripulante *tripulante = list_get(lista_READY, indice);
    pthread_mutex_unlock(&MXTRIPULANTE);
    //printf("ID: %d\n", tripulante->id);
    return tripulante;
}

Tripulante *elegir_tripulante_bloqueado()
{
    int indice = list_size(lista_BLOCKIO) - 1;
    Tripulante *tripulante = list_get(lista_BLOCKIO, indice);
    //se remueve en tripulantes??
    return tripulante;
}