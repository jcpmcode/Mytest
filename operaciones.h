/**
 * operaciones.h
 * @author Jose Carlos Paniagua Mendoza
 */

#define NUM_COMMANDS 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Función que despliega un mensaje de ayuda (explicacion del funcionamiento y uso del programa).
 */
void Ayuda();

/**
 * Función que analiza el código de la imagen .raw caracter por caracter y almacena la ocurrencia de cada caracater en un arreglo.
 * @param nombre_imagen [string donde se almacena el nombre de la imagen a procesar]
 * @param valores [arreglo en donde se almacena el numero de repeticiones por caracter]
 */
int analiza_imagen(char nombre_imagen[], int valores[]);

/**
 * Función que genera el archivo de salida con los datos listos para ser graficados por gnuplot.
 * @param valores [arreglo en donde se almacena el numero de repeticiones por caracter]
 */
void generar_archivo(int valores[]);

/**
 * Función que automatiza el proceso de graficar el histograma por medio de la herramienta de gnuplot.
 * Código obtenido de https://stackoverflow.com/questions/3521209/making-c-code-plot-a-graph-automatically
 */
void plot();

/**
 * Función que ecualiza una imagen, es decir, linealizar los valores de los tonos para que se ajusten a un tono especifico.
 * @param nombre_imagen [string donde se almacena el nombre de la imagen a procesar]
 * @param valores       [arreglo en donde se almacena el numero de repeticiones por caracter]
 */
void ecualizar(char nombre_imagen[], int valores[]);
