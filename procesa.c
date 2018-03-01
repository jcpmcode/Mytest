/**
* procesa.c-main
* @author Jose Carlos Paniagua Mendoza
*/

#include "operaciones.h"

int main (int argc, char **argv)
{
  int valores[256]; // Arreglo utilizado para contar cuantas veces se repitenn los valores de tonos en la imagen y poder generar el histograma.
  int i=0; // Contador utilizado para incializar el arreglo de valores.
  char nombre_imagen[25]; // String utilizado para almacenar el nombre de la imagen.

  if (argc < 3)
  {
    printf("ERROR: Faltan argumentos.\n");
    Ayuda();
  }
  else
  {
    if(argc > 3)
    {
      printf("ERRROR: Sobran argumentos.\n");
      Ayuda();
    }
    else
    {
      if (strstr(argv[1], ".raw") == NULL)
      {
        printf("ERROR: la extension del archivo de entrada no es .raw\n");
        Ayuda();
      }
      else
      {
        if (!((strcmp(argv[2], "-h") == 0) || (strcmp(argv[2], "-e") == 0)))
        {
          printf("ERROR: opcion de programa invalida, revise su segundo argumento.\n");
          Ayuda();
        }
        else
        {
          strcpy( nombre_imagen, argv[1]);
          if (strcmp(argv[2], "-h") == 0)
          {
            while(i<256) // Inicialización del arreglo valores[], en 0 cada elemento.
            {
              valores[i]=0;
              i++;
            }
            if (analiza_imagen(nombre_imagen, valores) == 1)
            {
              generar_archivo(valores);
              plot();
            }
          }
          else
          {
            ecualizar(nombre_imagen, valores);
          }
        }
      }
    }
  }
}
