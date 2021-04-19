#ifndef CLIENTE_STARTER_H
#define CLIENTE_STARTER_H

#include "shared_utils.h"
#include "server_utils.h"
#include "config_utils.h"
#include "handshake.h"

t_log* logger ;
t_config* g_config ;
t_config_cliente* config_cliente;
//config_cliente

int moduloActual;
int cCon;//cApp, cCom, cRes, cSin;
extern char* cIP ;
extern int PUERTO ;
extern int cliente_fd ;
extern t_handshake_output* handshake_regreso;
void enviarHandshake(t_config_cliente * config,char* IP, int Puerto, int conexion, t_log* logger);

#endif