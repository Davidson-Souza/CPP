/**
 * Implementação dos métodos referentes à classe ListaContigua (ListaContigua.h).
 * @Author: Derik
 * @Data: Oct, 2019
*/

//=================================  Includes globais  =======================================
#include "ListaContigua.h"
#include <iostream>
//=================================  Métodos auxiliares  =====================================
/**
 * Algoritmo de troca de valores entre dua variáveis. Ele usa uma variável auxiar, e três 
 * permutações para alcaçar o objetivo
*/
void ListaContigua::change(char &a, char &b){
    char aux;                                               // Cria uma auxiliar 
    aux = a;                                                // Copia a para a auxiliar
    a = b;                                                  // Copia b para a
    b = aux;                                                // Copia aux (antigo a) para b
}                                                           // Fim change

//==================================== Construtor  ============================================
ListaContigua::ListaContigua(){
    this->quant = 0;
    this->tam = 10;
    this->vet = new char[this->tam];
}

ListaContigua::ListaContigua(int tam){
    this->tam = tam;
    this->quant = 0;
    this->vet = new char[this->tam];
}

//===================== Implementação dos métodos  =============================

// Método que mostra o conteúdo da lista
void ListaContigua::show(){
    for (int i = 0; i<tam; i++){        // Percorre por todos os elementos da lista
        if (i<this->quant)              // i é menor que quant?
            std::cout << this->vet[i];  // Se sim, mostre o conteúdo da lista em i
        else                            // Não?
            std::cout << '-';           // Então mostre um '-' para representar espaço vazio
    }
    std::cout << std::endl;             // Por fim, dê uma quebra de linha
}                                       // Final do método show


/**
 * Método que insere um item com o index implícito
 * @Params:
 * item: Item à ser inserido.
 */
void ListaContigua::insert(char item){
    this->shiftFront();     // Arreda todos os item para a frete
    this->vet[0] = item;    // Insere o item no indice 0
    this->quant++;          // Incrementa a variável contadora
}                           // Fim insere


/**
 * Método que insere um item com o index explicito
 * @Params:
 * item: Item à ser inserido.
 * index: índice onde o item será inserido
 */
void ListaContigua::insert(char item, int index){
    this->shiftFront(index);        // Arreda todos os elementos para frete à partir do index passado
    this->vet[index] = item;        // Insere o item no lugar passado como parâmetro
    this->quant++;                  // Incrementa a variável contadora
}                                   // Fim insere


/**
 * Método da bolha para ordenação de vetores:
 *  Corre o vetor até o índex máximo, e em cada rodada permuta os itens que forem maiores
 * que o seu suscessor.
*/

void ListaContigua::sort(){
    int ultimo = this->quant-1;
    while(ultimo >= 0){
        for (int i = 0; i<this->quant-1; i++){
            if (this->vet[i] > this->vet[i+1]){ change(this->vet[i], this->vet[i+1]); }
        }
        ultimo --;
    }
}

/**
 * Método que faz a busca binária por um item expecífico
 * @Params: 
 * item: Item à ser pesquisado
*/
int ListaContigua::search(char item){
    int meio = 0,                                           // Variável que guarda o indice do meio da sequência
    inicio = 0,                                             // Variável que guarda o indice do começo da sequência
    final = this->tam-1;                                    // Variável que guarda o indice do fianl da sequência

    while(inicio<=final){                                   // Enquanto início form menor ou igual à final
        meio = (inicio + final)/2;                          // Meio recebe final + inicio, dividio por 2
        if (this->vet[meio] == item){ return meio; }        // Se o item do índice meio, for o item procurado, retorne meio
        else if(item < vet[meio]  ){ final = meio - 1; }    // Se o item do indice meio, for maior que o item procurado, mova o final para o meio
        else{ inicio = meio+1; }                            // Se o item do indice meio, for menor que o item procurado, mova o começo para o meio
    }                                                       // Fim enquanto
    return -1;                                              // Caso não encontre o item, retorne -1
}                                                           // Fim busca

/**
 * Método que deleta o primeiro item da lista
*/
void ListaContigua::del(){
    shiftEnd();                                             // Move todos os elementos da lista para tŕas
    quant--;                                                // Decrementa a variável contadora
}
/**
 * Método que remove o n-ésimo item da lista
 * @Params:
 * index: índice do item à ser deletado
*/
void ListaContigua::del(int index){
    shiftEnd(index);                                        // Move os elementos para tás, à partido de index
    quant--;                                                // Decrementa a variável contadora
}                                                           // Fim del

/**
 * Método que move todos os elementos da lista para frente, à partir do primeiro
*/
void ListaContigua::shiftFront(){                   
    for (int i = quant; i>0; i--){                          // Percorre os itens da lista de forma crescente
        this->vet[i] = this->vet [i-1];                     // O elemento n recebe o elemento n-1 (seu antecessor)
    }                                                       // Fim para
}                                                           // Fim shiftFront
/**
 * Método que move todos os elementos da lista para frente, à partir de index
 * @Params:
 * index: à partir de onde os itens serão movidos
*/
void ListaContigua::shiftFront(int index){
    for (int i = quant; i>index; i--){                      // Percorre os itens da lista à partir da posição index de forma crescente
        this->vet[i] = this->vet [i-1];                     // O elemento n recebe o elemento n-1 (seu antecessor)
    }                                                       // Fim para
}                                                           // Fim shiftFront
/**
 * Método para mover os elementos da lista para trás, à partir do último
*/
void ListaContigua::shiftEnd(){
    for (int i = 0; i<quant; i++){                          // Percorre os itens da lista, à partir do último de forma decrescente
        this->vet[i] = this->vet [i+1];                     // O elemento n recebe o elemento n+1 (seu sucessor)
    }                                                       // Fim para
}                                                           // Fim shiftEnd

/**
 * Método para mover os elementos da lista para trás, à partir da posição passada por index
*/
void ListaContigua::shiftEnd(int index){
    for (int i = index; i<quant; i++){                      // Percorre os itens da lista, à partir de index de forma decrescente
        this->vet[i] = this->vet [i+1];                     // O elemento n recebe o elemento n-1 (seu antecessor)
    }                                                       // Fim para
}                                                           // Fim shiftFront

