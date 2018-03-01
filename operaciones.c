/**
* operaciones.c
* @author Jose Carlos Paniagua Mendoza
*/

#include "operaciones.h"

void Ayuda()
{
  printf("Utilizacion del programa:\n"
  "Este programa se ejecuta con 2 argumentos forzamente, el primero\n"
  "debe ser el nombre de la imagen a procesar, y el segundo es la opcion\n"
  "del programa que se desea utilizar. Las opciones son: \n"
  "-h: genera el histograma de la imagen ingresada como argumento.\n"
  "-e: ecualiza la imagen ingresada como argumento.\n");
}

int analiza_imagen(char nombre_imagen[], int valores[])
{
  FILE *entrada;// Apuntador de tipo file para abrir el archivo de entrada.
  unsigned char c;// Variable utilizada para ir leyedo caracter por caracter.

  entrada= fopen(nombre_imagen, "rb");
  if (entrada == NULL)
  {
    printf("El archivo ingresado no existe. Verifique si ingreso correctamente el nombre del archivo.\n");
    return 0;
  }
  else
  {
    fseek(entrada, 15, SEEK_SET);
    while(!feof(entrada)) // Se lee pixel por pixel la imagen.
    {
      fread(&c, sizeof(char), 1, entrada);
      if(feof(entrada)==0)
      {
        valores[c] ++; // Se va llenando un arreglo con contadores de las ocurrencias de los valores de los caracteres de la imagen.
      }
    }
    fclose(entrada);
  }
  return 1;
}

void generar_archivo(int valores[])
{
  int i=0; //
  FILE *salida; //Apuntador de tipo file utilizado para el archivo de salida.

  salida=fopen("salida.txt", "wt"); //El archivo de texto de salida siempre se llamaŕa salida.txt y siempre se sobreescribirá cada vez que se ejecute el programa.
  while(i<256) // Impresión de los datos del histograma en el archivo.
  {
    fprintf(salida, "%d\t  %d\n", i, valores[i]); //Se imprime el valor de 'x' y de 'y' en el archivo de salida cada vez que se calculan.
    i++;
  }
  fclose(salida);
}

void plot()
{
  int i=0; // Contador utilizado para el úmero de comandos.
  char * commandsForGnuplot[] = {"set title \"HISTOGRAMA\"", "plot 'salida.txt' using 1:2:xtic(2) with boxes"};
  /*Opens an interface that one can use to send commands as if they were typing into the
  *     gnuplot command line.  "The -persistent" keeps the plot open even after your
  *     C program tery1ates.
  */
  FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
  for (i=0; i < NUM_COMMANDS; i++)
  {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
  }
}

void ecualizar(char nombre_imagen[], int valores[])
{
  int m= 0; // m será utilizado para el cálculo de la pendiente.
  int max=-255; // En esta variable se almacenará el valor máximo del caracter dentro del archivo a ecualizar.
  int min=255;  // En esta variable se almacenará el valor mínimo del caracter dentro del archivo a ecualizar.
  char c; // Se utiliza para la lectura y escritura de las imagenes caracter por caracter.
  char encabezado[15]; // Aqui se almacena el encabezado de las imagenes .raw
  FILE *entrada; // File pointer utilizado para la imagen a procesar.
  FILE *salida; // File pointer donde se escribe la imagen nueva.

  entrada= fopen(nombre_imagen, "rb");
  fseek(entrada, 0L, SEEK_SET); // Nos movemos al principio del archivo.
  fread(encabezado, 1, sizeof(encabezado), entrada); // Leemos el encabezado de la imagen.
  fseek(entrada, 15, SEEK_SET); // Nos movemos hasta el primer pixel de la imagen.
  while(!feof(entrada)) // Se lee el archivo caracter por caracter (byte por byte).
  {
    fread(&c, sizeof(char), 1, entrada);
    if(feof(entrada)==0)
    {
      if(c > max)
      {
        max=c; // Se obtiene el valor máximo de los caracteres de la imagen.
      }
      if(c<min)
      {
        min=c; // Se obtiene el valor minimo de los caracteres de la imagen.
      }
    }
  }
  m = 255/(max-min); // Calculo de la pendeiente. Se usa el 255 para que los valores no se salgan del rango que tiene que ocupar las dimensiones de la imagen.
  fseek(entrada, 0L, SEEK_SET); // Volvemos al inicio de la imagen.
  fseek(entrada, 15, SEEK_SET); // Vamos al primer pixel de la imagen.
  salida= fopen("salida.raw", "wb");
  fprintf(salida, "%s", encabezado);
  while(!feof(entrada)) // Se lee pixel por pixel al mismo tiempo que se hace la escritura en la nueva imagen.
  {
    fread(&c, sizeof(char), 1, entrada);
    c= c*m; // Cada pixel nuevo es igual al pixel original multiplicado por la pendiente calculada anteriormente.
    if(feof(entrada)==0)
    {
      fwrite(&c, 1, sizeof(char),salida);
    }
  }
  fclose(salida);
  fclose(entrada);
}
