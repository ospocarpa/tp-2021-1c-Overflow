#include "handshake.h"

t_paquete* serializar_handshake_input(t_handshake_input* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

/*
    printf("IP %s \n",datos->IP);
    printf("IP l %d \n",datos->IP_length);
    printf("Puerto %d \n",datos->Puerto);
    printf("PosX %d \n",datos->POS_X);
    printf("PosY %d \n",datos->POS_Y);
    printf("Mod %s \n",datos->Modulo);
    printf("Mod l %d \n",datos->Modulo_length);
    printf("Id %s \n",datos->Id_modulo);
    printf("Id l %d \n",datos->Id_modulo_length);
 */
    new_buffer->size = strlen(datos->Modulo) 
						+ strlen(datos->IP)
						+ strlen(datos->Id_modulo) 
						+ 3  
						+ (sizeof(uint32_t)*6);

    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento

    memcpy(stream + offset, &(datos->IP_length), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->IP, strlen(datos->IP)+1);
	offset += datos->IP_length + 1;

    memcpy(stream + offset, &(datos->Puerto), sizeof(uint32_t));
	offset += sizeof(uint32_t);
   
    memcpy(stream + offset, &(datos->Modulo_length), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->Modulo, strlen(datos->Modulo)+1);
	offset += datos->Modulo_length+1;

    memcpy(stream + offset, &(datos->Id_modulo_length), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->Id_modulo, strlen(datos->Id_modulo)+1);
	offset += datos->Id_modulo_length+1;
	
	memcpy(stream + offset, &(datos->POS_X), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &(datos->POS_Y), sizeof(uint32_t));
	offset += sizeof(uint32_t);

    new_buffer->stream = stream;
    paquete->codigo_operacion = INPUT_HANDSHAKE;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}

t_handshake_input* deserializar_handshake_input(t_paquete* paquete){
    t_handshake_input* respuesta = malloc(sizeof(t_handshake_input));
    t_buffer* buffer = paquete->buffer;


    memcpy(&(respuesta->IP_length), buffer->stream, sizeof(uint32_t));
    //printf("IP l %d \n",respuesta->IP_length);
	buffer->stream += sizeof(uint32_t);
	respuesta->IP = malloc(respuesta->IP_length+1);
	memcpy(respuesta->IP, buffer->stream, respuesta->IP_length+1);
	buffer->stream += respuesta->IP_length+1;
    //printf("IP %s \n",respuesta->IP);
    memcpy(&(respuesta->Puerto), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //printf("Puerto %d \n",respuesta->Puerto);
    memcpy(&(respuesta->Modulo_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //printf("Mod l %d \n",respuesta->Modulo_length);
	respuesta->Modulo = malloc(respuesta->Modulo_length+1);
	memcpy(respuesta->Modulo, buffer->stream, respuesta->Modulo_length+1);
	buffer->stream += respuesta->Modulo_length+1;
    //printf("Mod %s \n",respuesta->Modulo);
    memcpy(&(respuesta->Id_modulo_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //printf("Id l %d \n",respuesta->Id_modulo_length);
	respuesta->Id_modulo = malloc(respuesta->Id_modulo_length+1);
	memcpy(respuesta->Id_modulo, buffer->stream, respuesta->Id_modulo_length+1);
	buffer->stream += respuesta->Id_modulo_length+1;
    //printf("Id %s \n",respuesta->Id_modulo);
    memcpy(&(respuesta->POS_X), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //printf("PosX %d \n",respuesta->POS_X);
    memcpy(&(respuesta->POS_Y), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
    //printf("PosY %d \n",respuesta->POS_Y);




	return respuesta;
}






t_paquete* serializar_handshake_output(t_handshake_output* datos){
    t_paquete* paquete = malloc(sizeof(t_paquete));
    t_buffer* new_buffer = malloc(sizeof(t_buffer));

    new_buffer->size = datos->Modulo_length 
						+ datos->Id_modulo_length 
						+ 2 
						+ (sizeof(uint32_t)*2);
    void* stream = malloc(new_buffer->size);
    int offset = 0; // Desplazamiento
   
    memcpy(stream + offset, &(datos->Modulo_length), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->Modulo, datos->Modulo_length +1);
	offset += datos->Modulo_length;

    memcpy(stream + offset, &(datos->Id_modulo_length), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, datos->Id_modulo, datos->Id_modulo_length +1);
	offset += datos->Id_modulo_length;
	
    new_buffer->stream = stream;
    paquete->codigo_operacion = OUTPUT_HANDSHAKE;
	paquete->buffer = new_buffer;
	paquete->from_client = false;
	return paquete;
}

t_handshake_output* deserializar_handshake_output(t_paquete* paquete){
    t_handshake_output* respuesta = malloc(sizeof(t_handshake_output));
    t_buffer* buffer = paquete->buffer;

    memcpy(&(respuesta->Modulo_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);
	respuesta->Modulo = malloc(respuesta->Modulo_length +1);
	memcpy(respuesta->Modulo, buffer->stream, respuesta->Modulo_length +1);
	buffer->stream += respuesta->Modulo_length +1;

    memcpy(&(respuesta->Id_modulo_length), buffer->stream, sizeof(uint32_t));
	buffer->stream += sizeof(uint32_t);

	respuesta->Id_modulo = malloc(respuesta->Id_modulo_length +1);
	memcpy(respuesta->Id_modulo, buffer->stream, respuesta->Id_modulo_length +1);
	buffer->stream += respuesta->Id_modulo_length +1;

    return respuesta;
}


void devolverHandshake(char *modulo,int conexionCliente){
	t_handshake_output* datos =  malloc(sizeof(t_handshake_output));
	datos->Modulo = modulo;
	//printf("m %s\n",modulo);
	datos->Modulo_length = strlen(datos->Modulo);
	datos->Id_modulo = "";
	datos->Id_modulo_length = strlen(datos->Id_modulo);
	
	//log_info(logger, "enviando respuesta");
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete =  serializar_handshake_output(datos);
		//log_info(logger, "enviando HandShake2");
	sendMessage(paquete, conexionCliente); 
}