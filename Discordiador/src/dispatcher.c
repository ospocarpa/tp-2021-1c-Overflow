#include "dispatcher.h"

void init_dispatcher()
{
    //printf("Inicio\n");
    while (1)
    {
        //printf("Ejecución\n");
        sem_wait(&listos);
        printf("Antes algoritmo  linea 10\n");
        Tripulante *tripulante_seleccionado = busqueda_algoritmo();
        printf("Despues algoritmo  linea 12\n");
        sem_wait(&grado_multiprocesamiento);
        sem_wait(&tripulante_seleccionado->seleccionado);
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
    printf("soh la linea 35\n");
    int indice = list_size(lista_READY) - 1;
    printf("soh la linea 37\n");
    printf("%d\n", indice);
    pthread_mutex_lock(&MXTRIPULANTE);
    Tripulante *tripulante = list_get(lista_READY, indice); //error
    printf("soh la linea 39\n");
    //list_remove(lista_READY, indice);
    pthread_mutex_unlock(&MXTRIPULANTE);
    printf("soh la linea 41\n");
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