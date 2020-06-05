/**
 * Transação é a menor unidade em uma blockchain, é nela onde serão adicionados os dados úteis. O bloco
 * será uma junção das mesmas.
 * Nesse caso usarei uma estrutura arbitrária para armazenar textos simples.
 * ┌────────────┐       Informações:
 * │  Timelock  │                   timelock: o horário em formato Unix de quando a transação foi criada
 * │    Hash    │                   Hash: A hash da transação
 * │    Data    │                   Data: Os dados armazenados na transação
 * └────────────┘
 */
#include <time.h>
#define HASH_LENGTH 32

class Transaction
{
    private:
        time_t timeLock;
        char hash[100];
        char *data;
    public: 
        Transaction(char *data);

        // Apenas métodos de get, pois uma vez criada a transação ela é irreversível
        time_t getTimeLock();
        char *getHash();
        char *getData();
        void getRawData(char *data); // Retorna os dados todos juntos em uma string única

};