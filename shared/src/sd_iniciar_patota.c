#include "sd_iniciar_patota.h"

t_paquete *serializar_iniciar_patota(t_iniciar_patota data)
{
    int tam_buffer = sizeof(int) * 3 + data.long_path_tareas + data.long_posicion;
    t_paquete *paquete = malloc(sizeof(t_paquete));
    paquete->buffer = malloc(sizeof(t_buffer));
    paquete->buffer->stream = malloc(tam_buffer);
    paquete->codigo_operacion = INICIAR_PATOTA;
    int offset = 0;

    memcpy(paquete->buffer->stream, &data.cant_tripulantes, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete->buffer->stream + offset, &data.long_path_tareas, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete->buffer->stream + offset, data.path_tareas, data.long_path_tareas);
    offset += data.long_path_tareas;

    memcpy(paquete->buffer->stream + offset, &data.long_posicion, sizeof(int));
    offset += sizeof(int);

    memcpy(paquete->buffer->stream + offset, data.posiciones, data.long_posicion);

    return paquete;
}

t_iniciar_patota deserializar_iniciar_patota(t_paquete *paquete)
{
    t_iniciar_patota data;

    memcpy(&data.cant_tripulantes, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    memcpy(&data.long_path_tareas, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    int size_path = data.long_path_tareas;
    data.path_tareas = malloc(size_path + 1);
    memcpy(data.path_tareas, paquete->buffer->stream, size_path);
    paquete->buffer->stream += size_path;
    data.path_tareas[size_path] = '\0';

    memcpy(&data.long_posicion, paquete->buffer->stream, sizeof(int));
    paquete->buffer->stream += sizeof(int);

    int size_posiciones = data.long_posicion;
    data.posiciones = malloc(size_posiciones + 1);
    memcpy(data.posiciones, paquete->buffer->stream, size_posiciones);
    paquete->buffer->stream += size_posiciones;
    data.posiciones[size_posiciones] = '\0';

    return data;
}

t_list *convertir_a_list_posiciones(char *posiciones_string)
{
    t_list *posiciones = list_create();

    return posiciones;
}