/**
 * @file validadeEntry.c
 * @brief Leitura e validação dos parâmetros de entrada
 */

#ifndef __VALIDATEENTRY_H__
#define __VALIDATEENTRY_H__

#include <stdlib.h>
#include <stdio.h>
 /***********************
* @briefFunções para obter e conferir a presença de todos os valores de entrada
 ***********************/
void catchInt( char *param, char *next, char *test, int *num);
void catchFloat( char *param, char*next, char *test, double *num);

 /***********************
 * @brief Funções para validar os valores de entrada
 ***********************/
void validateIterations(int i);
void validateDimension(int n);
void validateDiagonals(int k);

#endif // __UTILS_H__

