#include "filesystem.h"

bool existePath(char* path){
    //printf("%s\n", path);
    FILE* file = fopen(path, "r");
	if(file==NULL)
		return false;
    return true;
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