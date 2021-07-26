#include "RecepcionMensajes.h"

//COMENTARIO: POR AHORA TIENE DATOS DUMMY PARA TESTING, HAY QUE PONER
//            LO QUE HACE CADA MODULO PARA CARGAR LOS VALORES
void *recepcionMensaje(t_package paquete, int cliente_fd, t_log *logger)
{
    log_info(logger, "recibo algo");
    t_package paquete_a_enviar;
    t_sabotaje* input;

    switch (paquete.cod_operacion)
    {
        case 0:
            exit;
            break;
        case SABOTAJE:
            printf("Llegó sabotaje\n");
            input = deserializar_I_SABOTAJE(paquete);
            mostrarSabotaje(input);
            //void inicio_sabotaje()

            t_aviso_fsck data_buffer;
            paquete_a_enviar = ser_fcsk(data_buffer);
            sendMessage(paquete_a_enviar, cliente_fd);
            break;
    }

    return NULL;
}