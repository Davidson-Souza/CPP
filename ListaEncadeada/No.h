/**
 * Nó para a lista encadeada.
 * O nó será a estrutura responsável por armazenar o dado e um ponteiro para o próximo nó.
 * A junção virtual de todos estes nós, constrituirão a lista encadeada
 * @Author: Derik
 * @Data: Oct, 2019
*/

class No{                           // Classe que implementa o objeto nó
    private:                        // Atributos privados da classe
        int data;                   // Dado armazenado no nó
        No *next;                   // Ponteiro para o próximo nó
    public:                         // Métodos públicos da classe
        No();                       // Construtor do nó
        void setData(int data);     // Muda o dado armazenado nele
        void setNext(No *next);     // Muda o ponteiro para o próximo dado

        int getData();              // Recupera o dado armazenado no nó
        No *getNext();              // recupera o ponteiro para o próximo item
};                                  // Fim nó