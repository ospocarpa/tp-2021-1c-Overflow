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
    datosPatota->long_tareas = bytesContenido,
    datosPatota->tareas = contenido;
    free(contenido);
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
//

void hilo_tripulante(Tripulante *tripulante)
{
    pthread_mutex_lock(&MXTRIPULANTE);
    list_add(lista_tripulantes, tripulante);
    pthread_mutex_unlock(&MXTRIPULANTE);

    //tripulante se conecta a mi ram

    int socket_cliente = crear_conexion(config->IP_MI_RAM_HQ, config->PUERTO_MI_RAM_HQ);

    if (socket_cliente < 0)
    {
        log_error(logger, "Conexion Mi-RAM fallida");
        liberar_conexion(socket_cliente);
        // return EXIT_FAILURE; //despues descomitear
    }
    else
    {
        log_info(logger, "Tripulante %d Conexion con Mi-RAM-HQ exitosa", tripulante->id);
    }

    printf("Hilo tripulante:%d\n", tripulante->id);

    /*  int sval;
    sem_getvalue(&grado_multiprocesamiento, &sval);
    printf("multiTarea:%d\n", sval); */

    _Bool finalizo_tarea = false; //chequear

    //Defino pedirTarea dentro de hilo_tripulante
    void pedirTarea()
    {
        // Completa esta estructura para pedir la tarea a mi_ram
        t_short_info_tripulante info_tripulante;
        info_tripulante.patota_id = tripulante->patota_id;
        info_tripulante.tripulante_id = tripulante->id;

        //se empaqueta y se envia el mensaje
        t_package paquete = ser_cod_informar_tarea_tripulante(info_tripulante);
        sendMessage(paquete, socket_cliente);
        //se espara una respuesta
        paquete = recibir_mensaje(socket_cliente);
        //En tarea se guarda la proxima tarea a ejecutar
        t_info_tarea tarea = des_res_informacion_tarea_tripulante(paquete);
        tripulante->tarea = &tarea;
        return;
    }

    pthread_mutex_lock(&tripulante->activo);

    while (1)
    {
        if (!finalizo_tarea)
        {
            pedirTarea();

            //Comprobacion que se guardo la tarea por defecto bien(despues borrar)
            printf("Tiempo de la tarea %d\n", tripulante->tarea->tiempo);
            //

            if (tripulante->status == NEW)
            {

                // 1era iteracion entraria al if
                // sacarlo de la lista_tripulantes ?
                tripulante->status = READY;

                // cantidad tripulantes:READY-EXEC-I/O
                // sem_post(&activados); //ver porque da error
            }
            if (tripulante->tarea == NULL)
            {

                list_add(lista_EXIT, tripulante);
                printf("Hilo tripulante :%d bye bye\n", tripulante->id);

                //falta removerlo de la lista tripulante
                //list_remove_and_destroy_by_condition(lista_tripulantes*, ,)

                break;
            }
            //Para que el dispatcher sepa que estamos listos
            sem_post(&listos);
            //Esperamos ser seleccionados
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
    liberar_conexion(socket_cliente);
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

void ir_a_la_posicion(Tripulante *tripulante, Posicion posicion_tarea)
{

    int rafaga; // en primera instancia, si es RR pasaria el valor y en vez de while usaria un for

    while (tripulante->posicion->posx != posicion_tarea.posx)
    {
        /*if(esta_pausado){
            pthread_mutex_lock(tripulante->activo);
        }
        */

        if (tripulante->posicion->posx < posicion_tarea.posx)
        {
            tripulante->posicion->posx++;
        }
        else
        {
            tripulante->posicion->posx--;
        }
    }

    while (tripulante->posicion->posy != posicion_tarea.posy)
    {
        /*if(esta_pausado){
            pthread_mutex_lock(tripulante->activo);
        }
        */
        if (tripulante->posicion->posy < posicion_tarea.posy)
        {
            tripulante->posicion->posy++;
        }
        else
        {
            tripulante->posicion->posy--;
        }
    }
}