#ifndef TAD_MONGO_STORE_H
#define TAD_MONGO_STORE_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <config_utils.h>
#include <commons/collections/list.h>

typedef struct
{
    char* punto_montaje; 
    t_list posiciones_sabotaje; //Lista [Posiciones]
} Mongo_Store;

typedef struct 
{
    __uint32_t block_size;
    __uint32_t blocks;
    _Bool bitmap;
} SuperBloque;

typedef struct 
{
    __uint32_t size;
    __uint32_t block_count;
    t_list blocks;
    char caracter_llenado;
    char* md5_archivo;
} File;

t_config_mongo_store *config;


#endif
