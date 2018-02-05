#include "operaciones.h"

int main (int argc, char **argv)
{
  unsigned char read[255];

  system("clear");
  if (Validar_argumentos_de_programa(argc, argv) == 1)
  {
    Abrir_imagen(argv);
  }
}
