#include "tripulantes.h"

void imprime_mensaje()
{
    pthread_mutex_lock(&MXTRIPULANTE);

    numeroTripulante++;

    printf("tripulante %d\t patota %d\thilo:%d\n", numeroTripulante, numeroPatota, process_get_thread_id());
    pthread_mutex_unlock(&MXTRIPULANTE);

    return;
}

void crearHilosTripulantes(int cantidad)
{

    // Inicializo semaforo
    pthread_mutex_init(&MXTRIPULANTE, NULL);

    numeroPatota++;

    for (int i = 0; i < cantidad; i++)
    {
        pthread_t hilo;

        pthread_create(&hilo, NULL, (void *)&imprime_mensaje, NULL);
        pthread_detach(hilo);
    }
}
