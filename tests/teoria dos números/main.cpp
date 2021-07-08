#include "main.h"

int main(void){
    int a, b;
    std::cout << "Digite um inteiro A: ";
    std::cin >> a;
    std::cout << "Digite um inteiro B: ";
    std::cin >> b;

    teoriaDosNumeros::mdc mdc(a, b);
    mdc.calcula();
    teoriaDosNumeros::mmc mmc(a, b);

    std::cout << mdc.getMdcResult() << std::endl;
    std::cout << mmc.getMmcResult() << std::endl;
}