#!/bin/bash
echo -e "\n\nHaciendo make de todos los modulos...\n\n"
make -C ./Cliente
make -C ./Discordiador
make -C ./MongoStore
make -C ./Mi-RAM-HQ
echo -e "\n\nHechos los makes!\n\n"
