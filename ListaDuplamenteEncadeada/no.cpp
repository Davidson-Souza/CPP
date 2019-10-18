/**
 * Arquivo com a implemetação dos métodos do arquivo "no.h"
 * @Author: Derik
 * @Data: Oct, 2019
 * @License: MIT
*/
//=========================  arquivos header  =====================================
  #include <iostream>
  #include "no.h"
//=========================  Declaração de namespaces  ============================
using namespace std;

//=========================  Construtores  ========================================
Node::Node(){
    this->anterior = NULL;
    this->proximo  = NULL;
    this->dado     = ' ';
}
Node::Node(Node &node){
    this->anterior = node.getAnterior();
    this->dado     = node.getData();
    this->proximo  = node.getProximo();
}
//=========================  Setter's  =============================================
void Node::setData(char data){
    this->dado = data;
}
void Node::setAnterior(Node *anterior){
    this->anterior = anterior;
}
void Node::setProximo(Node *proximo){
    this->proximo = proximo;
}
//=========================  Getter's  =============================================
char Node::getData(){
    return this->dado;
}
Node *Node::getAnterior(){
    return this->anterior;
}
Node *Node::getProximo(){
    return this->proximo;
}
//-----------------------------------------------------------------------------------