/**
 * Algoritmo extendido de euclides para fatoração de números e encontrar o Máximo
 * divisor comum.
 * @Author: Derik
 * @Data: Sept, 2019
 */
//======================  Bibliotecas usadas  ===============================
#ifndef MDC
#define MDC
#include "main.h"

// Namespace global
using namespace teoriaDosNumeros;

//======================  Funções usadas  ==================================
// Função que calcula os restos
mdc::mdc(int a, int b){
    this->a = a;
    this->b = b;
    this->mdcResult = -1;
}
void mdc::calcula(){
    restos();
    quocientes();
    calc_x();
    calc_y();
}
void mdc::restos(){
    int *res = new int [10];
    int i = 0;

    res[0] = this->a;
    res[1] = this->b;
    
    while (res[i+1] != 0)
    {
        res[i+2] = res[i] % res[i+1];
        i++;
    }
    this->restosResult = res;
    this->mdcResult = res[i];
}

// Função que calcula os quocientes
void mdc::quocientes(){
    int *q = new int[10];
    int i = 0;

    while (this->restosResult[i+1] != 0)
    {
        q[i] = (int) this->restosResult[i]/this->restosResult[i+1];
        i++;
    }
    this->quocientesV = q;
}
/*
    No algoritmo de Euclides extendido, podemos, além de calcular o MDC, ainda calcular os fatores, 
    X e Y, taix que o MDC D seja igual à X*A + Y*B.
*/

// Função que calcula o x do algoritmo de Euclides
// Fórmula: X_n+2 = x_n - q_n+2 * x_n+1
void mdc::calc_x(){
    int *x = new int[10];
    int i = 0;
    x[0] = 1;
    x[1] = 0;
    while (this->restosResult[i+2] != 0){
        x[i + 2] = x[i] - this->quocientesV[i] * x[i + 1];
        i ++;
    }
    this->x = x;
}

int mdc::getMdcResult(){
    return this->mdcResult;
}

// Função que calcula o y do algoritmo de Euclides
// Fórmula: Y_n+2 = Y_n - q_n+2 * Y_n+1
void mdc::calc_y(){
    int *y = new int[10];
    int i = 0;
    y[0] = 0;
    y[1] = 1;
    while (this->restosResult[i+2] != 0){
        y[i + 2] = y[i] - this->quocientesV[i] * y[i + 1];
        i ++;
    }
    this->y = y;
}
#endif