#include "RecepcionMensajes.h"

/* prototipo funciones privadas */
char * objeto_pedido(char * plato, int cant_plato_pedido, int cant_platos_listo);
char * res_format_obtener_pedido(t_pedido * respuesta_pedido);

/* --------------------------- */

int conexionCliente = -1;
bool tengoHandshake = false;

//COMENTARIO: POR AHORA TIENE DATOS DUMMY PARA TESTING, HAY QUE PONER
//            LO QUE HACE CADA MODULO PARA CARGAR LOS VALORES

void *recepcionMensaje(t_paquete *paquete, t_log *logger)
{
    t_plato* plato;
    t_pedido* pedido;
    t_platos *respuesta_platos;
    t_paquete *paquete_respuesta;
    t_nombreDeRes *nombreDeRes = malloc(sizeof(t_nombreDeRes));
    t_I_GUARDAR_PEDIDO *GPinput = malloc(sizeof(t_I_GUARDAR_PEDIDO));

    t_respuesta_bool *respuesta_bool = malloc(sizeof(t_respuesta_bool));
    t_restaurante *respuesta_restaurante = malloc(sizeof(t_restaurante));
    t_pedido *respuesta_pedido = malloc(sizeof(t_pedido));
    t_pedidoID *respuesta_pedidoID = malloc(sizeof(t_pedidoID));
    t_O_CONSULTAR_RESTAURANTE *respuesta_consultar_restaurante;
    t_receta* receta;
    switch (paquete->codigo_operacion)
    {
    case 0:
        exit;
    case RESPUESTA_BOOL: //Respuesta OK/Fail
        break;
    case I_CONSULTAR_RESTAURANTE:
        break;
    case O_CONSULTAR_RESTAURANTE:
        respuesta_consultar_restaurante = deserializar_O_CONSULTAR_RESTAURANTE(paquete);
        for (int c = 0; c < respuesta_consultar_restaurante->cantNombreDeRes; c++)
        {
            nombreDeRes = list_get(respuesta_consultar_restaurante->t_nombreDeRes, c);
            log_info(logger, "Nombre Restaurante: %s", nombreDeRes->nombreDeRes);
        }
        break;
    case I_SELECCIONAR_RESTAURANTE:
        break;
    case O_SELECCIONAR_RESTAURANTE:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Seleccionar Restaurante: %s", respuesta_bool->estado);
        break;
    case I_OBTENER_RESTAURANTE:
        break;
    case O_OBTENER_RESTAURANTE:
        respuesta_restaurante = deserializar_restaurante(paquete);
        mostrar_restaurante(respuesta_restaurante, logger);
        log_info(logger, "Respuesta Obtener Restaurante");
        break;
    case I_CONSULTAR_PLATOS:
        break;
    case O_CONSULTAR_PLATOS:
        respuesta_platos = deserializar_O_CONSULTAR_PLATOS(paquete);
        mostrar_platos(respuesta_platos->platos, respuesta_platos->cantPlatos, logger);
        log_info(logger, "Respuesta Consultar Platos");
        break;
    case I_CREAR_PEDIDO:
        break;
    case O_CREAR_PEDIDO:
        respuesta_pedidoID = deserializar_pedido_ID(paquete);
        log_info(logger, "Respuesta Crear Pedido: %d", respuesta_pedidoID->pedidoID);
        break;
    case I_GUARDAR_PEDIDO:
        break;
    case O_GUARDAR_PEDIDO:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Guardar Pedido: %s", respuesta_bool->estado);
        break;
    case I_ANADIR_PLATO:
        break;
    case O_ANADIR_PLATO:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Añadir plato: %s", respuesta_bool->estado);
        break;
    case I_GUARDAR_PLATO:
        break;
    case O_GUARDAR_PLATO:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Guardar Plato: %s", respuesta_bool->estado);
        break;
    case I_CONFIRMAR_PEDIDO:
        break;
    case O_CONFIRMAR_PEDIDO:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Confirmar Pedido: %s", respuesta_bool->estado);
        break;
    case I_PLATO_LISTO:
        break;
    case O_PLATO_LISTO:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Plato Listo: %s", respuesta_bool->estado);
        break;
    case I_CONSULTAR_PEDIDO:
        break;
    case O_CONSULTAR_PEDIDO:
        pedido = deserializar_output_Consultar_Pedido(paquete);
        mostrar_pedido(pedido, logger);
        log_info(logger, "Respuesta Consultar Pedido");
        break;
    case I_OBTENER_PEDIDO:
        break;
    case O_OBTENER_PEDIDO:
        respuesta_pedido = deserializar_output_pedido(paquete);
        char * res = res_format_obtener_pedido(respuesta_pedido);
        log_info(logger, "Respuesta Obtener Pedido");
        log_info(logger, "%s", res);
        break;
    case I_FINALIZAR_PEDIDO:
        break;
    case O_FINALIZAR_PEDIDO:
        respuesta_bool = deserializar_respuesta_bool(paquete);
        log_info(logger, "Respuesta Finalizar Pedido: %s", respuesta_bool->estado);
        break;
    case I_TERMINAR_PEDIDO:
        break;
    case O_TERMINAR_PEDIDO:
        log_info(logger, "Respuesta Terminar Pedido");
        break;
    case I_OBTENER_RECETA:
        break;
    case O_OBTENER_RECETA:
        receta = deserializar_receta(paquete);
        mostrar_receta(receta, logger);
        log_info(logger, "Respuesta Obtener Receta");
        break;
    case INPUT_HANDSHAKE:; //Input HandShake
        log_info(logger, "CodigoH %d", paquete->codigo_operacion);
        t_handshake_input *handshake = malloc(sizeof(t_handshake_input));
        handshake = deserializar_handshake_input(paquete);
        tengoHandshake = true;
        conexionCliente = crear_conexion(handshake->IP, handshake->Puerto, logger);
        //devolverHandshake("Restaurante",conexionCliente);
        devolverHandshake("Restaurante", conexionCliente);
        break;
    case OUTPUT_HANDSHAKE: //Output HandShake
        break;
    default:
        printf("Recepcion %d\n", paquete->codigo_operacion);
        break;
    }

    return NULL;
}

