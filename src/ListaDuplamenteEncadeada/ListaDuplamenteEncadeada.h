/**
 *                                  Lista duplemente encadeada.
 *  Como o nome sugere, a lista duplamente encadeada é uma "evolução" da lista encadeada.
 *  As mudanças que mais se destacam estão ligadas ao Nó (nodo, node), que agora possúi, alem do
 *  endereço de seu sucessor, ele possui também o endereço do seu antecessor. Com isso podemos, por 
 *  exemplo, percorrer a lista de tás para frente.
 *             Estrutura da lista:                    Estrutura do nó:
 *  +======================================+  +================================+
 *  * Quant                                *  * Prox:                          *
 *  * Header                               *  * Ante:                          *
 *  *                ------                *  * Data:                          *
 *  +======================================+  +================================+
 *  @Author: Derik
 *  @Data: Oct, 2019
 *  @License: MIT 
*/
//==========================  Bibliotecas externas  ======================================
  #include "no.h"                           // Classe Node
//==========================  Declaração da classe  ======================================
class ListaDuplamenteEncadeada
{
private:
    int quant;
    Node *header;
public:
    ListaDuplamenteEncadeada();

    void show();
    void insert(char element);              // Insere um elemento na lista
    Node *getElemento(int index);           // Retorna um elemento da lista
};

//=========================================================================================