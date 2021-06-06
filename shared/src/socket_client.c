#include "../include/socket_client.h"

int crear_conexion(char *ip, int puerto)
{
	struct addrinfo hints, *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	char *port = string_itoa(puerto);
	getaddrinfo(ip, port, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if (connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
	{
		return -1;
	}

	freeaddrinfo(server_info);
	free(port);
	return socket_cliente;
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

void sendMessage(t_paquete *paquete, int socket_cliente)
{
	int bytes = 0;
	void *a_enviar = malloc(sizeof(t_paquete));
	a_enviar = serializar_paquete(paquete, &bytes);
	send(socket_cliente, a_enviar, bytes, 0);
	free(a_enviar);
}

/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
*/
void *serializar_paquete(t_paquete *paquete, int *bytes)
{
	(*bytes) = paquete->buffer->size + sizeof(int) + sizeof(uint32_t) + sizeof(bool);
	void *a_enviar = malloc((*bytes));
	int desplazamiento = 0;

	memcpy(a_enviar + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento += sizeof(int);
	memcpy(a_enviar + desplazamiento, &(paquete->buffer->size), sizeof(uint32_t));
	desplazamiento += sizeof(uint32_t);
	memcpy(a_enviar + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento += paquete->buffer->size;

	return a_enviar;
}