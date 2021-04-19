#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include <string.h>

t_config * leer_config_file(char*);


typedef enum{
    FIFO,
    HRRN,
    SJF_SD,
    RR
} _alg_planificacion; 

typedef struct {
    char* IP_COMANDA;
    int PUERTO_COMANDA;
    char* IP_RESTAURANTE;
    int PUERTO_RESTAURANTE;
    int PUERTO_ESCUCHA;
    int RETARDO_CICLO_CPU;
    int GRADO_DE_MULTIPROCESAMIENTO;
    _alg_planificacion ALGORITMO_DE_PLANIFICACION;
    float ALPHA;
    int ESTIMACION_INICIAL;
    char* REPARTIDORES;
    char* FRECUENCIA_DE_DESCANSO;
    char* TIEMPO_DE_DESCANSO;
    char* ARCHIVO_LOG;
    char* PLATOS_DEFAULT;
    int POSICION_REST_DEFAULT_X;
    int POSICION_REST_DEFAULT_Y;    
} t_config_app;

typedef struct {
    char* IP_CLIENTE;
    char* IP;
    int PUERTO;
    char* ARCHIVO_LOG;
    int POSICION_X;
    int POSICION_Y;
    char* ID_CLIENTE;

} t_config_cliente;

typedef enum{
    LRU,
    CLOCK
} _alg_reemplazo;

typedef struct {
    int PUERTO_ESCUCHA;
    int TAMANIO_MEMORIA;
    int TAMANIO_SWAP;
    int FRECUENCIA_COMPACTACION;
    _alg_reemplazo ALGORITMO_REEMPLAZO;
    char* ARCHIVO_LOG;    
} t_config_comanda;

typedef struct {
    int PUERTO_ESCUCHA;
    char* IP_SINDICATO;
    int PUERTO_SINDICATO;
    char* IP_APP;
    int PUERTO_APP;
    int QUANTUM;
    char* ARCHIVO_LOG;
    _alg_planificacion ALGORITMO_PLANIFICACION;
    char* NOMBRE_RESTAURANTE;
    int RETARDO_CICLO_CPU;
} t_config_restaurante;

typedef struct {
    int BLOCK_SIZE;
    int BLOCKS;
    int PUERTO_ESCUCHA;
    char* PUNTO_MONTAJE;
} t_config_sindicato;

t_config_app* leerConfigApp(t_config* config);
t_config_cliente* leerConfigCliente(t_config* config);
t_config_comanda* leerConfigComanda(t_config* config);
t_config_restaurante* leerConfigRestaurante(t_config* config);
t_config_sindicato* leerConfigSindicato(t_config* config);
#endif