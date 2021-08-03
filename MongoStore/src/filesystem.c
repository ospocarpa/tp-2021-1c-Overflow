#include "filesystem.h"

void implementar_sincronizacion(){
    int file_size = sizeof(uint32_t) * 2 + filesystem.blocks_cant/8;  
    do{
        sleep(config_global_mongo_store->TIEMPO_SINCRONIZACION);
        memcpy(filesystem.stream_copy, filesystem.stream, file_size);      //Lo paso a la copia que se usará
        msync(filesystem.stream_copy, file_size, MS_SYNC);
        printf("Sincronizacion: %d\n", config_global_mongo_store->TIEMPO_SINCRONIZACION);
    }while(1);
}

void init_filesystem(){
    filesystem.blocks_cant = config_global_mongo_store->BLOCKS;
    filesystem.blocks_size = config_global_mongo_store->BLOCK_SIZE;
    filesystem.super_bloque_tam = filesystem.blocks_cant * filesystem.blocks_size;
    filesystem.bitmap = NULL;//?
    filesystem.blocks = malloc(filesystem.blocks_cant * filesystem.blocks_size);
    
    int file_size = sizeof(uint32_t) * 2 + filesystem.blocks_cant/8;
    filesystem.stream = malloc(file_size);
    filesystem.stream_copy = malloc(file_size);

    //printf("Cantidad: %d\n", filesystem.blocks_cant);
    //printf("Size: %d\n", filesystem.blocks_size);
}

bool existe_nombre_file_bitacora(char* filename){
    char* path_ims = get_path_file_bitacora(filename);
    return existePath(path_ims);
}

bool existe_nombre_file_recurso(char* filename){
    char* path_ims = get_path_file_recurso(filename);
    return existePath(path_ims);
}

bool existePath(char* path){
    //printf("%s\n", path);
    FILE* file = fopen(path, "r");
	if(file==NULL)
		return false;
    return true;
}

void eliminar_archivos_filesystem(char* filename){
    char* path_ims = get_path_file_recurso(filename);
    printf("Archivo: %s\n", path_ims);
    remove(path_ims);
}

char* get_contenido_recurso(char* filename){
    char* path_ims = get_path_file_recurso(filename);
    return getContenido(path_ims);
}

char* get_contenido_bitacora(char* filename){
    char* path_ims = get_path_file_bitacora(filename);
    return getContenido(path_ims);
}

char* getContenido(char* path_ims){
    printf("Path ims: %s\n", path_ims);
    t_config* info = config_create(path_ims);    
    
    t_list* bloques = get_bloques_from_metadata(info);
	int cant_bloques = list_size(bloques);
    int current_block;
    char* contenido = string_new();

    for(int c=0; c<cant_bloques; c++){
        current_block = list_get(bloques, c);
        char* contenido_bloque = get_bloque(current_block);
        printf("Contenido bloque: %s\n", contenido_bloque);
        string_append_with_format(&contenido, "%s", contenido_bloque);
    }
    printf("Contenido: %s\n", contenido);
    return contenido;
}

t_list* get_bloques_from_metadata(t_config* metadata_ims){
    int size_contenido = config_get_int_value(metadata_ims, "SIZE");
    
    char* bloques_string = config_get_string_value(metadata_ims,"BLOCKS");
    //printf("Bloques string: %s\n", bloques_string);
	bloques_string = string_substring(bloques_string, 1, string_length(bloques_string)-2); 
	//printf("Bloques string: %s\n", bloques_string);

	t_list* bloques = list_create();
	char** partes_bloques = string_split(bloques_string, ",");
    void a_la_lista_bloques(char *item){
		//item = "1"
		list_add(bloques, atoi(item));
    };
    string_iterate_lines(partes_bloques, a_la_lista_bloques);
    //printf("Finish\n");
    return bloques;
}

char* get_bloque(int bloque){
    //printf("Arranque get_bloque: %d\n", filesystem.blocks_size);
    char* contenido = malloc(filesystem.blocks_size);
    memcpy(contenido, filesystem.blocks + ((bloque) * filesystem.blocks_size), filesystem.blocks_size);

    //printf("Contenido: %s\n", contenido);
    return contenido;
}

void save_bitacora(t_file file_to_update){
    //printf("Save bicatora: %s\n", file_to_update.nombre_file);
    char* path_ims = get_path_file_bitacora(file_to_update.nombre_file);
    //printf("Path: %s\n", path_ims);
    t_config* info = config_create(path_ims);

    guardar_contenido(info, file_to_update);
    config_save_in_file(info, path_ims);
}

