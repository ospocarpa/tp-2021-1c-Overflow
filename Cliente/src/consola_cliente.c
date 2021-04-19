/*
	Proceso multihilo CLIENTE
*/

#include "consola_cliente.h"

/* ----------------------------------------------
   Obtencion de valor de entradas automaticamente
   ---------------------------------------------- */

struct
{
	comandos id;
	const char *str;
} cfg_keys[] = {
	{CLIENTE, "cliente"},
	{TEST, "test"},
	{CLEAR, "clear"},
	{HELP, "help"},
	{SALIR, "salir"}};

// ----------------------------------- FIN DE DECLARACIONES -----------------------------------------

int n_cfg_keys = sizeof(cfg_keys) / sizeof(cfg_keys[0]);

/* -------------------
   Se busca el mensaje 
   ------------------- */
int parse_cfg_key(const char *str)
{
	int i;
	for (i = 0; i < n_cfg_keys; i++)
		if (strcmp(str, cfg_keys[i].str) == 0)
			return cfg_keys[i].id;

	return INVALIDO;
}

/* -----------------
   f.Limpia pantalla
   ----------------- */
void clearScreen()
{
	const char *CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREE_ANSI, 12);
}

int leerCadena(char *cad, int n)
{
	int i = -1, c;

	c = getchar();
	if (c == EOF)
	{
		cad[i] = '\0';
		return 0;
	}

	if (c == '\n')
		i = 0;
	else
	{
		cad[0] = c;
		i = 1;
	}

	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		cad[i] = c;

	cad[i] = '\0';

	if (c != '\n' && c != EOF)
		while ((c = getchar()) != '\n' && c != EOF)
			;

	return strlen(cad);
}

/* -------------------------------
   f.Menu mensajes de mod. Cliente
   ------------------------------- */
int fClienteMensajes()
{

	int mensaje = 0;

	printf("\t==============================\n");
	printf("\t  Mensajes de modulo Cliente  \n");
	printf("\t==============================\n");
	printf("\t                              \n");
	printf("\t 1. Consultar Restaurantes    \n");
	printf("\t                              \n");
	printf("\t 2. Consultar Recetas  	    \n");
	printf("\t                              \n");
	printf("\t 3. Realizar Pedido			\n");
	printf("\t                              \n");
	printf("\t 4. Consultar Pedido          \n");
	printf("\t                              \n");
	printf("\t 5. Confirmar Pedido		  	\n");
	printf("\t                              \n");
	printf("\t 6. Regreso a consola         \n");
	printf("\t                              \n");
	printf("\t==============================\n");
	printf("\t                              \n");
	printf("\t Ingresar opcion: ");
	scanf("%d", &mensaje);

	return mensaje;
}

/* -------------------------
   f.Menu testing de modulos
   ------------------------- */
