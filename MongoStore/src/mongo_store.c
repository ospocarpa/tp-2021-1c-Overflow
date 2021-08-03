#include "mongo_store.h"

int main(int argc, char **argv)
{   
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    {
        run_tests();
        return 1;
    }
    debug = true;

    signal(SIGUSR1, method_sigusr1);
    t_config *g_config = leer_config_file("./cfg/mongo_store.config");
    config_global_mongo_store = leer_config_mongo_store(g_config);

    //Iniciar Log
    logger = iniciar_logger(config_global_mongo_store->ARCHIVO_LOG, "SERVIDOR");
    log_info(logger, "Iniciando módulo i-Mongo-Store");
    
    pthread_t thread_sincronizacion;
    pthread_create(&thread_sincronizacion, NULL, (void *)init_mongo_store, NULL);
    pthread_detach(thread_sincronizacion);

    pthread_t thread_init_mongo_store;
    pthread_create(&thread_init_mongo_store, NULL, (void *)implementar_sincronizacion, NULL);
    pthread_detach(thread_init_mongo_store);

    int puerto = config_global_mongo_store->PUERTO;
    server_mongo_store_iniciar(puerto);

    return 1;
}

void sincronizacion(){
    int fd = open("/home/utnso/prueba.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    int file_size = 100;
    ftruncate(fd, file_size);
    printf("Fd: %d\n", fd);
    
    void* stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);//Memoria virtual
    
    void* stream_copy = malloc(file_size);
    char* test = malloc(10);
    strcpy(test, "Ari Latpat");
    printf("%s\n", test);
    int offset = 0;
    memcpy(stream_copy+offset, test, 10);

    memcpy(stream+offset, stream_copy, 10);
    //msync(stream_copy, file_size, MS_SYNC);
}

void lectura_file(){
    int tam_bit_map = 4;
    void* puntero_bitmap = malloc(tam_bit_map);
    
    int block_size = 0;
    int blocks = 0;

    int fd = open("/home/utnso/polus/SuperBloque.ims", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    printf("Fd: %d\n", fd);
    int file_size = sizeof(uint32_t) * 2 + tam_bit_map;
    ftruncate(fd, file_size);
    void* stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);

    int offset = 0;
    memcpy(&block_size, stream + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(&blocks, stream + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
    memcpy(puntero_bitmap, stream + offset, tam_bit_map);

    t_bitarray* bitarray = bitarray_create_with_mode(puntero_bitmap, tam_bit_map, LSB_FIRST);
    printf("%d %d\n", block_size, blocks);
    print_bit_map(bitarray);
    
    void* puntero_bitmap2 = malloc(tam_bit_map);
    memcpy(puntero_bitmap2, stream + 2*sizeof(uint32_t), tam_bit_map);
    t_bitarray* bitarray2 = bitarray_create_with_mode(puntero_bitmap2, tam_bit_map, LSB_FIRST);
    print_bit_map(bitarray2);
    return 1;
}