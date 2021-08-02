#include "util_mongostore.h"

int get_length_parts(char* filename){
  char** parts = string_split(filename, ".");

  int contador = 0;
  void recorrer_posiciones(char *item){
        contador ++;
  }
  string_iterate_lines(parts, recorrer_posiciones);
  return contador;
}

t_list* get_archivos_de_directorio(char* directorio)
{
    t_list* path_files = list_create();
  /* Con un puntero a DIR abriremos el directorio */
  DIR *dir;
  /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
  struct dirent *ent;

  /* Empezaremos a leer en el directorio actual */
  dir = opendir (directorio);

  /* Miramos que no haya error */
  if (dir == NULL) 
    error("No puedo abrir el directorio");
  
  /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
  /* Leyendo uno a uno todos los archivos que hay */
  while ((ent = readdir (dir)) != NULL) 
    {
      /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
      /* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */
      procesoArchivo(ent->d_name);
      
      if(get_length_parts(ent->d_name)>1){
        char* a = malloc(strlen(ent->d_name));
        strcpy(a, ent->d_name);
        list_add(path_files, a);
      }
    }
    }
  closedir (dir);
  return path_files;
} 

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo)
{
  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
  /* para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
  FILE *fich;
  long ftam;

  fich=fopen(archivo, "r");
  if (fich)
    {
      fseek(fich, 0L, SEEK_END);
      ftam=ftell(fich);
      fclose(fich);
      /* Si todo va bien, decimos el tamaño */
      //printf ("%s (%ld bytes)\n", archivo, ftam);
    }
  else
    /* Si ha pasado algo, sólo decimos el nombre */
    //printf ("%s (No info.)\n", archivo);

    return archivo;
}