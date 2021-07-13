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
    datosPatota->patota_id = numeroPatota;
    datosPatota->id_primer_tripulante = numeroTripulante;
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

void pedirTarea(Tripulante *tripulante, int socket_cliente)
{
    // Completa esta estructura para pedir la tarea a mi_ram
    t_short_info_tripulante info_tripulante;
    info_tripulante.patota_id = tripulante->patota_id;
    info_tripulante.tripulante_id = tripulante->id;

    //Se empaqueta y se envia el mensaje
    t_package paquete = ser_cod_informar_tarea_tripulante(info_tripulante);
    sendMessage(paquete, socket_cliente);
    //Se espara una respuesta
    paquete = recibir_mensaje(socket_cliente);
    //En tarea se guarda la proxima tarea a ejecutar
    t_info_tarea tarea;
    tarea = des_res_informacion_tarea_tripulante(paquete);
    tripulante->tarea = &tarea;

    return;
}
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
    //falta conexion con mongo-Store
    _Bool mismo_id(void *param)
    {
        int *un_id = (int *)param;
        return tripulante->id == *un_id;
    }
    // Cuando quiero saber el valor de un semaforo
    /*  int sval;
    sem_getvalue(&grado_multiprocesamiento, &sval);
    printf("multiTarea:%d\n", sval); */
    //
    _Bool finalizo_tarea = false; //chequear

    pthread_mutex_lock(&tripulante->activo);

    while (1)
    {
        if (!finalizo_tarea)
        {
            tripulante->rafagas_consumidas = 0;
            pedirTarea(tripulante, socket_cliente);

            //Comprobacion que se guardo la tarea por defecto bien(despues borrar)
            //printf("Tiempo de la tarea %d\n", tripulante->tarea->tiempo);
            //

            if (tripulante->status == NEW)
            {

                // Solo en la 1era iteraccion entraria a est if
                //Se agrega a la lista de ready
                pthread_mutex_lock(&MXTRIPULANTE);
                list_add(lista_READY, tripulante);
                pthread_mutex_unlock(&MXTRIPULANTE);
                //

                tripulante->status = READY;
            }

            if (tripulante->tarea == NULL)
            {

                list_add(lista_EXIT, tripulante);
                printf("Tripulante %d Bye Bye\n", tripulante->id);
                //MI ram elimina a este tripulante de su memoria
                //falta removerlo de la lista tripulante

                Tripulante *tripulante1 = list_remove_by_condition(lista_tripulantes, mismo_id);
                Tripulante *tripulante2 = list_remove_by_condition(lista_READY, mismo_id);
                //list_remove_by_condition(lista_READY)
                free(tripulante);
                //Comprobacion :despues borrar
                printf("id del tripulane removido:%d-%d\n", tripulante1->id, tripulante2->id);

                break;
            }
            //Para que el dispatcher sepa que estamos listos
            sem_post(&listos);
            //Esperamos ser seleccionados
            pthread_mutex_lock(&tripulante->seleccionado);

            sem_post(&activados); // cantidad tripulantes:-EXEC-I/O
            list_add(lista_EXEC, tripulante);
            //Cuando hay sabotaje

            hay_sabotaje = true; //despues borrar linea
            if (hay_sabotaje)
            {
                chequear_activados();
                pthread_mutex_lock(&tripulante->activo);
            }

            mover_tripulante_a_tarea(tripulante, socket_cliente);

            sem_post(&grado_multiprocesamiento);

            if (tripulante->tarea->tarea != OTRA_TAREA)
            {
                printf("tripulante %d bloqueate\n", tripulante->id);
                sleep(config->RETARDO_CICLO_CPU);
                list_add(lista_BLOCKIO, tripulante);
                Tripulante *tripulante_bloq = list_remove_by_condition(lista_READY, mismo_id);
                printf("id del tripulane bloqueado:%d\n", tripulante_bloq->id);
                //Consultar
                //nos falta logica de como ejecutan los tripulantes bloqueados ??
                //bloqueate
                if (hay_sabotaje)
                {
                    chequear_activados();
                    pthread_mutex_lock(&tripulante->activo);
                }
            }
            while (tripulante->rafagas_consumidas < tripulante->tarea->tiempo)
            {
                if (hay_sabotaje)
                {
                    chequear_activados();
                    pthread_mutex_lock(&tripulante->activo);
                }
                tripulante->rafagas_consumidas++;
                sleep(config->RETARDO_CICLO_CPU);
            }
            //Falta que el tripulante consuma su rafa de CPU
            //consulta de agregar ese consumo (si es bloqueado por sabataje)
            // persistirlo
        }
    }

    liberar_conexion(socket_cliente);
    return;
}

