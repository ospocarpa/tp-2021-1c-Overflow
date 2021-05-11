#ifndef TAD_DISCORDIADOR_H
#define TAD_DISCORDIADOR_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <TAD.h>
#include <tests.h>

typedef enum
{
    NEW,
    READY,
    EXEC,
    BLOCKED,
    EXIT
} status_planificacion;

typedef struct
{
    t_list *patotas; //Lista [Patota]
    char *algoritmo;
} Discordiador;

typedef struct
{
    int id;
    t_list *tareas;      //Lista [Tarea]
    t_list *tripulantes; //Lista [Tripulante]
} Patota;

typedef struct
{
    int id;
    status_planificacion status;
    Posicion *posicion;
    Tarea *tarea;
    int patota_id;
} Tripulante;

typedef enum
{
    INICIAR_PATOTA,
    LISTAR_TRIPULANTES,
    EXPULSAR_TRIPULANTE,
    INICIAR_PLANIFICACION,
    PAUSAR_PLANIFICACION,
    OBTENER_BITACORA,
    SALIR
} cod_operacion;
typedef enum
{

    SUCCESS = 1,
    ERROR = 2,
    ERROR_CONEXION = 3

} estado_request; //estado_peticion

#endif