//====================  Arquivos usados  ===============================
  #include <iostream>
  #include "ListaDuplamenteEncadeada.h"
//====================  Construtor  ====================================
// Normal
ListaDuplamenteEncadeada::ListaDuplamenteEncadeada(/* args */){
  this->header = NULL;
  this->quant  = 0;
}
//=====================  Declaração dos métodos  =======================

void ListaDuplamenteEncadeada::insert(char item){
  Node *novo = new Node();
  novo->setData(item);
  novo->setProximo(header);
  if (header != NULL){ header->setAnterior(novo); };
  this->header = novo;
  this->quant ++;
}

void ListaDuplamenteEncadeada::show(){
  Node *prox = this->header;
  for (int i = 0; i<this->quant; i++){
    std::cout << prox->getData() << std::endl;
    prox = prox->getProximo();
  }
}

Node *ListaDuplamenteEncadeada::getElemento(int index){
  
  if(index > quant){ std::cout << "Index inexistente!"; }

  Node *prox = this->header;
  
  for (int i = 0; i<index-1; i++){
    prox = prox->getProximo();
  }
  
  return prox;
}