/**
 * @file geraMat.c
 * @brief Criação e Operação com matrizes
 */

#ifndef __GERAMAT_H__
#define __GERAMAT_H__

//Geradores de coeficientes
double generateRandomA( unsigned int i, unsigned int j, unsigned int k );
double generateRandomB( unsigned int k );

//Geradores de Matrizes
double *createTestMatrix (unsigned int m, unsigned int n);
double *generateZeroMatrix(unsigned int m, unsigned int n);
double *generateBandMatrix (unsigned int k, unsigned int n);
double *generateIndTerms (unsigned int n, unsigned int k);

//Operações Com Matrizes
double *copyMatrix (double *arr, unsigned int m, unsigned int n);
double *sumMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n);
double *multiplyMatrix(double *arr1, unsigned int m1, unsigned int n1,
          double *arr2, unsigned int m2, unsigned int n2);
double *transposeMatrix (double *arr,unsigned int m, unsigned int n);
double *getDiagonal(double *arr, unsigned int m);
double *conjugateGradients(double *A, double *b, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp);
double *preconditioningCg(double *A, double *B, double * M, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp);


#endif //_GERAMAT_H