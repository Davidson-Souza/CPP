#ifndef MEMPOOL_H
#define MEMPOOL_H
#include "mempool.h"
Mempool::Mempool()
{
    this->txCount = 0;
}
int Mempool::addTx(Transaction tx)
{
    this->txList[this->txCount] = tx;
    this->txCount++;
}
int Mempool::getTxCount()
{
    return this->txCount;
}
Transaction Mempool::getTxById(int id)
{
    return this->txList[id];
}
Transaction Mempool::retrieveTxById(int id)
{
    if(this->txCount > 0)
    {
        this->txCount--;
    }
    return this->txList[id];
}
#endif