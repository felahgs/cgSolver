/**
 * @file cgSolver.c
 * @brief Programa principal para o calculo pelo metodo de Gradientes Conjugados.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "validateEntry.h"
#include "geraMat.h"

int main (int argc, char *argv[])

/***********************
* @brief serão verificados os argumentos do programa. Cada valor que procede
* um argumneto será armazenado e validado mais adiante
* 
 ***********************/
{
    int n = -1, k = 0, i = 0;
    double p = -1, e = 1.0e-8;
    double *matrixA, *matrixB, *matrixC, *b;
    char *o = "nil";
    FILE *fp;
    
    for ( int j = 1; j < (argc -1); j ++)
    {
       catchInt(argv[j], argv[j+1], "-n", &n);
       catchInt(argv[j], argv[j+1], "-k", &k);
       catchInt(argv[j], argv[j+1], "-i", &i);
       catchFloat(argv[j], argv[j+1], "-e", &e);
       catchFloat(argv[j], argv[j+1], "-p", &p);
        
        if ( strcmp(argv[j], "-o") == 0 ) 
        {
            o = argv[j+1];
        }
    };
    
    srand(20182);
    
    validateIterations(i);
    validateDimension(n);
    validateDiagonals(k);
    
    
    if( strcmp(o, "nil") == 0)
    {
      fprintf(stderr, "Erro! Diretório ou nome de arquivo invalido!"
      " Entre con um nome de diretório de saída com o parâmetro \"-o\"!\n");   
      exit(1);
    }
    else
    {
        fp = fopen(o ,"w");
        if(fp == NULL)
        {
            fprintf(stderr, "Erro ao criar arquivo!");
            exit(1);
        }
        
        fprintf(fp, "# fgs12 Felipe Garcia de Souza\n");
        fprintf(fp, "# \n");
    }

    matrixA = generateBandMatrix(n,k);
    matrixC = getDiagonal(matrixA, n);
    b = generateIndTerms(n,k);
    
    if (p == 0) {
        printf("Gradientes Conjugados Sem Precondicionadores\n");
        conjugateGradients(matrixA, b, n, i, e, fp);    
    }
    else if (p > 0 && p < 1) {
        printf("Gradientes Conjugados com Precondicionador de Jacobi\n");
        preconditioningCg(matrixA, b, matrixC, n, i, e, fp);
    }
    else {
        fprintf(stderr, "Codigo de pre-condicionador incorreto ou ausente! "
        "Informe corretamente o pré condicionador usado com o argumento \"-p\""
        " 0: Sem pré-condicionador; 0 < p < 1: pré-condicionador de Jacobi\n");
    };
    
}

