#include "util_discordiador.h"

Patota *map_to_patota(t_iniciar_patota datosPatota)
{
    numeroPatota++;
    Patota *patota_new = malloc(sizeof(Patota));
    patota_new->id = numeroPatota;
    patota_new->tareas = list_create();      //Lista [Tarea]
    patota_new->tripulantes = list_create(); //Lista [Tripulante]

    char **posiciones_string = string_split(datosPatota.posiciones, " ");
    t_list *posiciones_lista = list_create();
    void recorrer_posiciones(char *item)
    {
        list_add(posiciones_lista, item);
    }
    string_iterate_lines(posiciones_string, recorrer_posiciones);

    for (int c = 0; c < datosPatota.cant_tripulantes; c++)
    {
        numeroTripulante++;
        Tripulante *tripulante = malloc(sizeof(Tripulante));
        tripulante->id = numeroTripulante;
        tripulante->status = NEW;
        tripulante->tarea = NULL;
        tripulante->posicion = malloc(sizeof(Posicion));
        tripulante->posicion->posx = 0;
        tripulante->posicion->posy = 0;
        tripulante->patota_id = numeroPatota;
        list_add(patota_new->tripulantes, tripulante);
    }

    int posx = 0;
    int posy = 0;

    for (int c = 0; c < list_size(posiciones_lista) && list_is_empty(posiciones_lista); c++)
    {
        Tripulante *tripulante = list_get(patota_new->tripulantes, c);
        char *posicion_string = list_get(posiciones_lista, c);
        char **coordenadas = string_split(posicion_string, "|");
        posx = atoi(coordenadas[0]);
        posy = atoi(coordenadas[1]);
        tripulante->posicion->posx = posx;
        tripulante->posicion->posy = posy;
    }

    //Falta mapeo de tareas para patota
    return patota_new;
}

void mostrar_t_patota(Patota *patota)
{
    printf("Inicio de patota\n");
    printf("Patota id: %d\n", patota->id);

    for (int c = 0; c < list_size(patota->tripulantes); c++)
    {
        Tripulante *tripulante = list_get(patota->tripulantes, c);
        printf("Tripulante id: %d ", tripulante->id);
        printf("Status: %s ", get_status_string(tripulante->status));
        printf("Posicion: %d-%d\n", tripulante->posicion->posx, tripulante->posicion->posy);
    }
}

void mostrar_datos_patota(t_iniciar_patota *datosPatota)
{
    printf("tripulantes: %d\n", datosPatota->cant_tripulantes);
    printf("long path tares: %d\n", datosPatota->long_path_tareas);
    printf("long posiciones: %d\n", datosPatota->long_posicion);
    printf("posiciones: %s\n", datosPatota->posiciones);
    printf("pathTareas: %s\n", datosPatota->path_tareas);
}

char *get_status_string(status_tripulante status)
{
    char *texto = "";
    switch (status)
    {
    case NEW:
        texto = "New";
        break;
    case READY:
        texto = "Ready";
        break;
    case EXEC:
        texto = "Exec";
        break;
    case BLOCKED:
        texto = "Blocked";
        break;
    case EXIT:
        texto = "Exit";
        break;
    }
    return texto;
}

t_list *get_tripulantes_all()
{
    //Retorna todos los tripulantes del sistema
    t_list *tripulantes = list_create();
    return tripulantes;
}