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
#include <commons/collections/list.h>

    void method_sigusr1();
    void init_mongo_store();
    void create_punto_montaje(t_config_mongo_store* config_mongo_store);
    void create_file_super_bloque(t_config_mongo_store* config_mongo_store);
    void create_file_blocks(t_config_mongo_store* config_mongo_store);
    void create_dir_files(t_config_mongo_store* config_mongo_store);
    void init_protocolo_fsck();

#endif