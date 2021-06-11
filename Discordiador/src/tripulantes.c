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
    //mostrar_datos_patota(datosPatota);
}

void ejecucion_dispatcher()
{
    //son todos los tripulantes listos
    t_list *tripulantes_all = list_create();

    switch (config->ALGORITMO)

    {
    case FIFO:

        break;
    case RR:

        break;
    default:
        break;
    }

    //tripulantes.listos a tripulanes.exec
}
void pedirTarea(Tripulante *tripulante)
{
    tripulante->tarea = NULL;
}
void hilo_tripulante(Tripulante *tripulante)
{
    printf("Hilo tripulante:%d\n", tripulante->id);
    /*  int sval;
    sem_getvalue(&grado_multiprocesamiento, &sval);
    printf("multiTarea:%d\n", sval); */

    _Bool finalizo_tarea = false;
    pthread_mutex_init(&tripulante->activo, 0);
    pthread_mutex_init(&tripulante->seleccionado, 0);
    pthread_mutex_lock(&tripulante->activo);
    while (1)
    {
        if (!finalizo_tarea)
        {
            pedirTarea(tripulante);
            if (tripulante->tarea == NULL)
            {
                printf("Hilo tripulante:%d bye bye\n", tripulante->id);
                break;
            }

            sem_post(&listos); //listos++
            pthread_mutex_lock(&tripulante->seleccionado);

            //   ir_a_la_posicion(tripulante->tarea->posicion->posx,tripulante->tarea->posicion->posy);
            sem_post(&grado_multiprocesamiento);

            //   if(tripulante->tarea.bloqueado == true) {
            //      bloqueate();
        }
    }

    //tripulane pasa a cola de exit ;
    /// -------------------------------------------------
    //pthread_mutex_lock(&MXTRIPULANTE);

    /*  printf("hilo:%d\n", process_get_thread_id());
    pthread_mutex_unlock(&MXTRIPULANTE);
 */
    return;
}

/*  
        1 tiene q llamar a mi_ram  para pedir siguiente tarea
          nota: si tiene tarea pasa a estado listo
          2 creamos semaforo planificacion "PAUSAR_PLANIFICACION"
          3 Cuando se pause la planificacion ,a todos los semaforos
          de los tripulantes se bloquea 
          4 si se desbloquea (por iniciar_planificacion de consola)
         5 otro semaforo arrancar (seleccionado para cada tripulante)?
        wait (tripulante ->activo)  
         wait (tripulante->seleccionado)

         --------------------------------------
         PENDIENTES
 
         1 Pensar como arranca  dispacher ejecuta :
               
         2 hacer que este metodo sea ciclico 
          
        3 Pensar transicicon listo ->bloqueado 
                    
        


     */

//reemplazar cantidad por datos
void crearHilosTripulantes(Patota *una_patota)
{
    printf("Iniciando\n");
    // Inicializo semaforo
    pthread_mutex_init(&MXTRIPULANTE, NULL);

    //numeroPatota++;
    int cantidad = list_size(una_patota->tripulantes);

    //  Tripulante *un_tripulante;

    for (int i = 0; i < cantidad; i++)
    {
        pthread_t hilo;
        Tripulante *un_tripulante;
        un_tripulante = list_get(una_patota->tripulantes, i);

        pthread_create(&hilo, NULL, (void *)&hilo_tripulante, un_tripulante);
        pthread_detach(hilo);
    }
}
