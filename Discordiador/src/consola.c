#include "consola.h"

void mostrar_consola(){
    int var = 0;
    char* accion = string_new();

    while(var != 7){
        printf("------------------------------------------------------\n");
        printf("Ingrese un numero acorde a la instruccion a realizar \n");
        printf("1-Iniciar Patota \n");
        printf("2-Listar Tripulante \n");
        printf("3-Expulsar Tripulante \n");
        printf("4-Iniciar Planificacion \n");
        printf("5-Pausar Planificacion \n");
        printf("6-Obtener Bitacora \n");
        printf("7-Salir \n");
        printf("-----------------------------------------------------\n");
        scanf("%d",&var);
        printf("Ingrese instruccion: ");
        scanf("%s", accion);
        switch(var) {
            case 1:
                /*char* cant_patotas = string_new();
                char* path_tarea = string_new();
                scanf("%d", &var);
                scanf("%d", &var);
                scanf("%d", &var);
                scanf("%d", &var);
                scanf("%d", &var);
                printf("Parametros: %s\n", comando);*/   
                break; 
            case 2:
                ;
                break; 
            case 3:
                ;
                break; 
            case 4:
                ;
                break; 
            case 5:
                ;
                break; 
            case 6:
                ;
                break; 
            case 7:
                printf("Fin de consola\n");
                break; 
        }
        system("clear");
    }
}