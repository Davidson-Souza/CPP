/**
 * Implementação do nó, para a classe lista duplamente encadeada.
 * Essa classe, assim como a encontrada na lista encadeada é o coração da lista encadeada,
 * a junção virtual das mesmas fomam a estrutura de dados propriamente ditas.
 * A diferença se dá em detrimento da adição de um campo extra, resposável por apontar para o 
 * nó anterior
 * 
 *  +--------------------+
 *  + A   |  D   |  P    +  ANTE  = Elemento anterior na lista 
 *  + N   |  A   |  R    +  Dados = Dados úteis armazenados no nodo, pode ser de qualquer tipo
 *  + T   |  D   |  Ó    +  Próx  = Próximo elemento da lista
 *  + E   |  O   |  X    + 
 *  +--------------------+
 * Esta é a representação "gráfica" do nodo.
 * Obs: O primeiro elemento da lista (0) deve ter o seu ponteiro ANTE setado para NULL.
 * Obs: O último elemento da lista (n) deve ter o seu ponteiro PRÓX setado para NULL
 * @Author: Derik
 * @Data: Oct, 2019
 * @License: MIT
*/  
//=======================  Declaração da classe Nó  ========================================
class Node{
    private:                                // Elementos privados, incacessíveis fora da classe
        Node *anterior;                     // Ponteiro para o item anterior na lista
        char  dado;                         // Dado que será armazenado
        Node *proximo;                      // Ponteiro para o próximo item da lista
    public:                                 // Elementos públicos da classe, acessíveis em qualquer lugar
        Node();                             // Construtor
        Node(Node &node);                   // Construtor de cópia
                                            // Métodos getter's
        Node *getAnterior();                // Recupera o valor de anterior
        char  getData();                    // Recupera o valor de dado;
        Node *getProximo();                 // Recupera o valor de proximo
                                            // Métodos setter's
        void setAnterior(Node *anterior);   // Muda o valor de anterior
        void setData(char dado);            // Muda o valor de dado
        void setProximo(Node *proximo);     // Muda o valor de proximo
};