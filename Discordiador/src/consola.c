#include "consola.h"

void mostrar_consola()
{

    printf(
        "\n------------------------------------------\n"
        "BIENVENIDO A LA CONSOLA DEL DISCORDIADOR\n"
        "Lista de comandos: \n"
        "INICIAR_PLANIFICACION\n"
        "PAUSAR_PLANIFICACION\n"
        "LISTAR_TRIPULANTES\n"
        "EXPULSAR_TRIPULANTE [Numero de tripulante]\n"
        "OBTENER_BITACORA [Numero de tripulante]\n"
        "INICIAR_PATOTA [Cantidad de tripulantes] [Ruta] [Coordenadas]\n"
        "SALIR\n"

    );
}

void liberar_puntero_doble(char **puntero_doble)
{

    int i = 0;
    while (*(puntero_doble + i) != NULL)
    {

        free(*(puntero_doble + i));
        i++;
    }

    free(puntero_doble);
}

bool leer_consola(void)
{
    pthread_mutex_init(&SEM_PAUSAR_PLANIFICACION, 0);
    hay_sabotaje = false;
    while (1)
    {
        mostrar_consola();
        int tamanio_buffer = 128;

        char *buffer = malloc(tamanio_buffer + 1);

        fgets(buffer, tamanio_buffer, stdin);

        string_trim_right(&buffer);

        *(buffer + string_length(buffer)) = '\0';

        if (string_length(buffer) + 1 >= tamanio_buffer)
        {
            printf("Excedistes por mucho los caracteres en la consola\n");
        }

        buffer = realloc(buffer, string_length(buffer) + 1);

        char **tokens = string_split(buffer, " ");

        string_to_upper(tokens[0]);

        if (string_equals_ignore_case(tokens[0], "INICIAR_PATOTA"))
        {
            printf(">>>>>INICIAR_PATOTA<<<<<\n");
            parsear_mensaje(INICIAR_PATOTA, tokens);
            printf("========================\n");
        }

        else if (string_equals_ignore_case(tokens[0], "LISTAR_TRIPULANTES"))
        {
            printf(">>>>>LISTAR_TRIPULANTES<<<<<\n");
            parsear_mensaje(LISTAR_TRIPULANTES, tokens);
            printf("========================\n");
        }
        else if (string_equals_ignore_case(tokens[0], "EXPULSAR_TRIPULANTE"))
        {
            printf(">>>>>EXPULSAR_TRIPULANTE<<<<<\n");
            parsear_mensaje(EXPULSAR_TRIPULANTE, tokens);
            printf("========================\n");
        }
        else if (string_equals_ignore_case(tokens[0], "INICIAR_PLANIFICACION"))
        {
            printf(">>>>>INICIAR_PLANIFICACION<<<<<\n");
            parsear_mensaje(INICIAR_PLANIFICACION, tokens);
            printf("========================\n");
        }
        else if (string_equals_ignore_case(tokens[0], "PAUSAR_PLANIFICACION"))
        {
            printf(">>>>>PAUSAR_PLANIFICACION<<<<<\n");
            parsear_mensaje(PAUSAR_PLANIFICACION, tokens);
            printf("========================\n");
        }
        else if (string_equals_ignore_case(tokens[0], "OBTENER_BITACORA"))
        {
            printf(">>>>>OBTENER_BITACORA<<<<<\n");
            parsear_mensaje(OBTENER_BITACORA, tokens);
            printf("========================\n");
        }
        else if (string_starts_with(tokens[0], "SALIR"))
        {

            printf(">>>>>SALIR<<<<<\n");
            free(buffer);
            liberar_puntero_doble(tokens);
            printf("\nTERMINO DE LEER CONSOLA|\n");
            printf("------------------------------------------\n");
            return false;
        }
        else
        {
            printf("No es valido lo ingresado\n");
        }

        free(buffer);

        liberar_puntero_doble(tokens);
        sleep(2);
    }
    printf("termino leer consola|\n");
    printf("\n------------------------------------------\n");
    return false;
}

