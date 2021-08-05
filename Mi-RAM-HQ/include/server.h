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
#include "sd_informar_posicion_tripulante.h"
#include "sd_informar_estado.h"
#include "socket_client.h"
#include "tad_mi_ram_hq.h"
#include "memoria.h"
#include "TAD.h"
#include "util_mi_ram.h"
#include "expulsar_tripulante.h"
#include "render_mapa.h"

void server_mi_ram_iniciar(int puerto);

#endif