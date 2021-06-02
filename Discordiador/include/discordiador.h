#ifndef DISCORDIADOR_H
#define DISCORDIADOR_H

#include <stdio.h>
#include <stdbool.h>
#include "log_utils.h"
#include "config_utils.h"
#include <commons/config.h>
#include "socket_client.h"
#include <sys/socket.h>
#include <TAD.h>

#include "shared_utils.h"
#include "RecepcionMensajes.h"
#include <consola.h>
#include "tests.h"

t_log *logger;
int numeroTripulante = 0;
int numeroPatota = 0;
void iniciar_servidor_main();
void ejecutar_operacion(int cliente_fd);
#define PATH_CONFIG "cfg/discordiador.config"

#endif