void parsear_mensaje(op_code operacion, char **tokens)
{

    int cantidad_argumentos = obtener_cantidad_argumentos(tokens);
    printf("Argumentos: %d\n", cantidad_argumentos);
    switch (operacion)
    {

    case LISTAR_TRIPULANTES:

        if (cantidad_argumentos == 0)
        {
            listar_tripulantes();
        }
        else
        {

            printf("Cantidad de argumentos invalido\n");
        }

        break;
    case EXPULSAR_TRIPULANTE:
        if (cantidad_argumentos == 1)
        {
            if (!es_un_numero(tokens[1]))
            {
                printf("El argumento es invalido\n");
            }
            else
            {
                expulsar_tripulante(atoi(tokens[1]));
            }
        }
        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;

    case INICIAR_PLANIFICACION:
        printf("Entro a iniciar planificacion\n");

        if (cantidad_argumentos == 0)
        {
            activar_planificacion();
        }
        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;

    case PAUSAR_PLANIFICACION:
        printf("Entro a pausar planificacion\n");

        if (cantidad_argumentos == 0)
        {
            detener_planificacion();
        }
        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;
    case OBTENER_BITACORA:
        if (cantidad_argumentos == 1)
        {
            printf("cantidad de argumentos correctos\n");
            if (!es_un_numero(tokens[1]))
            {
                printf("El argumento es invalido\n");
                return;
            }
            else
            {
                obtener_bitacora(atoi(tokens[1]));
            }
        }

        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;

    case INICIAR_PATOTA:
        printf("entre a iniciar patota\n");

        if (cantidad_argumentos >= 2 && cantidad_argumentos <= atoi(tokens[1]) + 2)
        {
            iniciar_patota(tokens);
        }

        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;

    default:
        break;
    }
}
// deberia ir a la shared ?
int existe_archivo(const char *ruta)
{
    FILE *archivo = fopen(ruta, "r+");

    if (archivo == NULL)
    {

        return false;
    }

    fclose(archivo);
    return true;
}

void detener_planificacion()
{

    if (planificacion_activa)
    {
        planificacion_activa = false;
        log_info(logger, "[Planificacion detenida]");
        
        t_list *tripulantes = get_tripulantes_all();
        for (int c = 0; c < list_size(tripulantes); c++)
        {
            Tripulante *tripulante = list_get(tripulantes, c);
            sem_wait(&tripulante->activo);
        }
    }
    else
    {
        log_info(logger, "[La planificacion ya está desactivada]");
    }
}

void activar_planificacion()
{
    if (!planificacion_activa)
    {
        planificacion_activa = true;
        log_info(logger, "[Planificacion activada]");
        planificar();
    }
    else
    {
        log_info(logger, "[La planificacion ya está activada]");
    }
}
void planificar()
{
    t_list *tripulantes = get_tripulantes_all();
    for (int c = 0; c < list_size(tripulantes); c++)
    {
        Tripulante *tripulante = list_get(tripulantes, c);
        //printf("Pasa por aca\n");
        sem_post(&tripulante->activo);
    }
}
void listar_tripulantes()
{
    t_list *tripulantes = get_tripulantes_all();
    char *format = "%d/%m/%y %H:%M:%S";
    char *timestamp = temporal_get_string_time(format);
    printf("Estado de la nave: %s\n", timestamp);

    for (int c = 0; c < list_size(tripulantes); c++)
    {
        Tripulante *tripulante = list_get(tripulantes, c);
        printf("Tripulante: %d    Patota: %d    Status: %s\n", tripulante->id, tripulante->patota_id, get_status_string(tripulante->status));
    }
}

