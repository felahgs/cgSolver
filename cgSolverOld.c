#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "geraMat.h"

int main (int argc, char *argv[])
{
    int n, k, i, a;
    double w, e = 1.0e-8;
    char *o;
    
    for (int j = 1; j < argc -1; j++) {
        a = j+1;
        if ( strcmp(argv[j], "-n") == 0 ) {
            
            n = atoi(argv[a]);
        }
        else if ( strcmp(argv[j], "-k") == 0 )  
        {
            k = atoi(argv[a]);
        }
        else if ( strcmp(argv[j], "-w") == 0 ) 
        {
            w = atof(argv[a]);
        }
        else if ( strcmp(argv[j], "-e") == 0 ) 
        {
            e = atof(argv[a]);
        }
        else if ( strcmp(argv[j], "-i") == 0 )  
        {
            i = atoi(argv[a]);
        }
        else if ( strcmp(argv[j], "-o") == 0 ) 
        {
            o = argv[a];
        }
    }
    
    srand(20182);
    
    if ( i <= 0 )
    {
        fprintf(stderr, "Erro! necessário definir o número máximo de iterações!"
        " O parametro \"-i\""
        " deve ser fornecido e ser maior ou igual a 10 \n");   
        exit(1);
    };
    
    if ( n < 10 )
    {
        fprintf(stderr, "Erro! Valor incorreto para a dimensão da matriz!"
        " A dimensão da matriz deve ser definida com parâmetro \"-n\""
        " e ser maior ou igual a 10 \n");   
        exit(1);
    };
    
    FILE *fp = fopen(o ,"w+");
    fprintf(fp, "# fgs12 Felipe Garcia de Souza\n");
    fprintf(fp, "# rym12 Rodrigo Yukio Misugi\n");
    fprintf(fp, "# \n");
    
    if(fp == NULL)
    {
      fprintf(stderr, "Erro! Diretorio ou nome de arquivo invalido!"
      "entre con um nome de diretorio de saída com o parâmetro \"-o\"\n");   
      exit(1);
    }
    
    if ( k <= 0 || k%2 == 0 )
    {
        fprintf(stderr, "Erro! Valor incorreto para o número de diagonais."
        " Entre com um valor em que -k seja maior que zero e ímpar\n");   
        exit(1);
    };
    
    double *matrixA, *matrixB, *matrixC, *b;

    matrixA = generateBandMatrix(n,k);
    matrixC = getDiagonal(matrixA, n);
    b = generateIndTerms(n,k);
    
    if (w == 0) {
        conjugateGradients(matrixA, b, n, i, e, fp);    
    }
    else if (w == 1) {
        preconditioningCg(matrixA, b, matrixC, n, i, e, fp);
    }
    else {
        fprintf(stderr, "Codigo de pre-condicionador incorreto ou ausente! "
        "Informe corretamente o pré condicionador usado com o argumento \"-w\""
        " 0: Sem pré-condicionador e -o 1: pré-condicionador de Jacobi\n");
    };
}

