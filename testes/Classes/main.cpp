#include "main.h"
int main(){
    Pessoa Joao, Cleide, Claudo;
    Joao.setId(1);
    Joao.setIdade(10);
    Joao.setSexo(true);
    Joao.setUsaOculos(false);

    Joao.copy(Joao);
    std::cout << Cleide.getId()  << std::endl;
    std::cout << Joao.getIdade() << std::endl;
    

    Produto cadeira, ventilador, amplificador;
    cadeira.fill();
    cadeira.setEstoque(10);
    cadeira.show();

    return 0;
}