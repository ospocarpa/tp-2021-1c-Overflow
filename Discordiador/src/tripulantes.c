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

        // printf("cadena parcial:%s\n", posiciones); .
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
//borrar esta funcion ??
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
    printf("Patota: %d tripulante: %d\n", tripulante->patota_id, tripulante->id);
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
    

    t_info_tarea* tarea_tripulante = malloc(sizeof(t_info_tarea));
    
    tarea_tripulante->tarea = tarea.tarea;
    tarea_tripulante->parametro = tarea.parametro;
    tarea_tripulante->tiempo = tarea.tiempo;
    tarea_tripulante->posicion.posx = tarea.posicion.posx;
    tarea_tripulante->posicion.posy = tarea.posicion.posy;

    tripulante->tarea = tarea_tripulante;
    return;
}

void hilo_tripulante(Tripulante *tripulante)
{
    pthread_mutex_lock(&MXTRIPULANTE);
    list_add(lista_tripulantes, tripulante);
    pthread_mutex_unlock(&MXTRIPULANTE);

    printf("Pedí antes: %d\n", tripulante->id);
    pthread_mutex_lock(&tripulante->activo);        //Activo: se refiere a si la planificación está activa //TO DO
    
    int socket_cliente_mongo_store = crear_conexion(config->IP_I_MONGO_STORE, config->PUERTO_I_MONGO_STORE);
    if (socket_cliente_mongo_store < 0)
    {
        log_error(logger, "Conexion MongoStore fallida");
        liberar_conexion(socket_cliente_mongo_store);
        // return EXIT_FAILURE; //despues descomitear
    }
    else
    {
        log_info(logger, "Tripulante %d Conexion con MongoStore exitosa", tripulante->id);
    }
    
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
    
    _Bool finalizo_tarea = true;
    //pthread_mutex_lock(&tripulante->activo);
    while (1)
    {
        if (finalizo_tarea)
        {
            tripulante->rafagas_consumidas = 0;
            pedirTarea(tripulante, socket_cliente);
            
            /*printf("Tiempo: %d\n", tripulante->tarea->tiempo);
            printf("Parámetro: %d\n", tripulante->tarea->parametro);
            printf("Posicion x-y: %d-%d\n", tripulante->tarea->posicion.posx, tripulante->tarea->posicion.posy);*/
            //Comprobacion que se guardo la tarea por defecto bien(despues borrar)
            //printf("Tiempo de la tarea %d\n", tripulante->tarea->tiempo);
            
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
                //Analizar si se eliminó en otra lista // TO DO
                list_add(lista_EXIT, tripulante);
                printf("Tripulante %d Bye Bye\n", tripulante->id);
                //MI ram elimina a este tripulante de su memoria
                //falta removerlo de la lista tripulante

                //Tripulante *tripulante1 = list_remove_by_condition(lista_tripulantes, mismo_id);
                Tripulante *tripulante2 = list_remove_by_condition(lista_READY, mismo_id);
                //list_remove_by_condition(lista_READY)
                tripulante->status = EXIT;
                //Comprobacion :despues borrar
                printf("id del tripulane removido de la cola de listos:%d\n", tripulante2->id);

                break;
            }
        }

        //Para que el dispatcher sepa que estamos listos
        sem_post(&listos);
        //Esperamos ser seleccionados
        pthread_mutex_lock(&tripulante->seleccionado);

        pthread_mutex_lock(&MXTRIPULANTE);
        list_remove_by_condition(lista_READY, mismo_id);
        cantidad_activos ++;
        tripulante->status = EXEC; 
        list_add(lista_EXEC, tripulante);
        pthread_mutex_unlock(&MXTRIPULANTE);


        if (hay_sabotaje)
        {
            chequear_activados();
            pthread_mutex_lock(&tripulante->activo);
            //el tripulante debe volve a ser seleccionado
            pthread_mutex_lock(&tripulante->seleccionado);
        }

        mover_tripulante_a_tarea(tripulante, socket_cliente);

        //TO-DO Deja de ejecutar y pasa a la lista de bloqueados (ANALIZARLO)
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
    //prueba de fifo en test.c
    int posicion_tarea_x = tripulante->tarea->posicion.posx;
    int posicion_tarea_y = tripulante->tarea->posicion.posy;

    int rafaga = 1;
    int retardo_cpu = config->RETARDO_CICLO_CPU;
    if (config->ALGORITMO == RR)
    {
        rafaga = config->QUANTUM;
    }
    int ciclos_consumidos = 0;

    while (tripulante->posicion->posx != posicion_tarea_x && ciclos_consumidos < rafaga)
    {
        if (!planificacion_activa || hay_sabotaje)
        {
            chequear_activados();
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

        if (config->ALGORITMO == RR)
        {
            ciclos_consumidos++;
        }
        sleep(retardo_cpu);
        enviar_posicion_mi_ram(tripulante, socket);
    }

    while (tripulante->posicion->posy != posicion_tarea_y && ciclos_consumidos < rafaga)
    {
        if (!planificacion_activa || hay_sabotaje)
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

        if (config->ALGORITMO == RR)
        {
            ciclos_consumidos++;
        }
        sleep(retardo_cpu);
        enviar_posicion_mi_ram(tripulante, socket);
    }

    //printf("Tripulante %d Posicion final %d-%d\n", tripulante->id, tripulante->posicion->posx, tripulante->posicion->posy);

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
    cantidad_activos --;
    if (cantidad_activos == 0)
    {
        //harcodeo un sabotaje por default
        //despues borrar
        t_sabotaje *sabotaje = malloc(sizeof(t_sabotaje));
        sabotaje->mensaje = "test";
        sabotaje->mensaje_length = strlen(sabotaje->mensaje);
        sabotaje->posicion = malloc(sizeof(Posicion));
        sabotaje->posicion->posx = 1;
        sabotaje->posicion->posy = 2;
        sabotaje->posicion->posy = 2;
        //
        inicio_sabotaje(sabotaje);
    }
}

void ir_a_la_posicion_sabotaje(Tripulante *tripulante, t_sabotaje *sabotaje, int socket)
{

    sleep(config->RETARDO_CICLO_CPU);
    enviar_posicion_mi_ram(tripulante, socket);

    while (1)
    {
        if (!planificacion_activa)
        {
            continue;
        }
        if (tripulante->posicion->posx != sabotaje->posicion->posx)
        {
            //Mueve uno en X
            if (sabotaje->posicion->posx > tripulante->posicion->posx)
            {
                tripulante->posicion->posx++;

                //aplicamos recursividad ?
                ir_a_la_posicion_sabotaje(tripulante, sabotaje, socket);
            }
            else if (sabotaje->posicion->posx < tripulante->posicion->posx)
            {
                tripulante->posicion->posx--;

                //aplicamos recursividad ?
                ir_a_la_posicion_sabotaje(tripulante, sabotaje, socket);
            }
        }
        //
        if (tripulante->posicion->posy != sabotaje->posicion->posy)
        {
            //Mueve uno en Y
            if (sabotaje->posicion->posy > tripulante->posicion->posy)
            {
                tripulante->posicion->posy++;

                //aplicamos recursividad ?
                ir_a_la_posicion_sabotaje(tripulante, sabotaje, socket);
            }
            else if (sabotaje->posicion->posx < tripulante->posicion->posx)
            {
                tripulante->posicion->posy--;

                //aplicamos recursividad ?
                ir_a_la_posicion_sabotaje(tripulante, sabotaje, socket);
            }
        }
        else
        {
            return;
        }
    }
}

Tripulante *buscar_el_mas_cercano(t_sabotaje *sabotaje)
{
    Tripulante *tripulante_retornar;
    double distancia_sabotaje = 999999999.9;
    for (int i = 0; i < list_size(lista_BLOCKEMERGENCIA); i++)
    {
        Tripulante *tripulante_sabotaje = list_get(lista_BLOCKEMERGENCIA, i);
        double distancia = sqrt(pow(sabotaje->posicion->posx - tripulante_sabotaje->posicion->posx, 2) + pow(sabotaje->posicion->posy - tripulante_sabotaje->posicion->posy, 2));
        if (distancia < distancia_sabotaje)
        {
            distancia_sabotaje = distancia;
            tripulante_retornar = tripulante_sabotaje;
        }
    }
    //printf("%d\n", distancia_sabotaje);
    return tripulante_retornar;
}

void inicio_sabotaje(t_sabotaje *sabotaje)
{
    hay_sabotaje = true;        //TO DO, se va a hacer en recepcion mensajes
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
    while (!list_is_empty(tripulantes_exec))
    { // rompe linea 375 (si hay_sabotaje = true)
        Tripulante *un_tripulante = list_remove(tripulantes_exec, 0);
        un_tripulante->status = BLOCKED_SABOTAJE;
    }
    //
    bool estas_ready(void *_tripulante)
    {
        Tripulante *tripulante = (Tripulante *)_tripulante;

        return tripulante->status == READY;
    }

    t_list *tripulantes_ready = list_filter(tripulantes, estas_ready);

    list_add_all(lista_BLOCKEMERGENCIA, tripulantes_ready);
    while (!list_is_empty(tripulantes_ready))
    {
        Tripulante *un_tripulante = list_remove(tripulantes_ready, 0);
        un_tripulante->status = BLOCKED_SABOTAJE;
    }

    //funcion buscar_el_mas_cercano

    Tripulante *tripulante_elegido = buscar_el_mas_cercano(sabotaje);
    int socket;
    ir_a_la_posicion_sabotaje(tripulante_elegido, sabotaje, socket); //TO DO pasa a exec al tripulante
    invocar_fsck();
    desbloquear_tripulantes();
    hay_sabotaje = false;
    printf("soy un sabotaje\n");
}

void invocar_fsck()
{
    //TO DO
    int conexion_a_mongo_store = crear_conexion(config->IP_I_MONGO_STORE, config->PUERTO_I_MONGO_STORE);

    t_aviso_fsck fcsk;
    t_package paquete = ser_fcsk(fcsk);

    if (conexion_a_mongo_store > 0)
    {
        sendMessage(paquete, conexion_a_mongo_store);
    }
}

void desbloquear_tripulantes()
{

    while (!list_is_empty(lista_BLOCKEMERGENCIA))
    {
        Tripulante *un_tripulante = list_remove(lista_BLOCKEMERGENCIA, 0);
        un_tripulante->status = READY;
        pthread_mutex_unlock(&un_tripulante->activo);
        list_add(lista_READY, un_tripulante);
    }
}