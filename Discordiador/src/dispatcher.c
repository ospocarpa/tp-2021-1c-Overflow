#include "dispatcher.h"

void init_dispatcher()
{
    //printf("Inicio\n");
    while (1)
    {
        //printf("Ejecución\n");
        sem_wait(&listos);
        Tripulante *tripulante_seleccionado = busqueda_algoritmo();
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

    int indice = list_size(lista_READY) - 1;
    Tripulante *tripulante = list_get(lista_READY, indice);
    list_remove(lista_READY, indice);
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