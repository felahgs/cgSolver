/**
 * @file geraMat.c
 * @brief Criação e Operação com matrizes
 */

#include <stdlib.h>
#include <stdio.h> 
#include <math.h>

#include "geraMat.h"
#include "utils.h"
/***********************
 * @brief Função que gera os coeficientes de um sistema linear k-diagonal
 * @param i coordenada da linha do elemento a ser calculado (0<=i)
 * @param j coordenada da coluna do elemento a ser calculado (j<n)
 * @param k numero de diagonais da matriz A
 ***********************/
inline double generateRandomA( unsigned int i, unsigned int j, unsigned int k )
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return ( (i==j)?(double)(k<<1) : 1.0 )  * (double)rand() * invRandMax;
}

/***********************
 * @brief Função que gera os termos independentes de sistema linear k-diagonal
 * @param k numero de diagonais da matriz A
 ***********************/
inline double generateRandomB( unsigned int k ) 
{
  static double invRandMax = 1.0 / (double)RAND_MAX;
  return (double)(k<<2) * (double)rand() * invRandMax;
}

/***********************
 * @brief Função que produz uma matriz de testes
 * @param m numero de linhas da matriz 
 * @param n numero de colunas da matriz
 * 
 * Coordenadas da matriz são iniciadas na coordenada 0 e vão até n-1 (C array)
 ***********************/
 double *createTestMatrix (unsigned int m, unsigned int n) 
 {
    double *arr = (double *)malloc(m * n * sizeof(double));
 
    int i, j, count = 0;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(arr + i*n + j) = ++count;
      }
    }
      
    return arr;
 }
 
 /***********************
 * Função gera uma matriz nula
 * 
 * @param n dimensão da matriz 
 * @param k numero de diagonais da matriz A
 ***********************/
  double *generateZeroMatrix (unsigned int m, unsigned int n) 
 {
    double *arr = (double *)malloc(m * n * sizeof(double));
 
    int i, j;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(arr + i*n + j) = 0;
      }
    }
    return arr;
 }
 
 /***********************
 * @brief Função que produz uma matriz esparsa  k-diagonal
 * @param n dimensão da matriz 
 * @param k numero de diagonais da matriz A
 * 
 * Produz uma matriz esparsa  k-diagonal utilizando generateRandomA
 * e popula as diagonais de acordo com o parâmetro "k" que indica o número de
 * diagonais com coeficientes diferentes de 0.
 * 
 * As coordenadas da matriz são iniciadas na coordenada 0 e vão até n-1 seguindo
 * os tamanhos padrões de arrys em C.
 * 
 * As diagonais são definidas pelo parâmetro "k" onde k é sempre ímpar, caso
 * k sejá maior que o número de diagonais máximas para a matriz de dimensão n,
 * a matriz gerada será completamente preenchida com o maior número de diagonais
 * possíveis para dada matriz, ou seja, ela será totalmente preenchida não 
 * possuindo nenhum valor 0.
 ***********************/
  double *generateBandMatrix (unsigned int n, unsigned int k) 
 {
    double *arr = (double *)malloc(n * n * sizeof(double));
    int m = (k+1)/2, i, j;
 
    for (i = 0; i <  n; i++) 
      for (j = 0; j < n; j++) 
      {
        *(arr + i*n + j) = 0;
        if( (j>=i && j<(i+m)) || (j<i && j>(i-m)) )
          *(arr + i*n + j) = generateRandomA(i,j,k);
      }
    
    return arr;
 }
 
 /***********************
 * @brief Função que gera o array de termos independentes do sistema a ser calculado
 * 
 * @param n dimensão da matriz que resulta nos termos
 * @param k numero de diagonais da matriz A
 * @return double array de termos independentes gerados
 ***********************/
 double *generateIndTerms (unsigned int n, unsigned int k)
 {
  // int i;
  int i, count = 50;
  double *arr = (double *)malloc(n * sizeof(double));
  for (i = 0; i <  n; i++) {
    *(arr + i) = generateRandomB(k);
  }
  return arr;
 }
 
  /***********************
 * @brief Cria uma copia do array passado como parametro
 * @param *arr matriz a ser copiada
 * @param m numero de linhas da matriz 
 * @param n numero de colunas da matriz
 ***********************/
 
 double *copyMatrix (double *arr, unsigned int m, unsigned int n) 
 {
    double *newArr = (double *)malloc(m * n * sizeof(double));
 
    int i, j, count = 0;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(newArr + i*n + j) = *(arr + i*n + j);
      }
    }
      
    return newArr;
 }
 
 /***********************
 * @brief Função que calcula a transposta de uma matriz devolvendo á como uma array
 * de double
 * @param m número de linhas da matriz original
 * @param n número de colunas da matriz original
 ***********************/