char * objeto_pedido(char * plato, int cant_plato_pedido, int cant_platos_listo){
    char * objeto = string_new();
    char * cant_pedido = string_itoa( cant_plato_pedido);
    char * cant_listo = string_itoa((cant_platos_listo));

    string_append_with_format(&objeto, "{%s, %s, %s}", plato, cant_pedido, cant_listo);

    return objeto;
}

char * res_format_obtener_pedido(t_pedido * respuesta_pedido){
    char * respuesta = string_new();

        switch (respuesta_pedido->estado_Actual)
        {
        case PENDIENTE:
            string_append(&respuesta,"{Pendiente, [");
            break;
        case CONFIRMADO:
            string_append(&respuesta,"{Confirmado, [");
            break;
        case TERMINADO:
            string_append(&respuesta,"{Terminado,[");
            break;
        }
        
        
         
        for (uint32_t i = 0; i < respuesta_pedido->cantPlatos; i++)
        {
            t_plato * plato = list_get(respuesta_pedido->platos, i);
            int cant_plato = (int) list_get(respuesta_pedido->cantidad_Platos, i);
            int cant_listos =  (int) list_get(respuesta_pedido->cantidad_Lista, i);

            char* nombre = plato->nombre;

            char * obj_pedido = objeto_pedido(nombre, cant_plato, cant_listos); 

            string_append(&respuesta,obj_pedido);

            uint32_t va_coma = i+1;

            if(va_coma < respuesta_pedido->cantPlatos){
                string_append(&respuesta,", ");
            }

            free(nombre);
        }

        string_append(&respuesta," ] }");

        return respuesta;
}