#include "RecepcionMensajes.h"

//COMENTARIO: POR AHORA TIENE DATOS DUMMY PARA TESTING, HAY QUE PONER
//            LO QUE HACE CADA MODULO PARA CARGAR LOS VALORES
void *recepcionMensaje(t_paquete *paquete, int cliente_fd, t_log *logger)
{
    log_info(logger, "recibo algo");
    //Deserializacion
    t_paquete *new_paquete;
    Tarea* tarea2;
    switch (paquete->codigo_operacion)
    {
        case 0:
            exit;
        break;
        case TAREA: 
            tarea2 = deserializar_I_TAREA(paquete);
            mostrarTarea(tarea2);
            break;
    }

    return NULL;
}