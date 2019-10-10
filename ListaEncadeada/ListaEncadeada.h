/**
 * Lista encadeada
 * A estrutura lista encadeada é mais rápida para a inserção, se comparada com a lista contígua.
 * Ela consiste em um conjuto de itens alocados de maineira independente na memória, onde cada um 
 * contém o endereço do seu sucessor. As estruturas que contém o ponteiro para o próximo e o dado em sí
 * é chamado de nó.
 * Um nó é uma classe que contém um ponteiro e um dado. O ponteiro aponta para o próximo item.
 * A lista é constituída de um header, que contém o endereço do primeiro nó. E um contador de elementos.
 *            Estrutura da lista:                    Estrutura do nó:
 *  +======================================+  +================================+
 *  * Quant                                *  * Pointer                        *
 *  * Header                               *  * Data                           *
 *  +======================================+  +================================+ 
 * @Author: Derik
 * @Data: Oct, 2019
 * 
*/  
//=================================  Definições globais  ===================================
  #ifndef LISTA                                             // O nome LISTA já foi definida?
  #define LISTA                                             // Se não, defina
//=================================  Arquivos externos  ===================================
  #include <iostream>
  #include "No.h"
//=================================  Assinatura das funções ===============================
class ListaEncadeada{                                       // Classe que implementa o objeto lista encadeada
private:                                                    // Atributos privados da classe
    int quant;                                              // Contador que mostrará quantos itens ela tem
    No *header;                                             // Endereço do primeiro nó

public:                                                     // Métodos públicos da estrutura
    
    ListaEncadeada();                                       // Construtor

    void remove(int index);                                 // Remove o index-ével elemento
    void remove();                                          // Método que remove o primeiro item
    void insert(int element);                               // Método que insere algo na lista
    void show();                                            // Método para mostrar os itens da lista
};                                                          // Fim ListaEncadeada
#endif                                                      // Fim se