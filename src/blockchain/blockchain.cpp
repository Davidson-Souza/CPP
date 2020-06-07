#include "blockchain.h"
#include <stdio.h>

BlockChain::BlockChain()
{
    this->mempool = Mempool();
    this->blkCount = 0;
}
void BlockChain::createGenesisBlock()
{
    this->blks[0] = Block(0, 3);
    Mempool m1 = Mempool();
    Transaction tx = Transaction("Olá mundo!");
    m1.addTx(tx);
    this->blks[0].setPreviusHash("0");
    this->blks[0].mining(m1);
    this->blkCount++;
}
int BlockChain::newTx(char *data)
{
    Transaction tx = Transaction(data);
    this->mempool.addTx(tx);
}

int BlockChain::newBlock()
{
    this->blks[this->blkCount] = Block(this->blkCount, 5);
    char buffer[32];
    strcpy(buffer, this->blks[blkCount - 1].getProof());
    this->blks[this->blkCount].setPreviusHash(buffer);
    this->blks[this->blkCount].mining(this->mempool);
    return this->blkCount++;
}

int BlockChain::runChain()
{
    createGenesisBlock();
    printf("Genesis Block Found: %s\n", this->blks[blkCount - 1].getProof());
    this->isRunning = 1;
    for(;;)
    {
       this->newBlock();
       printf("New block founded!: %s\n", this->blks[blkCount - 1].getProof());
    }
}

int BlockChain::getNumBlk()
{
    return this->blkCount;
}

Mempool BlockChain::getCurrentMempool()
{
    return this->mempool;
}
