#include "RecepcionMensajes.h"

//COMENTARIO: POR AHORA TIENE DATOS DUMMY PARA TESTING, HAY QUE PONER
//            LO QUE HACE CADA MODULO PARA CARGAR LOS VALORES
void *recepcionMensaje(t_paquete *paquete, int cliente_fd, t_log *logger)
{
    log_info(logger, "recibo algo");

    t_paquete *new_paquete;
    switch (paquete->codigo_operacion)
    {
        case 0:
            exit;
        case I_OBTENER_RESTAURANTE:
            printf("Llegó el mensaje\n");
            break;
        break;
    }

    return NULL;
}