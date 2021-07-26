#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdbool.h>
#include <global.h>
#include <config_utils.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <commons/bitarray.h>
#include <commons/collections/list.h>
#include <commons/string.h>

    //Estructura
    typedef struct{
        void* stream;                       //Memoria virtual
        void* stream_copy;                  //Memoria en la que se va a trabajar

		uint32_t blocks_cant;
		uint32_t blocks_size;
		t_bitarray* bitmap;
        void* blocks;                       //Es el conjunto de bloques
	} t_filesystem;

    t_filesystem filesystem;

    // Creación
    void implementar_sincronizacion();
    char* get_path_file_recurso(char* file_name);
    char* get_path_file_bitacora(char* file_name);
    char* get_contenido_recurso(char* filename);
    char* get_contenido_bitacora(char* filename);
    char* getContenido(char* path_ims);
    t_list* get_bloques_from_metadata(t_config* metadata_ims);
    char* get_bloque(int bloque);
    void save_bitacora(t_file file_to_update);
    void save_recurso(t_file file_to_update);
    void guardar_contenido(t_config* info, t_file file);
    int get_redondear(int dividendo, int divisor);
    int get_primer_bloque_disponible();
    void liberar_bloque(int bloque);
    t_bitarray* get_bitmap();
    char* list_convert_to_string(t_list* lista);
    void guardar_partes_contenido(char* contenido, t_list* bloques);
    void llenar_bloque(char* informacion, int bloque);
    t_list* get_contenido_por_partes(char* contenido, int longitud);
    char* getMD5(char* text);

    extern t_config_mongo_store* config_global_mongo_store;

    void init_filesystem();
    bool existePath(char* path);
    char* get_path_punto_montaje();
    char* get_path_files();
    char* get_path_bitacoras();
    void print_bit_map(t_bitarray* bitarray);
    void clean_bit_map(t_bitarray* bitarray);
    int create_file(char* path);

#endif