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
#ifndef BLOCK
#define BLOCK
#define MAX_SIZE 100
#define TARGET_NUM 12
#define MAX_DATA_SIZE 10000
#define MAX_BUFFER_SIZE 1000
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
        int height;
        int difficulty;
        unsigned long nonce;
        Transaction txVector[MAX_SIZE];
        char *merkleTop;
    public:
        Block(int height, int difficulty);
        Block();
        int getTxCount();
        int getHeight();
        Transaction getTxByIndex(int index);
        char *getMerkleTop();
        char *getRawHeader();
        char *getRawData();
        char *getProof();
        void setPreviusHash(char prevHash[MAX_BUFFER_SIZE]);
        void mining(Mempool &currentMempool);   // Após minerado, chame a blockchain novamente
};

#endif