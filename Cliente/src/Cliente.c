#include "Cliente.h"

int main(int argc, char **argv)
{
    t_config *g_config = leer_config_file("./cfg/discordiador.config");
    t_config_discordiador *config = leerConfigDiscordiador(g_config);

    printf("%s\n", config->ARCHIVO_LOG);
    t_log *logger = iniciar_logger(config->ARCHIVO_LOG, "CLIENTE");
    printf("%s %d\n", config->IP_MODULO, config->PUERTO_MODULO);
    int conexion_servidor = crear_conexion("127.0.0.1", 5002);
    /*inicio_FSCK(conexion_servidor);
    return 1;*/
    crear_recurso(conexion_servidor, "oxigeno.ims");
    sleep(2);
    agregar_recurso(conexion_servidor, "oxigeno.ims");
    sleep(5);
    inicio_FSCK(conexion_servidor);
    sleep(20);
    retirar_recurso(conexion_servidor, "oxigeno.ims");
    sleep(5);
    inicio_FSCK(conexion_servidor);
    sleep(20);
    crear_recurso(conexion_servidor, "basura.ims");
    sleep(2);
    agregar_recurso(conexion_servidor, "basura.ims");
    sleep(2);
    crear_sabotaje(conexion_servidor, "tripulante1.ims"); //crear tripulanaate y su bitacora
    sleep(3);
    update_bitacora(conexion_servidor, "tripulante1.ims", "hola"); //contatena
    sleep(3);
    update_bitacora(conexion_servidor, "tripulante1.ims", " mundo");
    sleep(3);
    inicio_FSCK(conexion_servidor);
    sleep(3);
    //eliminar_recurso(conexion_servidor);
    //get_recurso(conexion_servidor);
    //get_bitacora(conexion_servidor);
    return 0;
}

void inicio_FSCK(int conexion_servidor)
{
    t_aviso_fsck fcsk;
    t_package paquete = ser_fcsk(fcsk);
    sendMessage(paquete, conexion_servidor);
}

//cantidad(de caracteres de llenado) :sea un parametro
//caracter y el char* del archivo
//cantidad de caracteres del archivo 8no es necesario
void agregar_recurso(int conexion_servidor, char *filename)
{
    t_operation_file_recurso file;
    file.cantidad = 10;
    file.caracter = 'o';
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_agregar_recurso(file);
    sendMessage(paquete, conexion_servidor);
}

void retirar_recurso(int conexion_servidor, char *filename)
{
    t_operation_file_recurso file;
    file.cantidad = 4;
    file.caracter = 'o';
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_retirar_recurso(file);
    sendMessage(paquete, conexion_servidor);
}

void eliminar_recurso(int conexion_servidor, char *filename)
{
    t_operation_file_recurso file;
    file.cantidad = 4;
    file.caracter = 'c';
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_eliminar_recurso(file);
    sendMessage(paquete, conexion_servidor);
}
//bitacora generica :
void update_bitacora(int conexion_servidor, char *filename, char *contenido)
{
    t_file file;
    file.contenido = contenido;
    file.long_contenido = strlen(file.contenido);
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_update_bitacora(file);
    sendMessage(paquete, conexion_servidor);
}

void get_recurso(int conexion_servidor, char *filename)
{
    t_file file;
    file.contenido = "";
    file.long_contenido = strlen(file.contenido);
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_get_file_recurso(file);
    sendMessage(paquete, conexion_servidor);
}

void get_bitacora(int conexion_servidor)
{
    t_file file;
    file.contenido = "Contenido de bitacora";
    file.long_contenido = strlen(file.contenido);
    file.nombre_file = "tripulante4.ims";
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_get_file_bitacora(file);
    sendMessage(paquete, conexion_servidor);
}
//3 bolleanos (uno para cada recurso) ,mutex para cada booleano
//booleano(false) -->se crea recurso antes . -->booleano = true
void crear_recurso(int conexion_servidor, char *filename)
{
    t_create_file file;
    file.caracter = 'o';
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_create_file_recurso(file);
    sendMessage(paquete, conexion_servidor);
}

void crear_sabotaje(int conexion_servidor, char *filename)
{ //es bitacora
    t_create_file file;
    file.caracter = ' ';
    file.nombre_file = filename;
    file.long_nombre_file = strlen(file.nombre_file);

    t_package paquete = ser_create_file_bitacora(file);
    sendMessage(paquete, conexion_servidor);
}

void enviar_tarea(int conexion_servidor)
{
    Tarea *tarea = malloc(sizeof(Tarea));
    tarea->patota_id = 1;
    tarea->description = "test";
    tarea->description_length = strlen(tarea->description);
    tarea->parametros = "test 2";
    tarea->parametros_length = strlen(tarea->parametros);
    tarea->tiempo = 3;
    tarea->posicion = malloc(sizeof(Posicion));
    tarea->posicion->posx = 1;
    tarea->posicion->posy = 2;

    t_paquete *paquete = serializar_I_TAREA(tarea);
    sendMessage(paquete, conexion_servidor);
}