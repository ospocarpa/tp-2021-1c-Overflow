#include "mongo_store.h"

int main(int argc, char **argv)
{   
    printf("MD5: %s\n", getMD5("Pepe"));
    return 1;
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
    int block_size = 0;
    int blocks = 0;
    int bitmap = 0;

    int fd = open("/home/utnso/polus/SuperBloque.ims", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    int file_size = sizeof(uint32_t) * 2 + 4;
    void* stream = mmap(NULL, file_size, PROT_WRITE | PROT_READ , MAP_SHARED, fd, 0);
    t_bitarray* bitarray = NULL;

    memcpy(&block_size, stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	memcpy(&blocks, stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
    memcpy(&bitmap, stream, 4);
	stream += 4;

    printf("%d %d\n", block_size, blocks, bitmap);
    print_bit_map(bitarray);
    return 1;
}