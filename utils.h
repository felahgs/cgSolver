/**
 * @file utils.c
 * @brief Calculo de tempo e impressão de matrizes
 */


#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

// Aproximação aceitável como valor zero
#define ZERO 1.0e-20

// Parâmetros para teste de convergência
#define EPS 1.0e-8

double timestamp(void);
void printMat(double *arr, unsigned int m, unsigned int n, FILE *fp);
void printArray(double *arr, unsigned int m, unsigned int n);

#endif // __UTILS_H__

