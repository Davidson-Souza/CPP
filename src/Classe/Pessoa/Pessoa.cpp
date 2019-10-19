//======================  Arquivos header's  ====================================
  #include "Pessoa.h"
  #include <iostream>
//======================      Namespaces     ====================================
  using namespace std;
//======================   Construtores      ====================================
// Construtor padrão
Pessoa::Pessoa(){
    this->idade     = 0;
    this->id        = 0;
    this->sexo      = false;
    this->usaOculos = false;
}
// Construtor de cópia
Pessoa::Pessoa(Pessoa &other){
    this->idade     = other.getIdade();
    this->id        = other.getId();
    this->sexo      = other.getSexo();
    this->usaOculos = other.getUsaOculos();
}

//======================   Métodos getter's  ====================================
int Pessoa::getId(){
    return this->id;
}

int Pessoa::getIdade(){
    return this->idade;
}

bool Pessoa::getSexo(){
    return this->sexo;
}

bool Pessoa::getUsaOculos(){
    return this->usaOculos;
}
//=======================  Métodos setter's  =====================================
void Pessoa::setId(int id){
    this->id = id;
}

void Pessoa::setIdade(int idade){
    this->idade = idade;
}

void Pessoa::setSexo(bool sexo){
    this->sexo = sexo;
}

void Pessoa::setUsaOculos(bool usaOculos){
    this->usaOculos = usaOculos;
}
//=======================  Métodos adicionais  ==================================
// Método que copia os dados de um outro produdo para sí mesmo
void Pessoa::copy(Pessoa &other){
    this->id        = other.getId();
    this->idade     = other.getIdade();
    this->sexo      = other.getSexo();
    this->usaOculos = other.getUsaOculos();
}
//========================  Fim do arquivo  =====================================