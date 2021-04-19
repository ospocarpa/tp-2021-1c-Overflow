#ifndef CONSOLA_CLIENTE_H
#define CONSOLA_CLIENTE_H

#include "Cliente_Restaurante.h"
#include "Cliente_Sindicato.h"
#include "Cliente_MultiModulo.h"



// ----------------------------------- INICIO DE DECLARACIONES --------------------------------------


/* -----------------------------
   Para archivo de configuracion
   ----------------------------- */
struct datosConf {
	int valor1;
	char valor2;
};

/* --------------------------------
   Nomina de operaciones de consola
   -------------------------------- */
typedef enum
{
        CLIENTE = 0,
        TEST,
        CLEAR,
        HELP,
        SALIR,
        INVALIDO
} comandos;


/* -----------------------------------
   Estructura para mapear los comandos
   ----------------------------------- */


/* ----------------------------------------------
   Obtencion de valor de entradas automaticamente
   ---------------------------------------------- */
int parse_cfg_key(const char *str);

void clearScreen();
void salirModulo();
int leerCadena(char *cad, int n);
int fClienteMensajes();
void fTesting();
int mensajeHelp();
void* ejecutarComando (char* cadena);
int commandPrompt();
void* iniciarConsola(void* args);


#endif