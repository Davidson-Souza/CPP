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
void Produto::setCodigo(int codigo){
    this->codigo = codigo;
}
