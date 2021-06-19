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


    bool existePath(char* path);
    char* get_path_punto_montaje();

#endif