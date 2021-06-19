#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include <string.h>

typedef enum{
    FIFO,
    RR
} alg_planificacion;

typedef struct {
    char* IP_MODULO;
    int PUERTO_MODULO;
    char* IP_MI_RAM_HQ;
    int PUERTO_MI_RAM_HQ;
    char* IP_I_MONGO_STORE;
    int PUERTO_I_MONGO_STORE;
    int GRADO_MULTITAREA;
    alg_planificacion ALGORITMO;
    int QUANTUM;
    int DURACION_SABOTAJE;
    int RETARDO_CICLO_CPU;
    char* ARCHIVO_LOG;
} t_config_discordiador;

typedef struct {
    char* IP_MODULO;
    int PUERTO;
    char* PUNTO_MONTAJE;
    int TIEMPO_SINCRONIZACION;
    char* POSICIONES_SABOTAJE;
    int BLOCK_SIZE;
    int BLOCKS;
    char* IP_DISCORDIADOR;
    int PUERTO_DISCORDIADOR;
    char* ARCHIVO_LOG;
} t_config_mongo_store;

t_config * leer_config_file(char*);
t_config_discordiador* leerConfigDiscordiador(t_config* config);
t_config_mongo_store* leer_config_mongo_store(t_config* config);

#endif