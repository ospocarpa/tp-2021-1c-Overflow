#include "controller.h"

void method_sigusr1(){
    printf("Cuando reciba sigusr1\n");
    Sabotaje* sabotaje = malloc(sizeof(Sabotaje));

    sabotaje->mensaje = "Test";
    sabotaje->mensaje_length = strlen(sabotaje->mensaje);
    Posicion* posicion = malloc(sizeof(Posicion));

    //Retirar de la lista del config
    posicion->posx = 1;
    posicion->posy = 1;
    sabotaje->posicion = posicion;

    int conexion_a_discordiador = crear_conexion(config_global_mongo_store->IP_DISCORDIADOR, config_global_mongo_store->PUERTO_DISCORDIADOR);
    
    //printf("Ini: %d\n", conexion_a_discordiador);

    t_paquete* paquete = serializar_I_SABOTAJE(sabotaje);
    if(conexion_a_discordiador>0){
        sendMessage(paquete, conexion_a_discordiador);
    }
}

void init_mongo_store(){
    //printf("Puerto: %d\n", config->PUERTO);
    //Inicialización del file system
    
    create_punto_montaje(config_global_mongo_store);
    create_file_super_bloque(config_global_mongo_store);
    create_file_blocks(config_global_mongo_store);
    create_dir_files(config_global_mongo_store);
    create_dir_bitacoras(config_global_mongo_store);
}

void create_punto_montaje(t_config_mongo_store* config_mongo_store){

    if(debug)
        printf("%s\n", config_mongo_store->PUNTO_MONTAJE);
    
    char** partes = string_split(config_mongo_store->PUNTO_MONTAJE, "/");
    t_list* paths = list_create();
    void aLaListaPaths(char *item) {
        list_add(paths, item);
    }
    string_iterate_lines(partes, aLaListaPaths);
    /*
        /home/utnso/polus =>    [home, utnso, polus]
    */

    char* path_punto_montaje = malloc(strlen(config_mongo_store->PUNTO_MONTAJE));
    string_append_with_format(&path_punto_montaje, "%s", "");
    char* path; bool existe; int status;
    for(int c=0; c<list_size(paths); c++){
        path = list_get(paths, c);
        string_append_with_format(&path_punto_montaje, "%s", "/");
        string_append_with_format(&path_punto_montaje, "%s", path);
        
        existe = existePath(path_punto_montaje);
        if(debug){
            printf("%s ", path_punto_montaje);
            printf("%d\n", existe);
        }
        if(existe == 0){
            if(debug) printf("Creado\n");
            status = mkdir(path_punto_montaje, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);        
            //printf("Status %d\n");
        }
    }
}

void create_file_super_bloque(t_config_mongo_store* config_mongo_store){
    int status;

    //Crear directorio para super bloque
    char* path_super_bloque = string_new();
    char* punto_montaje = get_path_punto_montaje();
    string_append_with_format(&path_super_bloque, "%s", punto_montaje);
    string_append_with_format(&path_super_bloque, "%s", "/SuperBloque.ims");
    
    int fd = open(path_super_bloque, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    printf("State fd: %d", fd);

    //printf("Block size: %d Blocks: %d\n", config_mongo_store->BLOCK_SIZE, config_mongo_store->BLOCKS);
    int block_size = config_mongo_store->BLOCK_SIZE;
    int blocks = config_mongo_store->BLOCKS;

    //PENDIENTE: crear bitmap
    int bitmap = 2000;

    int offset = 0;
    int file_size = sizeof(uint32_t) * 3;
    printf("File size: %d\n", file_size);
    ftruncate(fd, file_size);

    if(fd){
        void* punteroBits = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
        memcpy(punteroBits+offset, &block_size, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
        memcpy(punteroBits+offset, &blocks, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
        memcpy(punteroBits+offset, &bitmap, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
    }
    printf("Fin\n");
}

void create_file_blocks(t_config_mongo_store* config_mongo_store){
    int status;

    //Crear directorio para bloques
    char* path_super_bloque = string_new();
    char* punto_montaje = get_path_punto_montaje();
    string_append_with_format(&path_super_bloque, "%s", punto_montaje);
    string_append_with_format(&path_super_bloque, "%s", "/Blocks.ims");
    
    int fd = open(path_super_bloque, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
}

void create_dir_files(t_config_mongo_store* config_mongo_store){
    int status;

    //Crear directorio files
    char* path_files = get_path_files();
    status = mkdir(path_files, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(debug) printf("Status files: %d\n", status);
}

void create_dir_bitacoras(t_config_mongo_store* config_mongo_store){
    int status;

    //Crear directorio files
    char* path_bitacoras = get_path_bitacoras();
    status = mkdir(path_bitacoras, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(debug) printf("Status bitacoras: %d\n", status);
}

void init_protocolo_fsck(){

}