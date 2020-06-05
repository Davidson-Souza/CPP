/**
 * O mempool nada mais é que uma lista com todas as transações ainda não confirmadas.
 */
#ifndef MEMPOOL
#define MEMPOOL
#include "transaction.cpp"
#define MAX_MEMPOOL_SIZE
class Mempool
{
    private:
        int txCount;
        Transaction txList[MAX_MEMPOOL_SIZE];
    public:
        Mempool();
        int addTx();        // Retorna o id
        int removeTx();
        int getTxCount();
        Transaction getTxById(int id);
        
};
#endif