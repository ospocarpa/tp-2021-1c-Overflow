#include "log_utils.h"

static t_log * logger = NULL;

void log_create(char * path_log, char * name_log){
    if(logger == NULL){
        logger = iniciar_logger(path_log, name_log);
    }
}

static void write_log_info(char * mensaje){
    log_info(logger,mensaje);
}

static void write_log_error(char* mensaje){
    log_error(logger,mensaje);
}

static void write_log_debug(char* mensaje){
    log_debug(logger, mensaje);
}

static void template_log(int type, const char * format, va_list arguments){
    //no se valida si el log es null

    va_list copy_arguments;
    va_copy(copy_arguments, arguments);
    size_t size_buffer = vsnprintf(NULL, 0, format, copy_arguments) + 1;
    va_end(copy_arguments);

    char * leyenda = malloc(size_buffer);
    vsnprintf(leyenda, size_buffer, format, arguments);

    switch (type)
    {
    case INFORM:
        write_log_info(leyenda);
        break;
    case DEBUG:
        write_log_debug(leyenda);
        break;
    case ERROR:
        write_log_error(leyenda);
        break;    
    default:
        break;
    }

    free(leyenda);
}

void log_info(const char *format, ...){
	va_list arguments;
	va_start(arguments, format);
	template_log(0, format, arguments);
	va_end(arguments);
}

void log_error(const char *format, ...){
	va_list arguments;
	va_start(arguments, format);
	template_log(ERROR, format, arguments);
	va_end(arguments);
}

void log_debug(const char *format, ...){
	va_list arguments;
	va_start(arguments, format);
	template_log(DEBUG, format, arguments);
	va_end(arguments);
}

void log_free(){
    log_destroy(logger);
}

t_log * get_log(){
    return logger;
}