double *transposeMatrix(double *arr, unsigned int m, unsigned int n)
{
  double *arrT = (double *)malloc(m * n * sizeof(double));
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
    for (j = 0; j < n; j++) 
      *(arrT + j*m + i) = *(arr + i*n + j);
  return arrT;
}

  /***********************
 * @brief Retorna a matriz diagonal correspondente da matriz quadrada passada
 * @param *arr matriz para se tirar a diagonal
 * @param m dimensões da matriz
 * @return a matriz diagonal de arr
 ***********************/
double *getDiagonal(double *arr, unsigned int m)
{
  double *arrD = (double *)malloc(m * m * sizeof(double));
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
    for (j = 0; j < m; j++) 
    {
      if(i == j) 
        *(arrD + j*m + i) = *(arr + j*m + i);
      else 
        *(arrD + j*m + i) = 0;
    }
  return arrD;
}

  /***********************
 * @brief Retorna a matriz inversa de uma matriz diagonal. A matriz parametro deve
 * ser uma matriz diagonal, caso contrario a saída não ser correta
 * 
 * @param *arr matriz diagonal para calcular sua inversa
 * @param m dimensões da matriz


 * @return a matriz diagonal de arr
 ***********************/
double *invDiagonal(double *arr, unsigned int m)
{
  double *arrI = (double *)malloc(m * m * sizeof(double));
  unsigned int i, j;
  for (i = 0; i <  m; i++) 
    for (j = 0; j < m; j++) 
      if(i == j) 
        *(arrI + j*m + i) = (1 / *(arr + j*m + i));
      else 
        *(arrI + j*m + i) = 0;
  return arrI;
}

  /***********************
 * @brief Soma tudas matrizes de mesmas dimensões
 * @param *arr1 primeira matriz da soma
 * @param *arr2 segunda matriz da soma
 * @param m numero de linhas das matrizes
 * @param n numero de colunas das matrizes

 * @return a matriz resultante da soma de ambas as entradas
 ***********************/
 
 double *sumMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n)
 {
    double *newArr = (double *)malloc(m * n * sizeof(double));
 
    int i, j;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(newArr + i*n + j) = *(arr1 + i*n + j) + *(arr2 + i*n + j);
      }
    }
      
    return newArr;
 }
 
   /***********************
 * @brief Subtrai tudas matrizes de mesmas dimensões
 * @param *arr1 primeira matriz da soma
 * @param *arr2 segunda matriz da soma
 * @param m numero de linhas das matrizes
 * @param n numero de colunas das matrizes

 * @return a matriz resultante da soma de ambas as entradas
 ***********************/
 
 double *subtractMatrix (double *arr1, double *arr2, unsigned int m, unsigned int n)
 {
    double *newArr = (double *)malloc(m * n * sizeof(double));
 
    int i, j;
    for (i = 0; i <  m; i++) {
      for (j = 0; j < n; j++) 
      {
         *(newArr + i*n + j) = *(arr1 + i*n + j) - *(arr2 + i*n + j);
      }
    }
      
    return newArr;
 }

 /***********************
 * @brief Calcula o produto de duas matrizes e retorna o resultado como uma nova
 * @param *arr1 ponteiro para a primeira matriz
 * @param m1 número de linhas da matriz primeira matriz
 * @param n1 número de colunas da matriz primeira matriz
 * @param *arr1 número de linhas da matriz original
 * @param m2 número de linhas da segunda matriz
 * @param n2 número de colunas segunda matriz
 * 
 * @return Devolve um ponteiro com o resultado da multiplicação arr1 X arr2
 ***********************/
double *multiplyMatrix(double *arr1, unsigned int m1, unsigned int n1,
          double *arr2, unsigned int m2, unsigned int n2) 
{
  double sum, *arrR = (double *)malloc(m1 * n2 * sizeof(double));
  unsigned int i, j, k;
  for ( i = 0; i < m1; i++) 
  {
    for (j = 0; j < n2; j++) 
    {
      sum = 0;
      for (k = 0; k < m2; k++)
      {
        sum = sum + ( *(arr1 + i*n1 + k) * *(arr2 + k*n2 + j) );
      }
      *(arrR + i*n2 + j) = sum;
    }
  }
    return arrR;
}


   /***********************
 * @brief Retorna maior elemento do array
 * @param *arr 
 * @param m dimensões do array

 * @return max maior elemento do array
 ***********************/
 
 double maxN (double *arr, unsigned int m, unsigned int n)
 {
    int i;
    float max = 0;
    for (i = 0; i <  m*n; i++) 
    {
        if (max < *(arr + i));
         max = *(arr + i);
    }
    return max;
 }
 
    /***********************
 * @brief Retorna a norma euclidiana da matriz
 * @param *A matriz principal
 * @param *b vetor de termos independentes
 * @param *x vetor de resultados 
 * @param n dnimensão da matriz 
 * @param variável para o calculo do tempo da função

 ***********************/
 
 double calculateNorm (double *A, double *b, double *x, int n, double *nTime)
 {
    *nTime = timestamp();
    double *aux, *aux1, norm;
    aux = multiplyMatrix(A, n, n, x, n, n);
    aux1 = subtractMatrix(b, aux, n, 1);
    
    norm = fabs(maxN(aux1, n, 1));
    
    *nTime = timestamp() - *nTime;
    free (aux); free (aux1);
    
    return norm;
    
 }


 /***********************
 * @brief Resolve o sistema utilizando o Metodo dos Gradientes Conjugados
 * @param *A matriz contendo o sistema linear a ser calculado
 * @param *b matriz de termos independentes de A
 * @param n dimensao da matriz A
 * @param maxIt numero maximo de iterações
 * @param eps erro maximo admitido para o criterio de parada
 * @param n número de colunas da matriz original
 * @param *fp arquivo de saída
 ***********************/
