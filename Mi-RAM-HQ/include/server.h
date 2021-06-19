#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <string.h>
#include "log_utils.h"
#include "server_utils.h"
#include <stdlib.h>
#include "sd_informar_tarea_tripulante.h"
#include "sd_expulsar_tripulante.h"
#include "sd_iniciar_patota.h"
#include "sd_listar_tripulantes.h"
#include "socket_client.h"

void server_mi_ram_iniciar(int puerto);

#endif