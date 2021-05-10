#ifndef DISCORDIADOR_H
#define DISCORDIADOE_H

#include <stdio.h>
#include <stdbool.h>
#include "log_utils.h"
#include "config_utils.h"
#include <commons/config.h>
#include "socket_client.h"
#include <sys/socket.h>
#include <TAD.h>
#include "config_utils.h"
#include "shared_utils.h"
#include "RecepcionMensajes.h"
#include <consola.h>

    t_log* logger;
    void iniciar_servidor_main();
    void ejecutar_operacion(int cliente_fd);

#endif