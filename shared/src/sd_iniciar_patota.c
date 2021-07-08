#include "sd_iniciar_patota.h"


/* ******* DISCORDIADOR ******* */
t_package ser_cod_iniciar_patota(t_iniciar_patota data)
{
    int tam_buffer = sizeof(int) * 3 + data.long_tareas + data.long_posicion + sizeof(uint32_t)*2 ;
    t_package paquete;
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion = INICIAR_PATOTA;
    paquete.tam_buffer = tam_buffer;
    int offset = 0;

    memcpy(paquete.buffer, &data.cant_tripulantes, sizeof(int));
    offset+=sizeof(int);

    memcpy(paquete.buffer+offset, &data.long_tareas, sizeof(int));
    offset+=sizeof(int);

    memcpy(paquete.buffer+offset, data.tareas, data.long_tareas);
    offset+=data.long_tareas;

    memcpy(paquete.buffer+offset, &data.long_posicion, sizeof(int));
    offset+=sizeof(int);

    memcpy(paquete.buffer+offset, data.posiciones, data.long_posicion);
    offset+= data.long_posicion;

    memcpy(paquete.buffer+offset, &data.patota_id, sizeof(uint32_t));
    offset+=sizeof(uint32_t);

    memcpy(paquete.buffer+offset, &data.id_primer_tripulante, sizeof(uint32_t));
    offset+=sizeof(uint32_t);
    
    return paquete;
}

bool des_res_iniciar_patota(t_package paquete)
{
    bool res;

    memcpy(&res, paquete.buffer, sizeof(bool));

    return res;
}

/* ******* MI RAM HQ ******* */
t_iniciar_patota des_cod_iniciar_patota(t_package paquete)
{
    t_iniciar_patota data;

    memcpy(&data.cant_tripulantes, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    memcpy(&data.long_tareas, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);


    int size_path= data.long_tareas;
    data.tareas = malloc(size_path+1);
    memcpy(data.tareas, paquete.buffer, size_path);
    paquete.buffer += size_path;
    data.tareas[size_path] = '\0';

    memcpy(&data.long_posicion, paquete.buffer, sizeof(int));
    paquete.buffer += sizeof(int);

    int size_posiciones = data.long_posicion;
    data.posiciones = malloc(size_posiciones+1);
    memcpy(data.posiciones, paquete.buffer, size_posiciones);
    paquete.buffer += size_posiciones;
    data.posiciones[size_posiciones] = '\0';

    memcpy(&data.patota_id, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    memcpy(&data.id_primer_tripulante, paquete.buffer, sizeof(uint32_t));
    paquete.buffer += sizeof(uint32_t);

    return data;
}

t_package ser_res_iniciar_patota(bool data)
{
    t_package paquete;
    int tam_buffer = sizeof(bool);
    paquete.buffer = malloc(tam_buffer);
    paquete.tam_buffer = tam_buffer;
    paquete.cod_operacion = INICIAR_PATOTA;

    memcpy(paquete.buffer, &data, sizeof(bool));

    return paquete;
}

t_list * convertir_a_list_posiciones(char * posiciones_string){
    t_list * posiciones = list_create();
    char ** list_posiciones = string_split( posiciones_string, " ");

    for (size_t i = 0; i < sizeof(list_posiciones); i++)
    {
        /* code */
    }
    
    return posiciones;
}