double *conjugateGradients(double *A, double *B, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp) 
{
   double *At, *X, *Xn, *R, *R1, *R2, *V, *Z, aux, s, m, timePC = 0, timeIt,
      itTotal = 0, timeNorm = 0;
   int it = 0;
   
   /**** Operations for transforming the Matrix in a symmetric matrix *******/
   At = transposeMatrix(A, n, n);
   R1 = multiplyMatrix(At, n, n, A, n, n); 
   R2 = multiplyMatrix(At, n, n, B, n, 1); 
   free(A); free(B);
   A = copyMatrix(R1, n, n); // A = AT * A
   B = copyMatrix(R2, n, 1); // b = AT * b
   free(R1); free(R2);
   /*******************************************************************/
    
   X = generateZeroMatrix(n,1); //x(0) = 0
   R = copyMatrix(B, n, 1); // r = b
   R1 = multiplyMatrix(R, 1, n, R, n, 1); //rT*r
   aux = *R1; //aux = rT*r
   V = copyMatrix(B, n, 1); // v = b
  /*******************************************************************/
  
 /************************ Iteration *******************************/
  for (int k = 0; k < maxIt; k++) {
    
      timeIt = timestamp();
      it++;
       
      Z = multiplyMatrix(A, n, n, V, n, 1); // z = A*v
       
      free(R1);
      R1 = multiplyMatrix(V, 1, n, Z, n, 1); //(vT * z)
      s = aux / *R1; //s = aux/(vT*z)
       
      *R1 = s; // Put the result of s in a 1x1 matrix to be multiplied
      R2 = multiplyMatrix(R1, 1, 1, V, 1, n); //(s * V);
      Xn = sumMatrix(X, R2, n, 1); // X(k+1) = X(k) + s*V
       
      free(R2);
      R2 = multiplyMatrix(R1, 1, 1, Z, 1, n);  //s*Z
      free(R1); free(R);
      R1 = copyMatrix(R, n, 1); //R1 = r
      R = subtractMatrix(R1, R2, n, 1); // r = r - sz
       
      free(R2);
      R2 = multiplyMatrix(R, 1, n, R, n, 1); //aux1 = rT * r
       
      fprintf(fp, "# iter %d: %.15g\n",  it, *R2);
      if (*R2 < eps) {
        
        double r = calculateNorm(A,B,Xn,n,&timeNorm);
        
        fprintf(fp, "# Residuo: %.15g \n", r);
        fprintf(fp, "# Tempo PC: %.15g sec \n", (timePC / 1000));
        fprintf(fp, "# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
        fprintf(fp, "# Tempo residuo: %.15g sec \n", timeNorm/1000);
        fprintf(fp, "# \n");
        fprintf(fp,"%d\n", n);
        printMat(Xn,1,n,fp);
        return Xn; // Saída com  sol  =  x{k+l )
      }
       
      m = *R2/aux; // m = aux1/aux;
      aux = *R2; // aux = aux1
       
      *R2 = m; //Puting the value of m in an array to peform an operation with
               //matrices
      free(R1);
      R1 = multiplyMatrix(R2, 1, 1, V, 1, n); // (m * V)
      free(V);
      V = sumMatrix(R, R1, n, 1); // V = R + (m * V)
       
      free(X);
      X = copyMatrix(Xn, 1, n); // Prepare for next iteration X(k) = X(k+1)
      free(Xn); free(Z); free(R2);
      itTotal = itTotal + (timestamp() - timeIt);
  }
    /*******************************************************************/
    
    fprintf(fp, "\nErro! Sistema não converge!\n");
    fprintf(stderr, "Erro! Sistema não converge!\n");
    exit(1);
}


 /***********************
 * @brief Resolve o sistema utilizando o Metodo dos Gradientes Conjugados com 
 *  pré condicionador
 * @param *A matriz contendo o sistema linear a ser calculado
 * @param *b matriz de termos independentes de A
 * @param *M matriz pré condicionadora
 * @param dimensao da matriz A
 * @param maxIt numero maximo de iterações
 * @param eps erro maximo admitido para o criterio de parada
 * @param n número de colunas da matriz original
 * @param *fp arquivo de saída
 ***********************/
double *preconditioningCg(double *A, double *B, double *M, unsigned int n, 
      unsigned int maxIt, double eps, FILE *fp) 
{
  double *At, *X, *Xn, *R, *R1, *R2, *V, *Z, *Y, aux, s, m, timePC = 0, timeIt,
      itTotal = 0, timeNorm = 0;
  int it = 0;
   
  /*** Operations for transforming the Matrix into a symmetric matrix *****/
  timePC = timestamp();
  At = transposeMatrix(A, n, n);
  R1 = multiplyMatrix(At, n, n, A, n, n); 
  R2 = multiplyMatrix(At, n, n, B, n, 1); 
  free(A); free(B);
  A = copyMatrix(R1, n, n); // A = AT * A
  B = copyMatrix(R2, n, 1); // b = AT * b
  free(R1); free(R2);
    /*******************************************************************/
  
  /*********** Invertion of the preconditioning matrix ****************/
  R1 = invDiagonal(M, n);
  free(M);
  M = copyMatrix(R1, n, n);
  free(R1);
  timePC = timestamp() - timePC;
  /*******************************************************************/
  
  X = generateZeroMatrix(n,1); //x(0) = 0
  R = copyMatrix(B, n, 1); // r = b
  V = multiplyMatrix(M, n, n, B, n, 1); // V = M^(-1) * b
  R1 = multiplyMatrix(V, 1, n, V, n, 1); //yT*r
  aux = *R1; //aux = yT*r
  /*******************************************************************/
   
  /************************ Iteration *******************************/
  for (int k = 0; k < maxIt; k++) {
    timeIt = timestamp();
      it++;
      
      Z = multiplyMatrix(A, n, n, V, n, 1); // z = A*v
      
      free(R1);
      R1 = multiplyMatrix(V, 1, n, Z, n, 1); //(vT * z)
      s = aux / *R1; //s = aux/(vT*z)
      
      *R1 = s; // Put the result of s in a 1x1 matrix to be multiplied
      R2 = multiplyMatrix(R1, 1, 1, V, 1, n); //(s * V);
      Xn = sumMatrix(X, R2, n, 1); // X(k+1) = X(k) + s*V
      
      free(R2);
      R2 = multiplyMatrix(R1, 1, 1, Z, 1, n);  //s*Z
      free(R1); free(R);
      R1 = copyMatrix(R, n, 1); //R1 = r
      R = subtractMatrix(R1, R2, n, 1); // r = r - sz
      
      free(R2);
      R2 = multiplyMatrix(R, 1, n, R, n, 1); //aux1 =rT*r
      
      Y = multiplyMatrix(M, n, n, R, n, 1); // Y = M^(-1) * r
      
      // printf("R2 %0.8f iteration:%d \n", *R2, it);
      fprintf(fp, "# iter %d: %.15g\n",  it, *R2);

      if (*R2 < eps) {
        double r = calculateNorm(A,B,Xn,n,&timeNorm);
        
        fprintf(fp, "# Residuo: %.15g \n", r);
        fprintf(fp, "# Tempo PC: %.15g sec \n", (timePC / 1000));
        fprintf(fp, "# Tempo iter: %.15g sec \n", (itTotal/it) / 1000);
        fprintf(fp, "# Tempo residuo: %.15g sec \n", timeNorm/1000);
        fprintf(fp, "# \n");
        fprintf(fp,"%d\n", n);
        printMat(Xn,1,n,fp);
         return Xn; // Saída com  sol  =  x{k+l )
      }
      
      R2 = multiplyMatrix(Y, 1, n, R, n, 1); //aux1 =yT*r
      
      m = *R2/aux; // m = aux1/aux;
      aux = *R2; // aux = aux1
      
      *R2 = m;  //Puting the value of m in an array to peform an operation with
      free(R1); //matrices
      R1 = multiplyMatrix(R2, 1, 1, V, 1, n); // m * V
      free(V);
      V = sumMatrix(Y, R1, n, 1); // V = y + (m * V)
      
      free(X);
      X = copyMatrix(Xn, 1, n); // Prepare for next iteration X(k) = X(k+1)
      free(Xn); free(Z); free(R2);
      itTotal = itTotal + (timestamp() - timeIt);
  }
    /*******************************************************************/
    
    fprintf(fp, "\nErro! Sistema não converge!\n");
    fprintf(stderr, "Erro! Sistema não converge!\n");   
    exit(1);
}