/**
 * Arquivo que implementa os métodos lista encadeada
*/
//=================================  Arquivos externos  ===================================
#include "ListaEncadeada.h"
#include <iostream>
//=================================       Métodos       ===================================
ListaEncadeada::ListaEncadeada(){
    this->quant = 0;
    this->header = NULL;
}

void ListaEncadeada::insert(int element){
    No *aux = new No;
    aux->setData(element);
    aux->setNext(this->header);
    this->header = aux;
    this->quant ++;
}

void ListaEncadeada::show(){
    No *next = this->header;
    for (int i = 0; i<this->quant; i++){
        std::cout << next->getData() << std::endl;
        next = next->getNext();
    }
}

void ListaEncadeada::remove(){
    this->header = this->header->getNext();
    this->quant --;
}

void ListaEncadeada::remove(int index){
    if (index > this->quant){ return; std::cout << "Index inexistente!"; }
    No *prox = this->header, *anterior;

    for (int i = 1; i<=index; i++){
        if (i < index){ prox = prox->getNext(); }
        else{ anterior = prox; prox = prox->getNext();}
    }
    std::cout << anterior->getData()<<" " << prox->getNext()<<std::endl<<std::endl;
    anterior->setNext(prox->getNext());
    quant--;
}