#include "blockchain.h"
#include <stdio.h>

BlockChain::BlockChain(int blocksPerPage, int difficulty)
{
    this->difficulty = difficulty;
    this->mempool = Mempool();
    this->blkCount = 0;
    this->page = 0;
    this->blocksPerPage = blocksPerPage;
}
void BlockChain::createGenesisBlock()
{
    this->blks[0] = Block(0, 3);
    Mempool m1 = Mempool();
    Transaction tx = Transaction("Olá mundo!");
    m1.addTx(tx);
    this->blks[0].setPreviusHash("0");
    this->blks[0].mining(m1);
}
int BlockChain::newTx(char *data)
{
    Transaction tx = Transaction(data);
    this->mempool.addTx(tx);
}
void BlockChain::saveToDisk()
{
    FILE *file = fopen("blk","a");
    Block block;
    for (register unsigned int i = 0; i<this->blkCount; i++)
    {
        fprintf(file, "Height:%d Data: %s Hash: %s Merkle:%s TxCount:%d\n",this->blks[i].getHeight(), this->blks[i].getRawData(), this->blks[i].getProof(), this->blks[i].getMerkleTop(), this->blks[i].getTxCount());
    }
    this->blks[0] = this->blks[this->blkCount];
    this->blkCount = 0;
    fclose(file);   
    this->page++;
}

int BlockChain::newBlock()
{
    this->blkCount++;
    this->blks[this->blkCount] = Block(this->page*this->blocksPerPage + this->blkCount, this->difficulty);
    char buffer[32];
    strcpy(buffer, this->blks[blkCount - 1].getProof());
    this->blks[this->blkCount].setPreviusHash("buffer");
    this->blks[this->blkCount].mining(this->mempool);
}

int BlockChain::runChain()
{
    createGenesisBlock();
    //printf("Genesis Block Found: %s\n", this->blks[blkCount].getProof());
    this->isRunning = 1;
    this->newBlock();
    this->newBlock();
    this->newBlock();
    this->newBlock();

    for(;;)
    {
        this->newBlock();
        //printf("New block founded!: %s\n", this->blks[blkCount - 1].getProof());
        if(this->blkCount == this->blocksPerPage)
            this->saveToDisk();
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