void save_recurso(t_file file_to_update){
    char* path_ims = get_path_file_recurso(file_to_update.nombre_file);
    t_config* info = config_create(path_ims);

    guardar_contenido(info, file_to_update);

    int block_count = list_size(get_bloques_from_metadata(info));
    config_set_value(info, "BLOCK_COUNT", string_itoa(block_count));
    config_set_value(info, "MD5_ARCHIVO", getMD5(file_to_update.contenido));

    config_save_in_file(info, path_ims);
}

void guardar_contenido(t_config* info, t_file file){
    printf("Guardar contenido: %s\n", file.contenido);
    int size = strlen(file.contenido);

    // 1. Obtener los bloqueos usados.
    t_list* bloques_usados = get_bloques_from_metadata(info);                          // t_list [int]
    // 2. Ver los bloques que necesita
    int cant_bloques_actuales = get_redondear(size, filesystem.blocks_size);
    printf("Bloques actuales: %d\n", cant_bloques_actuales);
    printf("Bloques usados: %d\n", list_size(bloques_usados));
    
    //3. Si son menos eliminar 1, si son más pedir 1
    t_list* bloques_que_necesita = list_create();  // t_list [int]
    if(cant_bloques_actuales == list_size(bloques_usados)){
        printf("Bloques iguales\n");
        bloques_que_necesita = bloques_usados;
    }
    if(cant_bloques_actuales > list_size(bloques_usados)){
        printf("Bloques a agregar\n");
        bloques_que_necesita = bloques_usados;
        int bloques_a_agregar = cant_bloques_actuales - list_size(bloques_usados);
        for(int c=0; c<bloques_a_agregar; c++){
            list_add(bloques_que_necesita, get_primer_bloque_disponible());
        }	
    }
    if(cant_bloques_actuales < list_size(bloques_usados)){
        printf("Bloques a eliminar\n");
        bloques_que_necesita = bloques_usados;
        int bloques_que_necesita_size = list_size(bloques_que_necesita);
        int bloques_a_restar = list_size(bloques_usados) - cant_bloques_actuales;
        int bloque_a_liberar;
        for(int c=0; c<bloques_a_restar; c++){
            bloque_a_liberar = list_get(bloques_que_necesita, bloques_que_necesita_size-c-1);
            liberar_bloque(bloque_a_liberar);
            bloques_que_necesita = list_take_and_remove(bloques_que_necesita, bloques_que_necesita_size-c-1);
        }
    }
    
    // 4. Actualizar la información con bloques definidos
    guardar_partes_contenido(file.contenido, bloques_que_necesita);

    printf("Size: %d\n", size);
    printf("Blocks: %s\n", list_convert_to_string(bloques_que_necesita));
    config_set_value(info, "SIZE", string_itoa(size));
    config_set_value(info, "BLOCKS", list_convert_to_string(bloques_que_necesita));
}

char* list_convert_to_string(t_list* lista){
    char* lista_string = string_new();
    
    if(list_size(lista) > 0){
        int number = 0;

        char* numbers_string = string_new();
        for(int c=0; c<list_size(lista)-1; c++){
            printf("%d\n", list_get(lista, c));
            number = list_get(lista, c);
            string_append_with_format(&numbers_string, "%s,", string_itoa(number));    
        }
        //printf("%d\n", list_get(lista, list_size(lista)-1));
        
        number = list_get(lista, list_size(lista)-1);
        string_append_with_format(&numbers_string, "%s", string_itoa(number));    
        string_append_with_format(&lista_string, "[%s]", numbers_string);
    }else{
        string_append_with_format(&lista_string, "[%s]", "");
    }
    return lista_string;
}

void guardar_partes_contenido(char* contenido, t_list* bloques){
    int size_bloque = filesystem.blocks_size;

    t_list* partes_del_contenido = get_contenido_por_partes(contenido, size_bloque);
    int next_bloque = 0, bloque = 0;
    for(int c=0; c<list_size(partes_del_contenido); c++){
        //printf("%s\n\n", list_get(partes_del_contenido, c));
        bloque = list_get(bloques, c);
        llenar_bloque(list_get(partes_del_contenido, c), bloque);
    }
}

void llenar_bloque(char* informacion, int bloque){
    memcpy(filesystem.blocks + bloque * filesystem.blocks_size, informacion, filesystem.blocks_size);

    printf("Información: %s\n", informacion);
}

