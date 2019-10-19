/**
 * Algoritmo extendido de euclides para fatoração de números e encontrar o Máximo
 * divisor comum.
 * @Author: Derik
 * @Data: Sept, 2019
 */
//======================  Bibliotecas usadas  ===============================
#ifndef MDC
#define MDC
#include <iostream>

//======================  Assinaturas das funções  ===============================
int *restos(int a, int b, int &quant);
int *quocientes(int *restosVet);
int *calc_x(int *restosVec, int *quocientesVect);
int *calc_y(int *restosVec, int *quocientesVect);

//======================  Variaveis globais  ===============================
  int numElems = 0;
//======================  Funções usadas  ==================================
int mdc(int a, int b){
    int quant;
    int *res = restos(a, b, quant);
    int *quo = quocientes(res);
    int *x   = calc_x(res, quo);
    int *y   = calc_y(res, quo);
    return res[quant];
};
// Função que calcula os restos
int *restos(int a, int b, int &quant){
    int *res = new int [10];
    int i = 0;

    res[0] = a;
    res[1] = b;
    
    while (res[i+1] != 0)
    {
        res[i+2] = res[i] % res[i+1];
        i++;
    }
    quant = i;
    return res;
}

// Função que calcula os quocientes
int *quocientes(int *restosVet){
    int *q = new int[10];
    int i = 0;

    while (restosVet[i+1] != 0)
    {
        q[i] = (int) restosVet[i]/restosVet[i+1];
        i++;
    }
    return q ;
}
/*
    No algoritmo de Euclides extendido, podemos, além de calcular o MDC, ainda calcular os fatores, 
    X e Y, taix que o MDC D seja igual à X*A + Y*B.
*/

// Função que calcula o x do algoritmo de Euclides
// Fórmula: X_n+2 = x_n - q_n+2 * x_n+1
int *calc_x(int *restosVec, int *quocientesVect){
    int *x = new int[10];
    int i = 0;
    x[0] = 1;
    x[1] = 0;
    while (restosVec[i+2] != 0){
        x[i + 2] = x[i] - quocientesVect[i] * x[i + 1];
        i ++;
    }
    return x;
}



// Função que calcula o y do algoritmo de Euclides
// Fórmula: Y_n+2 = Y_n - q_n+2 * Y_n+1
int *calc_y(int *restosVec, int *quocientesVect){
    int *y = new int[10];
    int i = 0;
    y[0] = 0;
    y[1] = 1;
    while (restosVec[i+2] != 0){
        y[i + 2] = y[i] - quocientesVect[i] * y[i + 1];
        i ++;
    }
    return y;
}
#endif