#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"

typedef enum
{
	INFORM=0,
    DEBUG=1,
    ERROR=2
}type_log;

void logger_create(char * path_log, char * name_log);
void logger_info(const char *format, ...);
void logger_error(const char *format, ...);
void logger_debug(const char *format, ...);
void logger_free();
t_log * get_logger();


#endif