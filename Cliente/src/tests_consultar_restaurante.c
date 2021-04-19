#include "tests_consultar_restaurante.h"


void test_serializar_consultar_restaurantes(){
    t_O_CONSULTAR_RESTAURANTE* croutput = malloc(sizeof(t_O_CONSULTAR_RESTAURANTE));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    croutput->t_nombreDeRes = list_create();
    croutput->cantNombreDeRes = 5;
    for(int c=0; c<croutput->cantNombreDeRes; c++){
        t_nombreDeRes* nombreDeRes = malloc(sizeof(t_nombreDeRes));
        nombreDeRes->nombreDeRes = "Restaurante1";
        nombreDeRes->nombreDeRes_length = strlen(nombreDeRes->nombreDeRes);
        list_add(croutput->t_nombreDeRes, nombreDeRes);
    }


    //Lo serializo
    paquete =  serializar_O_CONSULTAR_RESTAURANTE(croutput);

    //Genero una nueva variable
    t_O_CONSULTAR_RESTAURANTE* croutput2 = malloc(sizeof(t_O_CONSULTAR_RESTAURANTE));
    //Deserializo en esa variable
    croutput2 = deserializar_O_CONSULTAR_RESTAURANTE(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(croutput->cantNombreDeRes, croutput2->cantNombreDeRes );

    for(int c=0; c<croutput2->cantNombreDeRes; c++){

        t_nombreDeRes* nombreDeRes = list_get(croutput->t_nombreDeRes, c);
        t_nombreDeRes* nombreDeRes2 = list_get(croutput2->t_nombreDeRes, c);
        CU_ASSERT_STRING_EQUAL(nombreDeRes->nombreDeRes, nombreDeRes2->nombreDeRes );
    }

}