/*  
        1 tiene q llamar a mi_ram  para pedir siguiente tarea
          nota: si tiene tarea pasa a estado listo
          //TODO
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
    int posicion_tarea_x = 2; //tripulante->tarea->posicion.posx;
    int posicion_tarea_y = 3; //tripulante->tarea->posicion.posy;
    //Parece que se pasa mal la tarea o algo, pero harcodeando la posicion de la tarea funca bien.
    printf("TAREA POSICION X : %d POSICION Y: %d\n", posicion_tarea_x, posicion_tarea_y); //BORRAR

    int rafaga = 1;
    int retardo_cpu = config->RETARDO_CICLO_CPU;
    if (config->ALGORITMO == RR)
    {
        rafaga = config->QUANTUM;
    }
    int ciclos_consumidos = 0;

    while (tripulante->posicion->posx != posicion_tarea_x && ciclos_consumidos < rafaga)
    {
        if (planificacion_activa)
        {
            pthread_mutex_lock(&tripulante->activo);
        }
        //Mueve uno en X
        if (posicion_tarea_x > tripulante->posicion->posx)
        {
            tripulante->posicion->posx++;
        }
        else if (posicion_tarea_x < tripulante->posicion->posx)
        {
            tripulante->posicion->posx--;
        }
        //prueba
        printf("Tripulante: %d  posx: %d, posy: %d, ciclos consumidos: %d,tareaPosX: %d , tareaPosY: %d\n", tripulante->id, tripulante->posicion->posx, tripulante->posicion->posy, ciclos_consumidos, tripulante->tarea->posicion.posx, tripulante->tarea->posicion.posy);
        //
        if (config->ALGORITMO == RR)
        {
            ciclos_consumidos++;
        }
        sleep(retardo_cpu);
        enviar_posicion_mi_ram(tripulante, socket);
    }

    while (tripulante->posicion->posy != posicion_tarea_y && ciclos_consumidos < rafaga)
    {
        if (planificacion_activa)
        {
            pthread_mutex_lock(&tripulante->activo);
        }
        //Mueve uno en Y
        if (posicion_tarea_y > tripulante->posicion->posy)
        {
            tripulante->posicion->posy++;
        }
        else if (posicion_tarea_y < tripulante->posicion->posy)
        {
            tripulante->posicion->posy--;
        }
        //prueba
        printf("Tripulante: %d  posx: %d, posy: %d, ciclos consumidos: %d\n", tripulante->id, tripulante->posicion->posx, tripulante->posicion->posy, ciclos_consumidos);
        //
        if (config->ALGORITMO == RR)
        {
            ciclos_consumidos++;
        }
        sleep(retardo_cpu);
        enviar_posicion_mi_ram(tripulante, socket);
    }
    printf("Tripulante %d POsicion final %d-%d\n", tripulante->id, tripulante->posicion->posx, tripulante->posicion->posy);

    //Prueba en cosola en fifo:OK
    // mi ram nos envia una tarea con pos 3-4
    //iniciar_patota 5 ./cfg/tareasPatota1.txt 1|1 2|2 3|3 4|4 5|5
}

void enviar_posicion_mi_ram(Tripulante *tripulante, int socket)
{
    t_informar_posicion_tripulante info_tripulante;
    info_tripulante.patota_id = tripulante->patota_id;
    info_tripulante.tripulante_id = tripulante->id;
    info_tripulante.posicion.posx = tripulante->posicion->posx;
    info_tripulante.posicion.posy = tripulante->posicion->posy;

    t_package paquete = ser_res_informar_posicion_tripulante(info_tripulante);
    sendMessage(paquete, socket);
}
void chequear_activados()
{
    sem_wait(&activados);
    int cantidad_activos;
    sem_getvalue(&activados, &cantidad_activos);

    if (cantidad_activos == 0)
    {
        inicio_sabotaje();
    }
}

//se pasa por parametro un sabotaje?  Rta: sí
void inicio_sabotaje()
{
    bool comparador(void *tripulante1, void *tripulante2)
    {
        Tripulante *tripulante1_analizar = (Tripulante *)tripulante1;
        Tripulante *tripulante2_analizar = (Tripulante *)tripulante2;

        return tripulante1_analizar->id < tripulante2_analizar->id;
    }

    t_list *tripulantes = get_tripulantes_all();

    list_sort(tripulantes, comparador);
    bool estas_exec(void *_tripulante)
    {

        Tripulante *tripulante = (Tripulante *)_tripulante;

        return tripulante->status == EXEC;
    }

    t_list *tripulantes_exec = list_filter(tripulantes, estas_exec);

    list_add_all(lista_BLOCKEMERGENCIA, tripulantes_exec);
    while (list_is_empty(tripulantes_exec))
    {
        Tripulante *un_tripulante = list_remove(tripulantes_exec, 0);
        un_tripulante->status = BLOCKED;
    }
    //
    bool estas_ready(void *_tripulante)
    {
        Tripulante *tripulante = (Tripulante *)_tripulante;

        return tripulante->status == READY;
    }

    t_list *tripulantes_ready = list_filter(tripulantes, estas_ready);

    list_add_all(lista_BLOCKEMERGENCIA, tripulantes_ready);
    while (list_is_empty(tripulantes_ready))
    {
        Tripulante *un_tripulante = list_remove(tripulantes_ready, 0);
        un_tripulante->status = BLOCKED;
    }
    //Tripulante *tripulante_elegido = buscar_el_mas_cercano();

    //ir_a_la_posicion_sabotaje(sabotaje) //pasa a exec
    //invocar_fsck()
    desbloquear_tripulantes();
    printf("soy un sabotaje");
}

/* Tripulante* buscar_el_mas_cercano()
{
    
} */

void invocar_fsck(){
    int conexion_a_mongo_store = crear_conexion(config->IP_I_MONGO_STORE, config->PUERTO_I_MONGO_STORE);
    
    t_aviso_fsck fcsk;
    t_package paquete = ser_fcsk(fcsk);

    if(conexion_a_mongo_store>0){
        sendMessage(paquete, conexion_a_mongo_store);
    }
}

void desbloquear_tripulantes()
{
    while (list_is_empty(lista_BLOCKEMERGENCIA))
    {
        Tripulante *un_tripulante = list_remove(lista_BLOCKEMERGENCIA, 0);
        un_tripulante->status = READY;
        list_add(lista_READY, un_tripulante);
    }
}