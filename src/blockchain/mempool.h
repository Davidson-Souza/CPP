/**
 * O mempool nada mais é que uma lista com todas as transações ainda não confirmadas.
 */
#ifndef MEMPOOL
#define MEMPOOL
#include "transaction.cpp"
#define MAX_MEMPOOL_SIZE 100
class Mempool
{
    private:
        int txCount;
        Transaction txList[MAX_MEMPOOL_SIZE];
    public:
        Mempool();
        int addTx(Transaction tx);        // Retorna o id
        int removeTxByIndex();
        int getTxCount();
        Transaction getTxById(int id);
        Transaction retrieveTxById(int id);
        
};
#endif