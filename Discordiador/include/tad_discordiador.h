#ifndef TAD_DISCORDIADOR_H
#define TAD_DISCORDIADOR_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <TAD.h>
#include <tests.h>

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
    status_tripulante status;
    Posicion *posicion;
    //Tarea *tarea;
    t_info_tarea *tarea;
    int patota_id;
    int rafagas_consumidas;
    pthread_mutex_t activo; //mutex o binario ?? implementar binario
                            //desabilitado por defecto

    pthread_mutex_t seleccionado; //desahibiliado por defecto
                                  //habilitado por dispatcher
    pthread_mutex_t sabotaje;
    //defino los sockets que se conectaran a ambos modulos
    int socket_cliente_mongo_store;
    int socket_cliente_mi_ram;

} Tripulante;

// typedef enum
// {
//     INICIAR_PATOTA,
//     LISTAR_TRIPULANTES,
//     EXPULSAR_TRIPULANTE,
//     INICIAR_PLANIFICACION,
//     PAUSAR_PLANIFICACION,
//     OBTENER_BITACORA,
//     SALIR
// } cod_operacion;

// typedef enum
// {

//     SUCCESS = 1,
//     ERROR = 2,
//     ERROR_CONEXION = 3

// } estado_mensaje; //estado del mensaje en consola

#endif