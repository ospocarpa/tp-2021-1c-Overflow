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
void pedirTarea(Tripulante *tripulante, int socket)
{
    //Despues tendra que llamar a miram
    t_short_info_tripulante info_tripulante;
    info_tripulante.patota_id = tripulante->patota_id;
    info_tripulante.tripulante_id = tripulante->id;
    // printf("%d %d\n", info_tripulante.tripulante_id, info_tripulante.patota_id);
    t_package paquete = ser_cod_informar_tarea_tripulante(info_tripulante);
    sendMessage(paquete, socket);
    //Espero respuesta de mi_ram
    paquete = recibir_mensaje(socket);
    t_info_tarea tarea = des_res_informacion_tarea_tripulante(paquete);
    tripulante->tarea = &tarea;
    return;
}
void hilo_tripulante(Tripulante *tripulante)
{
    pthread_mutex_lock(&MXTRIPULANTE);
    list_add(lista_tripulantes, tripulante);

    //Tripulante *otroTripulante = list_get(lista_tripulantes, (tripulante->id) - 1);
    pthread_mutex_unlock(&MXTRIPULANTE);

    //tripulante se conecta a mi ram
    int socket_cliente = crear_conexion(config->IP_MI_RAM_HQ, config->PUERTO_MI_RAM_HQ);
    // printf("%s %d\n", config->IP_MI_RAM_HQ, config->PUERTO_MI_RAM_HQ);
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

    //usar estructura patota id
    //devolver un metodo tarea por default(por ahora)
    //getTarea(Tar)
    //printf("Posicione %d esta el tripulante%d\n", (tripulante->id) - 1, otroTripulante->id);
    printf("Hilo tripulante:%d\n", tripulante->id);
    /*  int sval;
    sem_getvalue(&grado_multiprocesamiento, &sval);
    printf("multiTarea:%d\n", sval); */

    _Bool finalizo_tarea = false; //chequear
                                  //mutex_init de los semaforos esta en la creacion de los tripulantes(mapToPatota)
    pthread_mutex_lock(&tripulante->activo);
    while (1)
    {
        if (!finalizo_tarea)
        {
            pedirTarea(tripulante, socket_cliente); //agregado
            printf("Tiempo de la tarea %d\n", tripulante->tarea->tiempo);
            if (tripulante->status == NEW)
            {

                // 1era itera
                tripulante->status = READY;
            }
            if (tripulante->tarea == NULL)
            { //linea 77 rompe
                //list_remove(lista_tripulantes, tripulante->id - 1);
                list_add(lista_EXIT, tripulante);
                printf("Hilo tripulante :%d bye bye\n", tripulante->id);
                break;
            }

            sem_post(&listos); //listos++
            pthread_mutex_lock(&tripulante->seleccionado);
            mover_tripulante_a_tarea(tripulante, socket_cliente);
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

void mover_tripulante_a_tarea(Tripulante *tripulante, int socket)
{
    Posicion posicion_tarea = tripulante->tarea->posicion;
    int rafaga = -1;
    if(config->ALGORITMO == RR){
        rafaga = config->QUANTUM;
    }
    int ciclos_consumidos = 0;

    while (tripulante->posicion->posx != posicion_tarea.posx && rafaga < ciclos_consumidos)
    {
        if(planificacion_activa){
            pthread_mutex_lock(&tripulante->activo);
        }
        //Mueve uno en X
        if (tripulante->posicion->posx < posicion_tarea.posx){
            tripulante->posicion->posx++;
        }
        else{
            tripulante->posicion->posx--;
        }
        ciclos_consumidos++;
        enviar_posicion_mi_ram(tripulante, socket);
    }

    while (tripulante->posicion->posy != posicion_tarea.posy && rafaga < ciclos_consumidos)
    {
        if(planificacion_activa){
            pthread_mutex_lock(&tripulante->activo);
        }
        //Mueve uno en Y
        if (tripulante->posicion->posy < posicion_tarea.posy){
            tripulante->posicion->posy++;
        }
        else{
            tripulante->posicion->posy--;
        }
        ciclos_consumidos++;
        enviar_posicion_mi_ram(tripulante, socket);
    }
}

void enviar_posicion_mi_ram(Tripulante *tripulante, int socket){
    t_informar_posicion_tripulante info_tripulante;
    info_tripulante.patota_id = tripulante->patota_id;
    info_tripulante.tripulante_id = tripulante->id;
    info_tripulante.posicion.posx = tripulante->posicion->posx;
    info_tripulante.posicion.posy = tripulante->posicion->posy;

    t_package paquete = ser_res_informar_posicion_tripulante(info_tripulante);
    sendMessage(paquete, socket);


}