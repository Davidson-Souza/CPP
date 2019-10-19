#include "Produto.h"
Produto::Produto(){
    this->codigo = 0;
}
Produto::Produto(Produto &outro){
    this->codigo = outro.codigo;
}


int Produto::getCodigo(){
    return this->codigo;
}
float Produto::getCusto(){
    return this->custo;
}
float Produto::getPreco(){
    return this->preco;
}
int Produto::getEstoque(){
    return this->estoque;
}


void Produto::setCodigo(int codigo){
    this->codigo = codigo;
}
void Produto::setCusto(float custo){
    this->custo = custo;
}
void Produto::setPreco(float preco){
    this->preco = preco;
}
void Produto::setEstoque(int estoque){
    this->estoque = estoque;
}


void Produto::fill(){
    std::cout << "Entre com o id do produto: ";
    std::cin  >> this->codigo;
    std::cout << "Entre com o estoque do produto: ";
    std::cin  >> this->estoque;
    std::cout << "Entre com o valor do produto: ";
    std::cin  >> this->preco;
    std::cout << "Entre com o custo do produto: ";
    std::cin  >> this->custo;
}

void Produto::show(){
    std::cout << "================  Mostrando um produto  ======================" << std::endl;
    std::cout << "Id: "      << this->codigo  << std::endl;
    std::cout << "Estoque: " << this->estoque << std::endl;
    std::cout << "Valor: "   << this->preco   << std::endl;
    std::cout << "Custo: "   << this->custo   << std::endl;
    std::cout << "===============================================================";
}