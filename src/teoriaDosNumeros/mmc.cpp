/**
 * Calcula o mmc, com base no MDC e teoremas relacionados ao mesmo 
 * @Author: Derik
 * @Data: Sept, 2019
 */
//=================================================================================
  // Incluindo a biblioteca geral do sistema
  #include "main.h"
  // Declarando o uso do namespace global
  using namespace teoriaDosNumeros;
//=================================================================================

// Método que calcula o mmc
mmc::mmc(int a, int b){
    mdc d(a,b);
    d.calcula();
    this->mmcResult = (a*b)/d.getMdcResult();
}

mmc::mmc(mdc d){
    d.calcula();
    this->mmcResult = (a*b)/d.getMdcResult();    
}
//=================================================================================
/* Métodos para controlar o encapsulamento das classes */
int mmc::getA(){
    return this->a;
}

int mmc::getB(){
    return this->b;
}

int mmc::getMmcResult(){
    return this->mmcResult;
}

void mmc::setA(int a){
    this->a = a;
}

void mmc::setB(int b){
    this->b = b;
}