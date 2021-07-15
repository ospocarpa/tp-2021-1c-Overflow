#include "consola.h"
//inline
_Bool planificacion_activa = false;
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

    //system("clear");
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
            //desconexion = true;
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

    int cantidad_argumentos;

    // estado_mensaje estado;

    cantidad_argumentos = obtener_cantidad_argumentos(tokens);

    switch (operacion)
    {

    case LISTAR_TRIPULANTES:

        if (cantidad_argumentos == 0)
        {
        }
        else
        {

            printf("Cantidad de argumentos invalido\n");
        }

        break;

    case EXPULSAR_TRIPULANTE:
        printf("Entro expulsar tripulante\n");

        if (cantidad_argumentos == 1)
        {
            //completar

            if (!es_un_numero(tokens[1]))
            {
                // se podria analizar solo hasta tokens[1]
                printf("El argumento es invalido\n");

                return;
            }
            //completar
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
            detener();
        }
        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;

    case OBTENER_BITACORA:
        printf("entre a obtener bitacora\n");

        if (cantidad_argumentos == 1)
        {
            printf("cantidad de argumentos correctos\n");
            //completar
            if (!es_un_numero(tokens[1]))
            { // existe el tripulante?

                printf("El argumento es invalido\n");

                return;
            }
            printf("argumentos correctos\n");
            //completar
        }
        else
        {
            printf("Cantidad de argumentos invalido\n");
        }

        break;

    case INICIAR_PATOTA:
        printf("entre a iniciar patota\n");

            if (cantidad_argumentos >= 2 && cantidad_argumentos <= atoi(tokens[1]) + 2){
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

// void ejecutar_operacion(Tripulante *tripulante)
// {
//new
/*
    Estado inicial: bloqueado
    alistate();
    
    ejecutar(){
        Código de ejecutar
        switch(siguiente_transicion){
            case 1: 
                bloqueate();
                break;
            case 2: 
                finalizate();
                break;
            case 3: 
                alistate();
                break;
        }
        //sleep(1);
    };

    bloqueate(){
        Código de bloqueo
        alistate();
    }
    
    alistate(){
        Código de alistate
        switch(siguiente_transicion){
            case 1: 
                ejecutar();
                break;
        }
    }
    //finish*/
// }

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

void detener()
{

    if (planificacion_activa)
    {
        planificacion_activa = false;
        logger_info("[Planificacion detenida]");
    }
    else
    {
        logger_info("[La planificacion ya está desactivada]");
    }
}

void activar_planificacion()
{
    if (!planificacion_activa)
    {
        planificacion_activa = true;
        logger_info("[Planificacion activada]");
        planificar();
    }
    else
    {
        logger_info("[La planificacion ya está activada]");
    }
}
void planificar()
{

    if (planificacion_activa)
    {

        //TODO
    }
    else
    {
        logger_info("La planificación está desactivada");
    }
}