void fTesting(int modulo_test)
{
	int opcion_test_mensaje = 0;
	switch (modulo_test)
	{
	case 1:
		printf("\t								\n");
		printf("\t===========================	\n");
		printf("\t Test modulo APP	     		\n");
		printf("\t===========================	\n");
		printf("\t1. Consultar Restaurantes   	\n");
		printf("\t2. Seleccionar Restaurantes 	\n");
		printf("\t3. Consultar Platos	      	\n");
		printf("\t4. Crear Pedido				\n");
		printf("\t5. Agregar Plato				\n");
		printf("\t6. Plato listo				\n");
		printf("\t7. Confirmar Pedido			\n");
		printf("\t8. Consultar Pedido			\n");
		printf("\t9. Salir						\n");
		printf("\t===========================	\n");
		printf("\t								\n");
		printf("\t Ingresar opcion: \n");
		scanf("%d", &opcion_test_mensaje);
		switch (opcion_test_mensaje)
		{
		case 1:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Consultar Restaurantes\n");
			printf("\t      \n");

			printf("\t      \n");
			consultarRestaurante();
			opcion_test_mensaje = 0;
			break;
		case 2:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Seleccionar Restaurantes\n");
			printf("\t      \n");

			printf("\t      \n");
			seleccionarRestaurantes();
			opcion_test_mensaje = 0;
			break;
		case 3:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Consultar Platos\n");
			printf("\t      \n");

			printf("\t      \n");
			consultarPlatos();
			opcion_test_mensaje = 0;
			break;
		case 4:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Crear Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			crearPedido();
			opcion_test_mensaje = 0;
			break;
		case 5:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Agregar Plato\n");
			printf("\t      \n");

			printf("\t      \n");
			anadirPlato();
			opcion_test_mensaje = 0;
			break;
		case 6:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Plato listo\n");
			printf("\t      \n");

			printf("\t      \n");
			platoListo();
			opcion_test_mensaje = 0;
			break;
		case 7:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Confirmar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			confirmarPedido();
			opcion_test_mensaje = 0;
			break;
		case 8:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo APP\n");
			printf("\t\t	-mensaje Consultar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			consultarPedido();
			opcion_test_mensaje = 0;
			break;
		case 9:
			printf("\t		\n");
			salirModulo();
			opcion_test_mensaje = 0;
			break;
		}
		break;
	case 2:
		printf("\t							\n");
		printf("\t=========================	\n");
		printf("\t Test modulo COMANDA 	   	\n");
		printf("\t=========================	\n");
		printf("\t1. Guardar Pedido 	   	\n");
		printf("\t2. Guardar Plato	   		\n");
		printf("\t3. Obtener Pedido	   		\n");
		printf("\t4. Confirmar Pedido	   	\n");
		printf("\t5. Plato listo	   		\n");
		printf("\t6. Finalizar Pedido	   	\n");
		printf("\t7. Salir					\n");
		printf("\t=========================	\n");
		printf("\t							\n");
		printf("\t Ingresar opcion: ");
		scanf("%d", &opcion_test_mensaje);
		switch (opcion_test_mensaje)
		{
		case 1:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo COMANDA\n");
			printf("\t\t	-mensaje Guardar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			guardarPedido();
			opcion_test_mensaje = 0;
			break;
		case 2:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo COMANDA\n");
			printf("\t\t	-mensaje Guardar Plato\n");
			printf("\t      \n");

			printf("\t      \n");
			guardarPlato();
			opcion_test_mensaje = 0;
			break;
		case 3:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo COMANDA\n");
			printf("\t\t	-mensaje Obtener Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			obtenerPedido();
			opcion_test_mensaje = 0;
			break;
		case 4:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo COMANDA\n");
			printf("\t\t	-mensaje Confirmar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			confirmarPedido();
			opcion_test_mensaje = 0;
			break;
		case 5:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo COMANDA\n");
			printf("\t\t	-mensaje Plato listo\n");
			printf("\t      \n");

			printf("\t      \n");
			platoListo();
			opcion_test_mensaje = 0;
			break;
		case 6:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo COMANDA\n");
			printf("\t\t	-mensaje Finalizar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			finalizarPedido();
			opcion_test_mensaje = 0;
			break;
		case 7:
			printf("\t		\n");
			salirModulo();
			opcion_test_mensaje = 0;
			break;
		}
		break;
	case 3:
		printf("\t							\n");
		printf("\t=========================	\n");
		printf("\t Test modulo RESTAURANTE	\n");
		printf("\t=========================	\n");
		printf("\t1. Consultar Platos		\n");
		printf("\t2. Crear Pedido			\n");
		printf("\t3. Agregar Plato			\n");
		printf("\t4. Confirmar Pedido		\n");
		printf("\t5. Consultar Pedido		\n");
		printf("\t6. Salir					\n");
		printf("\t=========================	\n");
		printf("\t                          \n");
		printf("\t Ingresar opcion: ");
		scanf("%d", &opcion_test_mensaje);
		switch (opcion_test_mensaje)
		{
		case 1:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo RESTAURANTE\n");
			printf("\t\t	-mensaje Consultar Platos\n");
			printf("\t      \n");

			printf("\t      \n");
			consultarPlatos();
			break;
		case 2:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo RESTAURANTE\n");
			printf("\t\t	-mensaje Crear Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			crearPedido();
			break;
		case 3:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo RESTAURANTE\n");
			printf("\t\t	-mensaje Agregar Plato\n");
			printf("\t      \n");

			printf("\t      \n");
			anadirPlato();
			break;
		case 4:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo RESTAURANTE\n");
			printf("\t\t	-mensaje Confirmar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			confirmarPedido();
			break;
		case 5:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo RESTAURANTE\n");
			printf("\t\t	-mensaje Consultar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			consultarPedido();
			break;
		case 6:
			printf("\t		\n");
			salirModulo();
			break;
		}
		break;
	case 4:
		printf("\t							\n");
		printf("\t=========================	\n");
		printf("\t Test modulo SINDICATO	\n");
		printf("\t=========================	\n");
		printf("\t1. Consultar Platos		\n");
		printf("\t2. Guardar Pedido			\n");
		printf("\t3. Guardar Plato			\n");
		printf("\t4. Confirmar Pedido		\n");
		printf("\t5. Obtener Pedido			\n");
		printf("\t6. Obtener Restaurante	\n");
		printf("\t7. Plato listo			\n");
		printf("\t8. Terminar Pedido		\n");
		printf("\t9. Obtener Receta			\n");
		printf("\t0. Salir					\n");
		printf("\t=========================	\n");
		printf("\t							\n");
		printf("\t Ingresar opcion: ");
		scanf("%d", &opcion_test_mensaje);
		switch (opcion_test_mensaje)
		{
		case 1:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Consultar Platos\n");
			printf("\t      \n");

			printf("\t      \n");
			consultarPlatos();
			break;
		case 2:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Guardar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			guardarPedido();
			break;
		case 3:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Guardar Plato\n");
			printf("\t      \n");

			printf("\t      \n");
			guardarPlato();
			break;
		case 4:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Confirmar Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			confirmarPedido();
			break;
		case 5:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Obtener Pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			obtenerPedido();
			break;
		case 6:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Obtener Restaurante\n");
			printf("\t      \n");

			printf("\t      \n");
			obtenerRestaurante();
			break;
		case 7:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Plato listo\n");
			printf("\t      \n");

			printf("\t      \n");
			platoListo();
			break;
		case 8:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Terminar pedido\n");
			printf("\t      \n");

			printf("\t      \n");
			terminarPedido();
			break;
		case 9:
			printf("\t      \n");
			printf("\t Test elegido: \n");
			printf("\t\t	-modulo SINDICATO\n");
			printf("\t\t	-mensaje Obtener Receta\n");
			printf("\t      \n");
			obtenerReceta();
			printf("\t      \n");
			break;
		case 0:
			printf("\t		\n");
			salirModulo();
			break;
		}
		break;
	case 5:
		salirModulo();
		break;
		break;
	}
	fTesting(modulo_test);
}

void salirModulo()
{
	printf("\t      					\n");
	printf("\t                           \n");
	printf("\t Cerrando modulo Cliente...\n");
	printf("\t                           \n");
	exit(EXIT_SUCCESS);
}

/* -------------------
   f.Inicio de consola
   ------------------- */
void *iniciarConsola(void *args)
{
	log_info(logger, "Modulo %s", handshake_regreso->Modulo);
	if(handshake_regreso->Modulo == NULL){
		log_error(logger, "No hay respuesta del módulo");
		return;
	}
	//clearScreen();
	printf("\t                                                     \n");
	printf("\t=====================================================\n");
	printf("\t     Bienvenido a la consola del modulo Cliente      \n");
	printf("\t=====================================================\n");
	printf("\t                                                     \n");
	//printf("\t help: Opciones de menu de la consola.               \n");
	printf("\t                                                     \n");

	/*
		 1. App    
		 2. Comanda
		 3. Restaurante
		 4. Sindicato   
		*/
	if (string_contains(handshake_regreso->Modulo, "Restaurante"))
	{
		moduloActual = 3;
	}
	else if (string_contains(handshake_regreso->Modulo, "Comanda"))
	{
		moduloActual = 2;
	}
	else if (string_contains(handshake_regreso->Modulo, "Sindicato"))
	{
		moduloActual = 4;
	}
	else if (string_contains(handshake_regreso->Modulo, "App"))
	{
		moduloActual = 1;
	}
	else
	{
		moduloActual = 5;
	}
	fTesting(moduloActual);
	return NULL;
}