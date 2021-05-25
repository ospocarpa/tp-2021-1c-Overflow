#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <stdbool.h>
#include <global.h>
#include <config_utils.h>

    void method_sigusr1();
    void init_mongo_store();
    void create_punto_montaje(t_config_mongo_store* config_mongo_store);
    void create_super_bloque(t_config_mongo_store* config_mongo_store);
    void create_files(t_config_mongo_store* config_mongo_store);
    void create_bitacoras(t_config_mongo_store* config_mongo_store);

#endif