void iniciar_patota(char **tokens)
{
    int cantidad_argumentos = obtener_cantidad_argumentos(tokens);

    if (!es_un_numero(tokens[1]))
    {
        printf("El argumento es invalido\n");
        return;
    }

    //tokens[2]: path del archivo
    if (!existe_archivo(tokens[2]))
    {

        log_error(logger, "No se encontro el archivo %s ", tokens[2]);
        return;
    }
    for (int i = 0; i < cantidad_argumentos - 2; i++)
    {
        char **coordenada = string_split(tokens[3 + i], "|");
        if (!es_un_numero(coordenada[0]) || !es_un_numero(coordenada[1]))
        {
            log_info(logger, "Coordenadas invalidas %s %s ", coordenada[0], coordenada[1]);
            return;
        }
        liberar_puntero_doble(coordenada);
    }
    t_iniciar_patota datosPatota;

    cargarTripulante(&datosPatota, tokens, cantidad_argumentos);
    mostrar_datos_patota(&datosPatota);

    mostrar_iniciar_patota(datosPatota);
    t_package paquete = ser_cod_iniciar_patota(datosPatota);

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
        log_info(logger, "Conexion con Mi-RAM-HQ exitosa");
    }

    sendMessage(paquete, socket_cliente);

    //Intento de espera respuesta de confirmacion de carga de los pcb

    bool respuesta;

    recv(socket_cliente, &respuesta, sizeof respuesta, 0);
    if (!respuesta)
    {
        log_error(logger, "No se puede crear la patota/tripulanes");
        return;
    }

    log_info(logger, " Empezando a crear los  tripulanes...");

    Patota *patota_new = map_to_patota(datosPatota);
    mostrar_t_patota(patota_new);
    crearHilosTripulantes(patota_new);
    liberar_conexion(socket_cliente);
}

void expulsar_tripulante(int tripulante_id)
{
    int patota_id = 0;
    t_list *tripulantes = get_tripulantes_all();
    for (int c = 0; c < list_size(tripulantes); c++)
    {
        Tripulante *tripulante = list_get(tripulantes, c);
        if (tripulante->id == tripulante_id)
        {
            patota_id = tripulante->patota_id;
            break;
        }
    }

    int conexion_a_miram = crear_conexion(config->IP_MI_RAM_HQ, config->PUERTO_MI_RAM_HQ);

    Tripulante *tripulante_a_expulsar = NULL;
    tripulante_a_expulsar = tripulante_segun_id(tripulante_id);
    if (tripulante_a_expulsar == NULL)
    {
        printf("tripulante no exite\n");
        return;
    }
    if (tripulante_a_expulsar->status == EXIT)
    {
        printf("tripulante %d ya fue expulsado antes\n", tripulante_a_expulsar->id);
        return;
    }
    tripulante_a_expulsar->expulsado = true;
    tripulante_a_expulsar->status = EXIT;
    printf("tripulante %d se va expulsar\n", tripulante_a_expulsar->id);
    // una opcion podria ser forzar terminar el hilo de ese tripulante para no modificar disenio

    t_expulsar_tripulante data;
    data.patota_id = patota_id;
    data.tripulante_id = tripulante_id;
    t_package paquete = ser_cod_expulsar_tripulante(data);

    if (conexion_a_miram > 0)
    {
        sendMessage(paquete, conexion_a_miram);
    }
}

void obtener_bitacora(int tripulante_id)
{
    int conexion_a_mongostore = crear_conexion(config->IP_I_MONGO_STORE, config->PUERTO_I_MONGO_STORE);

    char *nombre_file = string_new();
    string_append_with_format(&nombre_file, "tripulante%s.ims", string_itoa(tripulante_id));

    t_file file;
    file.nombre_file = malloc(strlen(nombre_file));
    file.contenido = "";
    file.long_contenido = strlen(file.contenido);
    strcpy(file.nombre_file, nombre_file);
    file.long_nombre_file = strlen(file.nombre_file);

    if (conexion_a_mongostore > 0)
    {
        t_package paquete = ser_get_file_bitacora(file);
        sendMessage(paquete, conexion_a_mongostore);

        t_file sabotaje;
        t_package paquete_respuesta = recibir_mensaje(conexion_a_mongostore);
        sabotaje = des_get_file(paquete_respuesta);
        mostrar_file(sabotaje);
    }
}