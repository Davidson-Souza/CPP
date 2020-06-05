/**
 * O bloco é uma das entidades básicas da blockchain, ele é formado pela união do cabeçálho, que é
 * formado por uma árvore do tipo Merke, o hash do bloco anterior, timestamp e número de trasações.
 * Transações são as células usadas para armazenar os dados no bloco.
 * 
 * ┌────────────┐
 * │    Head    │   Head: Cabeçaho do bloco
 * |     Tx     │   Tx: Transação individual
 * |     Tx     │   Hash: Assinatura do bloco
 * |     Tx     │
 * |    Hash    │
 * └────────────┘
 */
#ifndef TRANSACTION
#define TRANSACTION
#define MAX_SIZE 100
#define TARGET_NUM 123234345
#define MAX_DATA_SIZE 10000
#define MAX_HEADER_SIZE 1000
#include "transaction.cpp"
#include "mempool.cpp"
#include <time.h>
#include <stdlib.h>
class Block
{
    private:
        int txCount;
        char *previusHash;
        time_t timestamp;
        char *proof;
        unsigned long nonce;
        Transaction txVector[MAX_SIZE];
        char *merkleTop;
    public:
        Block(char *previusHash);
        int getTxCount();
        Transaction getTxByIndex(int index);
        char *getMerkleTop();
        void getRawHeader(char *header);
        void getRawData(char *buffer);
        void mining(Mempool &currentMempool,void (*callback)(void));   // Após minerado, chame a blockchain novamente
};

#endif