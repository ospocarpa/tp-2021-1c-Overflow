#include "sd_iniciar_patota.h"

t_paquete * serializar_iniciar_patota(t_iniciar_patota data)
{
    t_paquete * paquete = malloc(sizeof(t_paquete));
    int tam_buffer = sizeof(int) * 3 + data.long_path_tareas + data.long_posicion;
    t_buffer * new_buffer = malloc(sizeof(t_buffer));
    void * stream = malloc(tam_buffer);
    int offset = 0;
    new_buffer->size = tam_buffer;

    memcpy(stream, &data.cant_tripulantes, sizeof(int));
    offset+=sizeof(int);

    memcpy(stream+offset, &data.long_path_tareas, sizeof(int));
    offset+=sizeof(int);

    memcpy(stream+offset, data.path_tareas, data.long_path_tareas);
    offset+=data.long_path_tareas;

    memcpy(stream+offset, &data.long_posicion, sizeof(int));
    offset+=sizeof(int);

    memcpy(stream+offset, data.posiciones, data.long_posicion);
    
    new_buffer->stream = stream;
    paquete->codigo_operacion = INICIAR_PATOTA;
    paquete->buffer = new_buffer;
    
    return paquete;
}

t_iniciar_patota deserializar_iniciar_patota(t_paquete * paquete)
{
    t_iniciar_patota data;

    memcpy(&data.cant_tripulantes, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    memcpy(&data.long_path_tareas, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    int size_path= data.long_path_tareas;
    data.path_tareas = malloc(size_path);
    memcpy(data.path_tareas, paquete->buffer->stream, size_path);
    paquete->buffer->stream += size_path;
    data.path_tareas[size_path] = '\0';

    memcpy(&data.long_posicion, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    int size_posiciones = data.long_posicion;
    data.posiciones = malloc(size_posiciones);
    memcpy(data.posiciones, paquete->buffer->stream, size_posiciones);
    paquete->buffer->stream += size_posiciones;
     data.posiciones[size_posiciones] = '\0';

    return data;
}

t_list * convertir_a_list_psiciones(char * posiciones_string){
    t_list * posiciones = list_create();

    return posiciones;
}