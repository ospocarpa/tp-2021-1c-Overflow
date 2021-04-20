#ifndef HANDSHAKE_H
#define HANDSHAKE_H
#include <stdlib.h>
#include <string.h>
#include "TAD.h"
#include "TADAnexo.h"

typedef struct {
    char* IP;
    uint32_t IP_length;
    uint32_t Puerto;
    char* Modulo;
    uint32_t Modulo_length;
    uint32_t POS_X;
    uint32_t POS_Y;
    char* Id_modulo;
    uint32_t Id_modulo_length;

} t_handshake_input;

typedef struct {
    char* Modulo;
    uint32_t Modulo_length;
    char* Id_modulo;
    uint32_t Id_modulo_length;

} t_handshake_output;

t_paquete* serializar_handshake_input(t_handshake_input* datos);
t_handshake_input* deserializar_handshake_input(t_paquete* paquete);
t_paquete* serializar_handshake_output(t_handshake_output* datos);
t_handshake_output* deserializar_handshake_output(t_paquete* paquete);

void devolverHandshake(char *modulo,int conexionCliente);
#endif