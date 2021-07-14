#include "../include/sd_sabotaje.h"

t_package serializar_I_SABOTAJE(t_sabotaje* input){
	t_package paquete;
	int tam_buffer = input->mensaje_length + sizeof(uint32_t) * 3;
	paquete.tam_buffer = tam_buffer;
    paquete.buffer = malloc(tam_buffer);
    paquete.cod_operacion= SABOTAJE;
    int offset = 0;

	memcpy(paquete.buffer + offset, &input->mensaje_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(paquete.buffer + offset, input->mensaje, input->mensaje_length);
	offset += input->mensaje_length;

	memcpy(paquete.buffer + offset, &input->posicion->posx, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(paquete.buffer + offset, &input->posicion->posy, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	return paquete;
}

t_sabotaje* deserializar_I_SABOTAJE(t_package paquete){
	//preguntar lo de Sarea 
	t_sabotaje* respuesta = malloc(sizeof(t_sabotaje));

	memcpy(&respuesta->mensaje_length, paquete.buffer, sizeof(uint32_t));
	paquete.buffer += sizeof(uint32_t);

	respuesta->mensaje = malloc(respuesta->mensaje_length);
	memcpy(respuesta->mensaje, paquete.buffer, respuesta->mensaje_length);
	respuesta->mensaje[respuesta->mensaje_length] = '\0';
	paquete.buffer += respuesta->mensaje_length;


	respuesta->posicion = malloc(sizeof(Posicion));
	memcpy(&respuesta->posicion->posx, paquete.buffer, sizeof(uint32_t));
	paquete.buffer += sizeof(uint32_t);
	memcpy(&respuesta->posicion->posy, paquete.buffer, sizeof(uint32_t));
	paquete.buffer += sizeof(uint32_t);

    return respuesta;
}

void mostrarSabotaje(t_sabotaje* sabotaje){
    printf("Description: %s\n", sabotaje->mensaje);
    printf("Description length: %d\n", sabotaje->mensaje_length);
    printf("Posicion x: %d\n", sabotaje->posicion->posx);
    printf("Posicion y: %d\n", sabotaje->posicion->posy);
}
