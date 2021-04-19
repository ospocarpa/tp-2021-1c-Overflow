#include "tests_obtener_restaurante.h"


void test_serializar_input_obtener_restaurantes(){
    t_nombreDeRes* nombreDeRes = malloc(sizeof(t_nombreDeRes));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    nombreDeRes->nombreDeRes = "Restaurante1";
    nombreDeRes->nombreDeRes_length = strlen(nombreDeRes->nombreDeRes);


    //Lo serializo
    paquete =  serializar_I_OBTENER_RESTAURANTE(nombreDeRes);

    //Genero una nueva variable
     t_nombreDeRes* nombreDeRes2 = malloc(sizeof(t_nombreDeRes));
    //Deserializo en esa variable
    nombreDeRes2 = deserializar_I_OBTENER_RESTAURANTE(paquete);
    
    //Comparo Valores
    CU_ASSERT_STRING_EQUAL(nombreDeRes->nombreDeRes, nombreDeRes2->nombreDeRes );
    CU_ASSERT_EQUAL(nombreDeRes->nombreDeRes_length, nombreDeRes2->nombreDeRes_length );



}