/**
 * @file validadeEntry.c
 * @brief Leitura e validação dos parâmetros de entrada
 */

#include "validateEntry.h"
#include <stdio.h>
#include <string.h>

/***********************
 * @brief Função que verifica o parametro de entrada.
 * @param param parametro da linha de comando 
 * @param next valor seguido do parametro na chamada para executar o programa
 * @param test string de teste para comparar o parametro
 * @num inteiro que recebera o valor convertidoas da matriz
 * 
 * Função que verifica o parametro de entrada. utilizando o argumento e o 
 * proximo valor da string de entrada. Caso as strings sejam iguais, é atribuido
 * a variavel passada como parametro o valor da seguido do parametro de entrada
 * testado
 ***********************/
void catchInt( char *param, char*next, char *test, int *num)
{
    if ( strcmp(param, test) == 0 ) 
    {
        *num = atoi(next);;
    }
}

/***********************
 * @brief Função que verifica o parametro de entrada.
 * @param param parametro da linha de comando 
 * @param next valor seguido do parametro na chamada para executar o programa
 * @param test string de teste para comparar o parametro
 * @num float que recebera o valor convertidoas da matriz
 * 
 * Função que verifica o parametro de entrada. utilizando o argumento e o 
 * proximo valor da string de entrada. Caso as strings sejam iguais, é atribuido
 * a variavel passada como parametro o valor da seguido do parametro de entrada
 * testado
 ***********************/
void catchFloat( char *param, char*next, char *test, double *num)
{
    if ( strcmp(param, test) == 0 ) 
    {
        *num = atof(next);;
    }
};

/***********************
* @brief Valida o parametro do numero de intereçãoes
* @i numero de interações 
 ***********************/
void validateIterations(int i)
{
    if ( i <= 0 )
{   
        printf("i = %d \n", i);
        fprintf(stderr, "Erro! necessário definir o número máximo de iterações!"
        " O parametro \"-i\""
        " deve ser fornecido e se maior ou igual a 10 \n");   
        exit(1);
    };
};

/***********************
* @brief Valida o parametro da dimensão da matriz
* @n dimensão da matriz/sistema
 ***********************/
void validateDimension(int n)
{
    if ( n < 10 )
    {
        fprintf(stderr, "Erro! Valor incorreto para a dimensão da matriz!"
        " A dimensão da matriz deve ser definida com parâmetro \"-n\""
        " e ser maior ou igual a 10 \n");   
        exit(1);
    };
};

/***********************
* @brief Valida o numero de diagonais da matriz
* @k diagonais da matriz
 ***********************/
void validateDiagonals(int k)
{
    if ( k <= 0 || k%2 == 0 )
    {
        fprintf(stderr, "Erro! Valor incorreto para o número de diagonais."
        " Entre com um valor em que -k seja maior que zero e ímpar!\n");   
        exit(1);
    };
};