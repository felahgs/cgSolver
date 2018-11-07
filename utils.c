/**
 * @file utils.c
 * @brief Calculo de tempo e impressão de matrizes
 */

#include "utils.h"
#include <stdio.h>

/***********************
 * Retorna tempo em milisegundos
 ***********************/
double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

/***********************
 * Função que imprime uma matriz quadrada de uma forma facil de ler
 * *arr: ponteiro da matriz
 * m, n: dimensões da matriz
 ***********************/
void printMat(double *arr, unsigned int m, unsigned int n, FILE *fp)
{
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
  {
    for (j = 0; j < n; j++) 
    {
      fprintf(fp, "%.15g ", *(arr + i*n + j));
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
}

void printArray(double *arr, unsigned int m, unsigned int n)
{
  for (int i = 0; i < m*n; i++)
  {
    printf("%6.2f ", *(arr + i));
  }
  printf("\n");
}