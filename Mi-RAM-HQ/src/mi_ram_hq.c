#include "mi_ram_hq.h"

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    {
        //run_tests();
        init_renderizacion_mapa();
        crear_tripulante(1, 0, 0);
        crear_tripulante(2, 4, 2);
        sleep(1);
        desplazar_tripulante(1, 0, 1);
        sleep(1);
        desplazar_tripulante(1, 0, 1);
        sleep(1);
        eliminar_tripulante(2);
    }
    else
    {
        cfg_create("cfg/mi_ram_hq.config");
        logger_create("cfg/mi_ram_hq.log", "MI_RAM_HQ");
        logger_info("Iniciando módulo Mi-RAM-HQ");
        
        int puerto = get_puerto();
      
        int tam_memoria = get_tamanio_memoria();
        iniciar_memoria_principal(tam_memoria);
        
        //Para paginación
        iniciar_memoria_virtual(get_tamanio_swap());
        inicializacion_estructuras();
        server_mi_ram_iniciar(puerto);

        signal(SIGUSR1, method_sigusr1);

        // Libero el log y config al final
        cfg_free();
        logger_free();

        return 1;
    }
}

void experimento(){
    t_list* huecos = list_create();
    t_hueco* hueco1 = malloc(sizeof(t_hueco));
    hueco1->base = 1;
    hueco1->desplazamiento = 1;
    t_hueco* hueco2 = malloc(sizeof(t_hueco));
    hueco2->base = 2;
    hueco2->desplazamiento = 2;
    list_add(huecos, hueco1);
    list_add(huecos, hueco2);

    t_hueco* hueco_temp = list_get(huecos, 0);
    hueco_temp->base = 100;

    for(int c=0; c<list_size(huecos);c++){
        t_hueco* hueco_temp = list_get(huecos, c);
        printf("Base: %d Desplazamiento: %d\n", hueco_temp->base, hueco_temp->desplazamiento);
    }
}