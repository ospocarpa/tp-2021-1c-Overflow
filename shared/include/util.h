#ifndef UTIL_H_
#define UTIL_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>
#include<stdbool.h>
#include<commons/log.h>
#include<commons/string.h>
#include "TAD.h"
#include "desearilizador.h"

	int crear_conexion(char *ip, int puerto, t_log* logger);
	void* serializar_paquete(t_paquete* paquete, int* bytes);
	void liberar_conexion(int socket_cliente);
	void sendMessage(t_paquete* paquete, int socket_cliente);

#endif /* UTIL_H_ */
