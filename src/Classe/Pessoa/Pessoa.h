/**
 *  Classe produto
 *  @Author: Davidson
 *  @Data: Oct, 2019
*/
//=========================  Definições globais  ===============================
#ifndef PESSOA
#define PESSOA
//=========================  Criação da classe   ===============================
class Pessoa{
    private:                                        // Atributos privados da classe
        int id;                                     // Id único da pessoa no sistema
        int idade;                                  // Idade da pessoa
        bool sexo;                                  // Sexo da pessoa, true = homem, false = mulher
        bool usaOculos;                             // Diz se a pessoa usa óculos, true = sim, false = não
    public:                                         // Métodos públicos
        Pessoa();                                   // Construtor
        Pessoa(Pessoa &other);                      // Construtor de cópia
        
        // Métodos setters
        int getId();                                // Recupera o Id da Pessoa
        int getIdade();                             // Recupera a idade da pessoa
        bool getSexo();                             // Recupera o sexo da pessoa
        bool getUsaOculos();                        // Recupera a informação de se a pessoa usa óculos ou não
        
        // Métodos getters
        void setId(int id);                         // Muda o ida da pessoa
        void setIdade(int idade);                   // Muda a idade da pessoa
        void setSexo(bool sexo);                    // Muda o sexo da pessoa
        void setUsaOculos(bool usaOculos);          // Muda a informação de se ela usa ou não óculos
        
        // Outros métodos
        void copy(Pessoa &other);                   // Método para copiar os dados de outra pessoa para este

};                                                  // Fim da declaração da classe

#endif                                              // Fim do arquivo