t_list* get_contenido_por_partes(char* contenido, int longitud){    //t_list [string]
    t_list* partes = list_create();
    
    int inicio = 0; bool detener = false;
    do{
        if(inicio+longitud>strlen(contenido)){
            longitud = strlen(contenido)-inicio;
            detener = true;
        }
        char* parte = string_substring(contenido, inicio, longitud);
        list_add(partes, parte);
        inicio += longitud;
    }while(!detener);
    return partes;
}

int get_redondear(int dividendo, int divisor){
    int cantidad = dividendo/divisor;
    if(dividendo%divisor>0) cantidad++;
    return cantidad;
}

int get_primer_bloque_disponible(){
    int indice = 0;

    t_bitarray* bitmap = get_bitmap();
    int bits = bitarray_get_max_bit(bitmap);
	bool auxiliar;
	for(int c=0; c<bits; c++){
		auxiliar = bitarray_test_bit(bitmap, c);
		if(!auxiliar){
			indice = c;
			break;
		}
	}
    asignar_bloque(indice);
    
    print_bit_map(bitmap);
    return indice;
}

void asignar_bloque(int bloque){
    t_bitarray* bitmap = get_bitmap();
    bitarray_set_bit(bitmap, bloque);

    int offset = 2 * sizeof(uint32_t);
    memcpy(filesystem.stream + offset, bitmap->bitarray, filesystem.blocks_cant/8);
    log_info(logger, "Asignación de un nuevo bloque %d", bloque);
}

void liberar_bloque(int bloque){
    t_bitarray* bitmap = get_bitmap();
    log_info(logger, "Desasignación del bloque %d", bloque);
    bitarray_clean_bit(bitmap, bloque);

    int offset = 2 * sizeof(uint32_t);
    memcpy(filesystem.stream + offset, bitmap->bitarray, filesystem.blocks_cant/8);
}

t_bitarray* get_bitmap(){
    int size = filesystem.blocks_cant/8;
    void* puntero_bitmap = malloc(size);
        
    memcpy(puntero_bitmap, filesystem.stream + (sizeof(uint32_t) * 2), size);      //reemplazar a filesystem.stream_copy
    t_bitarray* bitmap = bitarray_create_with_mode(puntero_bitmap, size, LSB_FIRST);
    return bitmap;
}

char* get_path_file_recurso(char* file_name){
    char* path_file = get_path_files();
    char* path_file_recurso = string_new();
    
    string_append_with_format(&path_file_recurso, "%s", path_file);
    string_append_with_format(&path_file_recurso, "/%s", file_name);
    return path_file_recurso;
}

char* get_path_file_bitacora(char* file_name){
    char* path_file = get_path_bitacoras();
    char* path_file_bitacora = string_new();
    
    string_append_with_format(&path_file_bitacora, "%s", path_file);
    string_append_with_format(&path_file_bitacora, "/%s", file_name);
    return path_file_bitacora;
}

char* get_path_punto_montaje(){
    char* path_punto_montaje = string_new();
    string_append_with_format(&path_punto_montaje, "%s", config_global_mongo_store->PUNTO_MONTAJE);
    return path_punto_montaje;
}

char* get_path_files(){
    char* path_files = string_new();
    string_append_with_format(&path_files, "%s", config_global_mongo_store->PUNTO_MONTAJE);
    string_append_with_format(&path_files, "%s", "/Files");
    return path_files;
}

char* get_path_bitacoras(){
    char* path_bitacoras = string_new();
    string_append_with_format(&path_bitacoras, "%s", config_global_mongo_store->PUNTO_MONTAJE);
    string_append_with_format(&path_bitacoras, "%s", "/Files");
    string_append_with_format(&path_bitacoras, "%s", "/Bitacoras");
    return path_bitacoras;
}

char* get_path_super_bloque(){
    char* path_super_bloque = string_new();
    char* punto_montaje = get_path_punto_montaje();
    string_append_with_format(&path_super_bloque, "%s", punto_montaje);
    string_append_with_format(&path_super_bloque, "%s", "/SuperBloque.ims");
    return path_super_bloque;
}

void print_bit_map(t_bitarray* bitarray){
    //bitarray_set_bit(bitarray, 3);
    //bitarray_set_bit(bitarray, 10);

    uint32_t bits = bitarray_get_max_bit(bitarray);
    printf("Bits: %d\n", bits);
    /*for(int c=0; c<bits; c++){
		bitarray_clean_bit(bitarray, c);
	}*/

    for(int c=0; c<bits; c++){
        bool bit = bitarray_test_bit(bitarray, c);
        printf("%d ", bit);
    }
    printf("\n");
}

