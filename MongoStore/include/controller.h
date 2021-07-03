#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <stdbool.h>
#include "global.h"
#include "TAD.h"
#include "config_utils.h"
#include "filesystem.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <commons/bitarray.h>
#include <commons/collections/list.h>

    extern t_config_mongo_store* config_global_mongo_store;
    extern t_filesystem filesystem;

    void method_sigusr1();
    void init_mongo_store();
    void create_punto_montaje(t_config_mongo_store* config_mongo_store);
    void create_file_super_bloque(t_config_mongo_store* config_mongo_store);
    void create_file_blocks(t_config_mongo_store* config_mongo_store);
    void create_dir_files(t_config_mongo_store* config_mongo_store);
    void create_dir_bitacoras(t_config_mongo_store* config_mongo_store);
    void agregar_recurso(t_operation_file_recurso file_input);
    void retirar_recurso(t_operation_file_recurso file_input);
    void init_protocolo_fsck();

    // Asociados a la respuesta de los mensajes
    void create_recurso(t_create_file create_get_file);
    void create_tripulante_bitacora(t_create_file create_get_file);
    t_file get_recurso(char* nombre_file);
    t_file get_bitacora_tripulante(t_file file_input);

#endif