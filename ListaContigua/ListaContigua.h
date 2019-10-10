/**
 *=================================  Lista contígua  ======================================
 * Arquivo header de uma estrutura abstrata do tipo lista contígua
 * A lista contígua é um tipo especial de classe que contém à priore três membros base:
 * tam   - Um inteiro que conterá o tamanho máximo da lista.
 * quant - Um inteiro que conterá a quantidade de elementos que a lista possui.
 * vet   - Um ponteiro para o vetor que guardará os dados da lista propriamente ditos.
 * 
 * Representação:
 * 
 *  +────────────────────────────────────────────────────────────────────────────+
 *  + tam: n                                                                     +
 *  + quant: 0                                                                   +
 *  + -------------------------------------------------------------------------- +
 *  +      +─────────────────+                                                   +
 *  + vet: |  *  |  *  |  *  |                                                   +
 *  +      +─────────────────+                                                   +
 *  +────────────────────────────────────────────────────────────────────────────+
 * 
 * Ela também contempla alguns métodos públicos para que seja feito o controle e acesso à sua 
 * estrutura interna. Tal acesso é sempre indireto, feito por meio dos métodos apropriados.
 * @Author: Derik
 * @Data: Oct, 2019 
 */
//=+=======================  Definições globais  ===================================================
#ifndef LISTA                           
#define LISTA
//=========================  Assinaturas das funções  =============================================
class ListaContigua{
private:                                // Atributos privados
    //==============================  Atributos  ==================================================
    int tam;                            // Tamanho da lista
    int quant;                          // Quantidade de elementos inseridos na lista
    char *vet;                          // Ponteiro para o vetor de dados da lista
    //=====================  Métodos auxiliares internos  ==========================================
    void change(char &a, char &b);      // Método auxiliar para permutar os valores de duas variáveis
    void shiftEnd();                    // Método que move todos os elementos para trás
    void shiftFront();                  // Método que move todos os elementos para frente
    void shiftEnd(int index);           // Método que move todos os elementos, à partir de index para trás
    void shiftFront(int index);         // Método que move todos os elementos, à partir de index para frente
    //=============================================================================================
public:                                 // Métodos públicos
    ListaContigua(int tam);             // Construtor com o tamanho explícito
    ListaContigua();                    // Construtor com o tamanho implícito

    void sort();                        // Método para ordenar a lista
    void show();                        // Método para mostrar os elementos da lista

    void insert(char item);             // Método para inserir na lista com o index implícito (0)
    void insert(char item, int index);  // Método para inserir na lista com o index explícito

    void del();                         // Método para deletar da lista com o index implícito (0)
    void del(int index);                // Método para deletar da lista com o index explícito

    int search(char item);              // Busca binária na lista
    int searchBF(char item);            // Busca na lista via brute force (obsoleto e custoso)
};
#endif                                  // End ListaContigua