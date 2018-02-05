#include "operaciones.h"

void Ayuda() //Función que despliega un mensaje de ayuda (explicación del uso del programa).
{
  printf(
    "\nAyuda:\n"
    "Para utilizar este programa tiene que ejecutarlo con 2 argumentos, el primer argumento\n"
    "tiene que ser el nombre del archivo que se quiere copiar, el segundo argumento debe ser\n"
    "el nombre del archivo de salida en donde se quiere almacenar la copia de la imagen.\n"
    "Es muy importante que ambos nombres deben ser ingresados con la extension .raw, de lo\n"
    "contrario el programa no funcionara.\n\n"
  );
}

int Validar_argumentos_de_programa(int argc, char **argv) //Función que valida el número de argumentos y su contenido.
{
  if (argc != 3)
  {
    printf("ERROR: Numero de argumentos incorrecto.\n");
  }
  else
  {
    if (strstr(argv[1], ".raw") == NULL)
    {
      printf("ERROR: la extension del archivo de entrada no es .raw\n");
    }
    else
    {
      if (strstr(argv[2], ".raw") == NULL)
      {
        printf("ERROR: la extension del archivo de salida no es .raw\n");
      }
      else
      {
        if (strcmp(argv[1], argv[2]) == 0)
        {
          printf("ERROR: Los nombres de los archivos de entrada y salida no pueden ser iguales.\n");
        }
        else
        {
          return 1;
        }
      }
    }
  }
  return 0;
}

void Abrir_imagen(char **argv)
{
  FILE *entrada, *salida;
  unsigned char c;
  char str[25];
  int i=0;
  int flag = 0;

  entrada= fopen(argv[1], "rt");
  if (entrada == NULL)
  {
    printf("El archivo ingresado no existe. Verifique si ingreso correctamente el nombre del archivo.\n");
  }
  else
  {
    salida= fopen(argv[2], "wt");
    if (salida != NULL)
    {
      while (flag == 0)
      {
        printf("Ya existe un archivo con ese nombre, desea sobreescribirlo? [si | no]\n");
        gets(str);
        if(strcasecmp(str, "no") == 0)
        {
          printf("Vuelva a ejecutar el programa con otro nombre para archivo de salida.\n");
          return;
        }
        else
        {
          if (strcasecmp(str, "si") == 0)
          {
            flag = 1;
            while((c=getc(entrada)) != EOF)//Se lee carácter por carácter el archivo en un ciclo.
            {
              // if(i<10)
              // {
                printf("%d\t%c\n", i, c);
                // fputc(c, salida);
              // }
              // else
              // {
              //   return;
              // }
              i++;//Se incrementa un contador cada que se encuentra una letra.
            }
            fclose(salida);
            fclose(entrada);
          }
          else
          {
            printf("ERROR: Ingrese una opcion valida.\n");
          }
        }
      }
    }
  }
}
