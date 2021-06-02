#include "tripulantes.h"

void cargarTripulante(t_iniciar_patota *datosPatota, char **tokens, int cantidad_argumentos)
{
    datosPatota->cant_tripulantes = atoi(tokens[1]);
    int cantidadPosiciones = cantidad_argumentos - 2;
    char *posiciones = string_new();
    char *contenido;
    for (int i = 0; i < cantidadPosiciones; i++)
    {
        string_append(&posiciones, tokens[3 + i]);
        string_append(&posiciones, " ");

        // printf("cadena parcial:%s\n", posiciones);
    }
    string_trim_right(&posiciones);
    datosPatota->long_posicion = strlen(posiciones);
    datosPatota->posiciones = posiciones;
    int bytesContenido = guardar_contenido_archivo(tokens[2], &contenido);
    datosPatota->long_path_tareas = bytesContenido,
    datosPatota->path_tareas = contenido;
    free(contenido);
    free(posiciones);

    /*   printf("tripulantes: %d\n", datosPatota->cant_tripulantes);
    printf("long path tares: %d\n", datosPatota->long_path_tareas);
    printf("long posiciones: %d\n", datosPatota->long_posicion);
    printf("posiciones: %s\n", datosPatota->posiciones);
    printf("pathTareas: %s\n", datosPatota->path_tareas); */
}

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
