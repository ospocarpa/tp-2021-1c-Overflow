#include "controller.h"

void method_sigusr1(){
    if(debug) printf("Cuando reciba sigusr1\n");
    t_sabotaje* sabotaje = malloc(sizeof(t_sabotaje));

    sabotaje->mensaje = "Test";
    sabotaje->mensaje_length = strlen(sabotaje->mensaje);

    int indice = list_size(config_global_mongo_store->POSICIONES_SABOTAJE);
    if(debug) printf("Indice: %d\n", indice);
    if(indice==0) return;
    Posicion* posicion = list_get(config_global_mongo_store->POSICIONES_SABOTAJE, indice-1);
    sabotaje->posicion = posicion;
    list_remove(config_global_mongo_store->POSICIONES_SABOTAJE, indice-1);

    int conexion_a_discordiador = crear_conexion(config_global_mongo_store->IP_DISCORDIADOR, config_global_mongo_store->PUERTO_DISCORDIADOR);
    //printf("Ini: %d\n", conexion_a_discordiador);

    t_package paquete = serializar_I_SABOTAJE(sabotaje);
    mostrarSabotaje(sabotaje);
    if(conexion_a_discordiador>0){
        sendMessage(paquete, conexion_a_discordiador);
    }
}

void init_mongo_store(){
    //printf("Puerto: %d\n", config->PUERTO);
    //Inicialización del file system
    init_filesystem();
    
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
    char* path_super_bloque = get_path_super_bloque();
    
    bool existe_super_bloque = existePath(path_super_bloque);
    int fd = open(path_super_bloque, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    if(debug) printf("State fd: %d\n", fd);
    //printf("Block size: %d Blocks: %d\n", config_mongo_store->BLOCK_SIZE, config_mongo_store->BLOCKS);
    int block_size = config_mongo_store->BLOCK_SIZE;
    int blocks = config_mongo_store->BLOCKS;
    int file_size = sizeof(uint32_t) * 2 + blocks/8;
    ftruncate(fd, file_size);

    if(!existe_super_bloque){
        //Bitmap
        void* puntero_bitmap = malloc(blocks/8);
        if(debug) printf("Tamaño bitmap: %d\n", blocks/8);
        t_bitarray* bitmap = bitarray_create_with_mode(puntero_bitmap, blocks/8, LSB_FIRST);
        clean_bit_map(bitmap);

        int offset = 0;
        if(debug) printf("File size: %d\n", file_size);

        /*void* punteroBits = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
        memcpy(punteroBits+offset, &block_size, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
        memcpy(punteroBits+offset, &blocks, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
        memcpy(punteroBits+offset, puntero_bitmap, blocks/8);
        offset+=sizeof(uint32_t);

        memcpy(filesystem.stream, punteroBits, file_size);  
        printf("Blocks size: %d Blocks: %d\n", block_size, blocks);*/

        filesystem.stream = malloc(file_size);
        filesystem.stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
        memcpy(filesystem.stream+offset, &block_size, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
        memcpy(filesystem.stream+offset, &blocks, sizeof(uint32_t));
        offset+=sizeof(uint32_t);
        memcpy(filesystem.stream+offset, puntero_bitmap, blocks/8);
        offset+=blocks/8;
  
        printf("Blocks size: %d Blocks: %d\n", block_size, blocks);

        /*
        //Prueba
        printf("\nInicio\n");
        void* puntero_bitmap_prueba = malloc(blocks/8);
        
        memcpy(puntero_bitmap_prueba, filesystem.stream_copy + (sizeof(uint32_t) * 2), blocks/8);
        t_bitarray* bitmap2 = bitarray_create_with_mode(puntero_bitmap_prueba, blocks/8, LSB_FIRST);
        printf("Mostrar bit map\n");
        print_bit_map(bitmap2);
        bitarray_set_bit(bitmap2, 5);
        bitarray_set_bit(bitmap2, 6);
        printf("Mostrar bit map después del cambio\n");
        print_bit_map(bitmap2);

        printf("Mostrar bit map original después del cambio\n");
        print_bit_map(bitmap);*/
    }else{
        filesystem.stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
    }

    memcpy(filesystem.stream_copy, filesystem.stream, file_size);      //Lo paso a la copia que se usará
}

void create_file_blocks(t_config_mongo_store* config_mongo_store){
    int status;

    //Crear directorio para bloques
    char* path_super_bloque = string_new();
    char* punto_montaje = get_path_punto_montaje();
    string_append_with_format(&path_super_bloque, "%s", punto_montaje);
    string_append_with_format(&path_super_bloque, "%s", "/Blocks.ims");
    
    bool exist_file = existePath(path_super_bloque);
    if(debug) printf("Creación del archivo bloque: %d\n", exist_file);

    int block_size = config_mongo_store->BLOCK_SIZE;
    int blocks = config_mongo_store->BLOCKS;
    int file_size = block_size * blocks;
    //printf("Bloque: %s - %d\n", path_super_bloque, file_size);
    int fd = open(path_super_bloque, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    ftruncate(fd, file_size);
    if(!exist_file){
        void* stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
        memcpy(filesystem.blocks, stream, file_size);        
    }else{
        printf("Blocks usado\n");
        filesystem.blocks = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
    }
    printf("Tamaño bloques: %d\n", sizeof(filesystem.blocks));
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

void create_recurso(t_create_file create_get_file){
    char* filename = create_get_file.nombre_file;
    char* caracter_llenado = string_repeat(create_get_file.caracter, 1);

    //printf("File: %s\n", filename);
    char* path_file_ims = get_path_file_recurso(filename);
    //printf("File ims: %s\n", path_file_ims);

    //Crear archivo recurso.ims
    int status = create_file(path_file_ims);
    if(debug) printf("Status archivo recurso ims: %d\n", status);
    
    t_config* file_ims = config_create(path_file_ims);
	config_set_value(file_ims, "SIZE", "0");
	config_set_value(file_ims, "BLOCK_COUNT", "0");
	config_set_value(file_ims, "BLOCKS", "[]");
	config_set_value(file_ims, "CARACTER_LLENADO", caracter_llenado);
	config_set_value(file_ims, "MD5_ARCHIVO", "");
	config_save_in_file(file_ims, path_file_ims);
}

void create_tripulante_bitacora(t_create_file create_get_file){
    char* filename = create_get_file.nombre_file;
    char* caracter_llenado = string_repeat(create_get_file.caracter, 1);

    //printf("File: %s\n", filename);
    char* path_file_ims = get_path_file_bitacora(filename);
    //printf("File ims: %s\n", path_file_ims);

    //Crear archivo recurso.ims
    int status = create_file(path_file_ims);
    if(debug) printf("Status archivo recurso ims: %d\n", status);
    
    t_config* file_ims = config_create(path_file_ims); 
    //char* blockSize = string_itoa(configSindicato->BLOCK_SIZE);
	//char* blocks = string_itoa(configSindicato->BLOCKS);
	config_set_value(file_ims, "SIZE", "0");
	config_set_value(file_ims, "BLOCKS", "[]");
	config_save_in_file(file_ims, path_file_ims);
}

t_file get_recurso(char* nombre_file){
    t_file file;

    printf("Archivo: %s\n", nombre_file);
    if(existe_nombre_file_recurso(nombre_file)){
        file.nombre_file = nombre_file;
        file.contenido = get_contenido_recurso(nombre_file);
        file.long_nombre_file = strlen(file.nombre_file);
        file.long_contenido = strlen(file.contenido);
    }else{
        log_info(logger, "No existe archivo");
    }
    return file;
}

t_file get_bitacora_tripulante(t_file file_input){
    t_file file;

    printf("Archivo: %s\n", file_input.nombre_file);
    if(existe_nombre_file_bitacora(file_input.nombre_file)){
        file.nombre_file = file_input.nombre_file;
        file.contenido = get_contenido_bitacora(file.nombre_file);
        file.long_nombre_file = strlen(file.nombre_file);
        file.long_contenido = strlen(file.contenido);
    }else{
        log_info(logger, "No existe archivo");
    }
    
    return file;
}

void update_bitacora(t_file file_input){
    printf("Archivo: %s\n", file_input.nombre_file);
    if(!existe_nombre_file_bitacora(file_input.nombre_file)){
        t_create_file create_get_file;
        create_get_file.caracter = ' ';
        create_get_file.nombre_file = file_input.nombre_file;
        create_get_file.long_nombre_file = strlen(create_get_file.nombre_file);
        create_tripulante_bitacora(create_get_file);
    }

    t_file file_to_update = get_bitacora_tripulante(file_input);
    
    char* contenido = string_new();
    string_append_with_format(&contenido, "%s", file_to_update.contenido);
    string_append_with_format(&contenido, "%s", file_input.contenido);
    file_to_update.contenido = malloc(strlen(contenido));
    strcpy(file_to_update.contenido, contenido);

    printf("A actualizar\n");
    mostrar_file(file_to_update);
    save_bitacora(file_to_update);
}

void agregar_recurso(t_operation_file_recurso file_input){
    if(!existe_nombre_file_recurso(file_input.nombre_file)){
        t_create_file create_get_file;
        create_get_file.caracter = file_input.caracter;
        create_get_file.nombre_file = file_input.nombre_file;
        create_get_file.long_nombre_file = strlen(create_get_file.nombre_file);
        create_recurso(create_get_file);
    }

    t_file file_to_update = get_recurso(file_input.nombre_file);
    
    char* contenido = string_new();
    string_append_with_format(&contenido, "%s", file_to_update.contenido);
    string_append_with_format(&contenido, "%s", string_repeat(file_input.caracter, file_input.cantidad));
    file_to_update.contenido = malloc(strlen(contenido));
    strcpy(file_to_update.contenido, contenido);

    save_recurso(file_to_update);
}

void retirar_recurso(t_operation_file_recurso file_input){
    if(!existe_nombre_file_recurso(file_input.nombre_file)){
        t_create_file create_get_file;
        create_get_file.caracter = file_input.caracter;
        create_get_file.nombre_file = file_input.nombre_file;
        create_get_file.long_nombre_file = strlen(create_get_file.nombre_file);
        create_recurso(create_get_file);
    }
    printf("Retirar recurso\n");
    print_bit_map(get_bitmap());
    printf("\n");
    t_file file_to_update = get_recurso(file_input.nombre_file);
    int cantidad_que_tiene = strlen(file_to_update.contenido);
    int cantidad_a_restar = file_input.cantidad;
    int cantidad_actual = cantidad_que_tiene - cantidad_a_restar;
    if(cantidad_actual<0){
        cantidad_actual = 0;
        log_info(logger, "Se intenta eliminar más mensajes de lo que tiene");
    }
    file_to_update.contenido = string_repeat(file_input.caracter, cantidad_actual);

    save_recurso(file_to_update);
}

void eliminar_recurso(t_operation_file_recurso file_input){
    /* Implica indicar los bloques como disponibles */
    if(!existe_nombre_file_recurso(file_input.nombre_file)){
        log_info(logger, "El recurso no existe");
        return;
    }
    printf("Archivo: %s\n", file_input.nombre_file);
    
    t_file file_to_update = get_recurso(file_input.nombre_file);
    file_to_update.contenido = "";
    save_recurso(file_to_update);
    eliminar_archivos_filesystem(file_input.nombre_file);
}

void init_protocolo_fsck(){
    //Avisar a discordiador la finalización del fsck
    resolver_sabotaje_super_bloque();
    resolver_sabotaje_files();
}