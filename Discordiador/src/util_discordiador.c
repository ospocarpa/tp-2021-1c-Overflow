#include "../include/util_discordiador.h"

//funcion agregada
bool esBloqueante(Tarea *tarea)
{
    //pendiente
    return true;
}

Patota *map_to_patota(t_iniciar_patota datosPatota)
{
    // numeroTripulante--;
    Patota *patota_new = malloc(sizeof(Patota));
    patota_new->id = numeroPatota;
    patota_new->tareas = list_create();      //Lista [Tarea]
    patota_new->tripulantes = list_create(); //Lista [Tripulante]

    t_list *posiciones_lista = list_create();
    char **posiciones_string;
    if (strcmp(datosPatota.posiciones, "") != 0)
    {

        posiciones_string = string_split(datosPatota.posiciones, " ");

        void recorrer_posiciones(char *item)
        {
            list_add(posiciones_lista, item);
        }
        string_iterate_lines(posiciones_string, recorrer_posiciones);
    }

    for (int c = 0; c < datosPatota.cant_tripulantes; c++)
    {

        Tripulante *tripulante = malloc(sizeof(Tripulante));
        tripulante->id = numeroTripulante;
        tripulante->status = NEW;
        tripulante->tarea = malloc(sizeof(t_info_tarea));
        tripulante->tarea = NULL;
        tripulante->posicion = malloc(sizeof(Posicion));
        tripulante->posicion->posx = 0;
        tripulante->posicion->posy = 0;
        
        tripulante->posicion_anterior = malloc(sizeof(Posicion));
        tripulante->posicion_anterior->posx = 0;
        tripulante->posicion_anterior->posy = 0;

        tripulante->patota_id = numeroPatota;
        tripulante->rafagas_consumidas = 0;
        //se inicializan los semaforos de los tripulantes
        sem_init(&tripulante->activo, 0, 0);
        sem_init(&tripulante->seleccionado, 0, 0);
        sem_init(&tripulante->seleccionado_bloqueado, 0, 0);
        //sem_init(&tripulante->sabotaje, 0, 0);

        // pthread_mutex_init(&tripulante->seleccionado, NULL);
        // pthread_mutex_init(&tripulante->seleccionado_bloqueado, NULL);
        //pthread_mutex_init(&tripulante->sabotaje,0);
        list_add(patota_new->tripulantes, tripulante);
        // defino los sockets en -1
        tripulante->socket_cliente_mongo_store = -1;
        tripulante->socket_cliente_mi_ram = -1;
        tripulante->expulsado = false;
        numeroTripulante++;
    }

    int posx = 0;
    int posy = 0;

    for (int c = 0; c < list_size(posiciones_lista); c++)
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
    //list_clean(posiciones_lista);
    //list_destroy(posiciones_lista);
    //liberar_puntero_doble(posiciones_string);
    numeroPatota++;
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
    printf("long path tares: %d\n", datosPatota->long_tareas);
    printf("long posiciones: %d\n", datosPatota->long_posicion);
    printf("posiciones: %s\n", datosPatota->posiciones);
    printf("pathTareas: %s\n", datosPatota->tareas);
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
        texto = "Block I/0";
        break;
    case EXIT:
        texto = "Exit";
        break;
    case BLOCKED_SABOTAJE:
        texto = "Block sabotaje";
        break;
    }
    return texto;
}

t_list *get_tripulantes_all()
{
    t_list *tripulantes = lista_tripulantes;
    for (int i = 0; i < list_size(tripulantes); i++)
    {
        Tripulante *tripulante = list_get(tripulantes, i);
        printf("ID del tripulante : %d\n", tripulante->id);
    }
    return tripulantes;
}

Tripulante *tripulante_segun_id(int id)
{
    _Bool mismo_id(void *param)
    {
        Tripulante *tripulante = param;
        return tripulante->id == id;
    }
    return (Tripulante *)list_find(get_tripulantes_all(), &mismo_id);
}
//lista_tripulante= get

int existe_tripulante(int id)
{
    return tripulante_segun_id(id) == NULL ? false : true;
}

int obtener_cantidad_argumentos(char **tokens)
{

    int i = 1;
    int cantidad = 0;

    while (*(tokens + i) != NULL)
    {
        cantidad++;
        i++;
    }

    return cantidad;
}

int guardar_contenido_archivo(const char *ruta, char **contenido)
{

    FILE *arch = fopen(ruta, "r");
    int bytes;
    *contenido = NULL;
    fseek(arch, 0, SEEK_END);
    bytes = ftell(arch);
    fseek(arch, 0, SEEK_SET);
    *contenido = malloc(bytes);
    fread(*contenido, 1, bytes, arch);
    fclose(arch);
    return bytes;
}

char *get_tareas_from_path(char *path)
{
    int file_size = 1000;
    int fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ftruncate(fd, file_size);
    char *tareas = mmap(NULL, file_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    //printf("%s %d\n", space, strlen(space));
    return tareas;
}