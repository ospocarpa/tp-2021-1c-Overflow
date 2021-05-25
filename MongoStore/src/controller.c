#include "controller.h"

void method_sigusr1(){
    printf("Cuando reciba sigusr1\n");
}

void init_mongo_store(){
    //Inicialización del file system
    create_punto_montaje(t_config_mongo_store* config_mongo_store){}
    create_super_bloque(t_config_mongo_store* config_mongo_store){}
    create_files(t_config_mongo_store* config_mongo_store){}
    create_bitacoras(t_config_mongo_store* config_mongo_store){}    
}

void create_punto_montaje(t_config_mongo_store* config_mongo_store){}
void create_super_bloque(t_config_mongo_store* config_mongo_store){}
void create_files(t_config_mongo_store* config_mongo_store){}
void create_bitacoras(t_config_mongo_store* config_mongo_store){}