void clean_bit_map(t_bitarray* bitarray){
    uint32_t bits = bitarray_get_max_bit(bitarray);
    for(int c=0; c<bits; c++){
		liberar_bloque(c);
	}
}

int create_file(char* path){
    /*
        1: fue creado con éxito
        0: no fue creado porque existe
    */
    int status = 0;
    FILE* file = fopen(path, "r");
	if(file==NULL){
		//No existe
		file = fopen(path, "w+");
        status = 1;
	}
    return status;
}

void resolver_sabotaje_super_bloque(){
    int tamanio_bloque = filesystem.super_bloque_tam;
    
    //Cantidad de bloques
    int cant_bloques = tamanio_bloque/filesystem.blocks_size;
    filesystem.blocks_cant = cant_bloques; 
    
    //Analizar bitmap
    t_bitarray* bitmap = get_bitmap();
    clean_bit_map(bitmap);

    /* Obtener los nombres en una lista: recursos y bitacoras */
    t_list* name_bitacoras = get_archivos_de_directorio(get_path_bitacoras());
    t_list* name_recursos = get_archivos_de_directorio(get_path_files());
    t_list* path_files_ims = list_create();
    
    for(int c=0; c<list_size(name_bitacoras); c++)
        list_add(path_files_ims, get_path_file_bitacora(list_get(name_bitacoras, c)));
    for(int c=0; c<list_size(name_recursos); c++)
        list_add(path_files_ims, get_path_file_recurso(list_get(name_recursos, c)));

    t_config* info;
    t_list* bloques;
    for(int c=0; c<list_size(path_files_ims); c++){
        char* path_file_ims = list_get(path_files_ims, c);
        printf("FIle: %s\n", path_file_ims);
        info = config_create(path_file_ims);    
        bloques = get_bloques_from_metadata(info);
        int cant_bloques = list_size(bloques);
        int current_block;
        printf("Bloques de %s: ", path_file_ims);
        for(int d=0; d<cant_bloques; d++){
            current_block = list_get(bloques, d);
            printf("%d ", current_block);
            asignar_bloque(current_block);
        }
        printf("\n");
    }
}

void resolver_sabotaje_files(){
    /* Obtener los nombres en una lista: recursos y bitacoras */
    t_list* name_recursos = get_archivos_de_directorio(get_path_files());
    t_list* path_files_ims = list_create();
    for(int c=0; c<list_size(name_recursos); c++)
        list_add(path_files_ims, get_path_file_recurso(list_get(name_recursos, c)));

    t_config* info;
    t_list* bloques;

    int size = 0, block_count;
    char* contenido;
    char* contenido_md5;
    char* file_md5;
    char* caracter;
    char caracter_simple;
    for(int c=0; c<list_size(path_files_ims); c++){
        char* path_file_ims = list_get(path_files_ims, c);
        info = config_create(path_file_ims);    
        bloques = get_bloques_from_metadata(info);

        // Revisar el size de los archivos del recurso 
        contenido = getContenido(path_file_ims);
        size = strlen(contenido);
        config_set_value(info, "SIZE", string_itoa(size));

        // Revisar consistencia entre block_count y blocks
        block_count = list_size(bloques);
        config_set_value(info, "BLOCK_COUNT", string_itoa(block_count));

        // Reparar archivos por MD5 
        contenido_md5 = getMD5(contenido);
        file_md5 = config_get_string_value(info, "MD5_ARCHIVO");
        caracter = config_get_string_value(info, "CARACTER_LLENADO");

        if(!string_equals_ignore_case(contenido_md5, file_md5)){
            t_file file_to_update;
            
            printf("Test 2\n");
            caracter_simple = caracter[0];
            file_to_update.contenido = string_repeat(caracter_simple , size);
            file_to_update.long_contenido = strlen(file_to_update.contenido);
            file_to_update.nombre_file = list_get(name_recursos, c);
            file_to_update.long_nombre_file = strlen(file_to_update.nombre_file);
            
            printf("Test 3\n");
            save_recurso(file_to_update);
            printf("Test 4\n");
        }
    }
}

char* getMD5(char* text){
    FILE *fp;
    char path[1035];
    //char* final = []; 

    /* Open the command for reading. */
    char *terminal = string_new();
    string_append_with_format(&terminal, "echo -n \"%s\"| md5sum", text);

    fp = popen(terminal, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    char** parts; 
    while (fgets(path, sizeof(path), fp) != NULL) {
        parts = string_split(path, "  -");
        //printf("%s", path);
        //printf("%s\n", parts[0]);
    }

    /* close */
    pclose(fp);
    return parts[0];
}