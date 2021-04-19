#include "tests_anadir_plato.h"


void test_serializar_I_ANADIR_PLATO(){
    t_I_ANADIR_PLATO* I_ANADIR_PLATO = malloc(sizeof(t_I_ANADIR_PLATO));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    I_ANADIR_PLATO->pedidoID = 1;
    t_plato* plato = malloc(sizeof(t_plato));
    plato->precio = 11;
    plato->nombre = "Comida";
    plato->nombre_length = strlen(plato->nombre);
    I_ANADIR_PLATO->plato = plato;
    //Lo serializo
    paquete =  serializar_I_ANADIR_PLATO(I_ANADIR_PLATO);

    //Genero una nueva variable
     t_I_ANADIR_PLATO* I_ANADIR_PLATO2 = malloc(sizeof(t_I_ANADIR_PLATO));
    //Deserializo en esa variable
     I_ANADIR_PLATO2 = deserializar_I_ANADIR_PLATO(paquete);
    //Comparo Valores
    
    CU_ASSERT_EQUAL(I_ANADIR_PLATO->pedidoID, I_ANADIR_PLATO2->pedidoID );

    CU_ASSERT_STRING_EQUAL(I_ANADIR_PLATO->plato->nombre, I_ANADIR_PLATO2->plato->nombre );
    CU_ASSERT_EQUAL(I_ANADIR_PLATO->plato->precio, I_ANADIR_PLATO2->plato->precio );
    CU_ASSERT_EQUAL(I_ANADIR_PLATO->plato->nombre_length, I_ANADIR_PLATO2->plato->nombre_length );


}