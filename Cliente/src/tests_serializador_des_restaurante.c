#include "tests_serializador_des_restaurante.h"

void test_serializar_t_restaurantes()
{
    t_restaurante *croutput = malloc(sizeof(t_restaurante));
    t_paquete *paquete = malloc(sizeof(t_paquete));

    /*
	uint32_t cantCocineros;
	uint32_t cantHornos;
	t_posicion *posicion; 2x uint32_t
	uint32_t cantAfinidad;
	t_list *afinidadCocineros; // list [t_afinidad]
	uint32_t cantPlatos;
	t_list *platos; // list [t_plato]
   */

    //Cargo Valores
    croutput->nombre = "NombreRestaurante";
    croutput->nombre_length = strlen(croutput->nombre);
    croutput->cantCocineros = 7;
    croutput->cantHornos = 10;
    t_posicion *posicion = malloc(sizeof(t_posicion));
    posicion->pos_x = 42;
    posicion->pos_y = 24;
    croutput->posicion = posicion;
    croutput->cantPlatos = 3;
    croutput->cantPedidos = 5;
    croutput->platos = list_create();
    for (int c = 0; c < croutput->cantPlatos; c++)
    {
        t_plato *plato = malloc(sizeof(t_plato));
        plato->nombre = "Plato1";
        plato->nombre_length = strlen(plato->nombre);
        plato->precio = 1;
        list_add(croutput->platos, plato);
    }
    croutput->cantAfinidad = 1;
    croutput->afinidadCocineros = list_create();

    for (int c = 0; c < croutput->cantAfinidad; c++)
    {
        t_afinidad *afinidad = malloc(sizeof(t_afinidad));
        afinidad->nombre = "Plato1";
        afinidad->nombre_length = strlen(afinidad->nombre);
        list_add(croutput->afinidadCocineros, afinidad);
    }

    //Lo serializo
    paquete = serializar_restaurante(croutput);

    //Genero una nueva variable
    t_restaurante *croutput2 = malloc(sizeof(t_restaurante));
    //Deserializo en esa variable
    croutput2 = deserializar_restaurante(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(croutput->cantPedidos, croutput2->cantPedidos);
    CU_ASSERT_EQUAL(croutput->cantCocineros, croutput2->cantCocineros);
    CU_ASSERT_EQUAL(croutput->cantHornos, croutput2->cantHornos);
    CU_ASSERT_EQUAL(croutput->posicion->pos_x, croutput2->posicion->pos_x);
    CU_ASSERT_EQUAL(croutput->posicion->pos_y, croutput2->posicion->pos_y);

    //printf("Nombre %s\n",croutput->nombre);
    //printf("Nombre %s\n",croutput2->nombre);

    //printf("Long %d\n",croutput->nombre_length);
    //printf("Long %d\n",croutput2->nombre_length);

    CU_ASSERT_STRING_EQUAL(croutput->nombre, croutput2->nombre);

    CU_ASSERT_EQUAL(croutput->cantPlatos, croutput2->cantPlatos);
    CU_ASSERT_EQUAL(croutput->cantAfinidad, croutput2->cantAfinidad);

    for (int c = 0; c < croutput->cantPlatos; c++)
    {
        t_plato *plato = list_get(croutput->platos, c);
        t_plato *plato2 = list_get(croutput2->platos, c);

        CU_ASSERT_STRING_EQUAL(plato->nombre, plato2->nombre);
        CU_ASSERT_EQUAL(plato->precio, plato2->precio);
    }

    for (int c = 0; c < croutput->cantAfinidad; c++)
    {
        t_afinidad *afinidad = list_get(croutput->afinidadCocineros, c);
        t_afinidad *afinidad2 = list_get(croutput2->afinidadCocineros, c);

        CU_ASSERT_STRING_EQUAL(afinidad->nombre, afinidad2->nombre);
    }
}