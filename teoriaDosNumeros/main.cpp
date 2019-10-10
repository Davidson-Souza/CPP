/**
 * Programa principal para teste dos algoritmos de teoria dos números
 * @Author: Derik
 * @Data: Sept, 2019
 */
//==========================  Algoritmos usados  ========================
  #include "mdc.cpp"
  #include "mmc.cpp"
//==========================  Variáveis globais  ========================
  int *history;
//==========================  Assinatura das funções ====================
void mostra_opcoes();
int menu();
void callMmc(int a, int b);
void callMdc(int a, int b);

//==========================  Programa principal  =======================
int main(){
    comeco:
        int sel = menu();
        if (sel == -1){return 128; }
        if (sel == 3) {goto comeco; }
    int a,
        b;
    std::cout << "Entre com o valor de A: ";
    std::cin >> a;
    
    std::cout << "entre com o valor de B: ";
    std::cin >> b;

    if (sel == 2){ callMdc(a, b); }
    if (sel == 1){ callMmc(a, b); }
}   //End main

//==========================  Desenvolvimento das funções  ==============

/**
 * Mostra as opções de operações disponíveis, junto ao seu código
*/
void mostra_opcoes(){
    std::cout <<"1 - MMC\n2 - MDC\n3 - Help\n";
}

/**
 * Mostra o menu principal para o usuário
*/
int menu(){
    mostra_opcoes();
    std::cout << "Digite uma opção: ";
    int sel;
    std::cin >> sel;
    if (sel>3 || sel<1){ std::cout << "Opção inválida" << std::endl; return -1; }
    return sel;
}

/**
 * Chama a função que calcula o mmc
*/
void callMmc(int a, int b){
    std::cout << mmc(a, b)<< std::endl;
}

/**
 * Chama a função que calcula o mdc
*/
void callMdc(int a, int b){
    std::cout << mdc(a, b) << std::endl;
}
