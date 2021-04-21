/*#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "TAD.h"

#define SIZE_LOG 256

typedef enum
{
	INFORM=0,
    DEBUG=1,
    ERROR=2
}type_log;

void log_create(char * path_log, char * name_log);
void log_info(const char *format, ...);
void log_error(const char *format, ...);
void log_debug(const char *format, ...);
void log_free();
t_log * get_log();


#endif*/