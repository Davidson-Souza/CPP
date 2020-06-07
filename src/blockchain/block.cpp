#ifndef BLOCK_CPP
#define BLOCK_CPP
#include "block.h"
#include "utilities/merkle.cpp"
#include <string>
#include <unistd.h>
#define zeroHash "0000000000000000000000"
Block::Block(int height, int difficulty)
{
    this->txCount = 0;
    this->height = height;
    this->difficulty = difficulty;
    this->merkleTop = "";
    this->proof = "";
    this->nonce = 0;
    this->timestamp = time(NULL);
}
void Block::setPreviusHash(char prevHash[MAX_BUFFER_SIZE])
{
    this->previusHash = prevHash;
}

Block::Block()
{
    this->txCount = 0;
    this->height = 0;
    this->proof = "";
    this->difficulty = 0;
    this->merkleTop = (char *) "";
    this->previusHash = (char *) "";
    this->nonce = 0;
    this->timestamp = time(NULL);
}


void Block::mining(Mempool &currentMempool)
{
    this->txCount = currentMempool.getTxCount() > MAX_SIZE ? MAX_SIZE : currentMempool.getTxCount();
    char dest[100];
    for (unsigned register int i = 0; i < this->txCount; i++)
    {
        this->txVector[i] = currentMempool.pop();
        this->txVector[i].getRawData(dest);
        printf("Transaction #%d: %s\n", i, dest);
    }
    
    char *rawData = new char[MAX_BUFFER_SIZE], *hash = new char[100], *_rawData = new char[MAX_BUFFER_SIZE];
;
    if(txCount > 0)
    {
        this->merkleTop = createMerkleTree(this->txVector, this->txCount);
        rawData = this->getRawData();
    }
    else
    {
        strcpy(_rawData, "");
    }
    strcat(_rawData, this->getRawHeader());
    int hInt;
    do
    {
        sprintf(_rawData, "%s%d", rawData, nonce);
        bytes2md5(_rawData, 100, hash);
        nonce++;
    }
    while(strncmp(hash, zeroHash, this->difficulty) != 0);
    proof = hash;
}
// 16:34

char *Block::getRawData()
{
    char *rawData = new char [MAX_DATA_SIZE];
    for (unsigned register int i = 0; i < this->txCount; i++)
    {
        char txData[MAX_BUFFER_SIZE];
        this->txVector[i].getRawData(txData);
        sprintf(rawData, "%s", txData);
    }
    return rawData;
}
char *Block::getRawHeader()
{
    char *blockHeader = new char [MAX_HEADER_SIZE];
    sprintf(blockHeader, "%s%s%d%d%d", this->previusHash,this->merkleTop, this->timestamp, this->txCount, this->height);
    return blockHeader;
}

int Block::getTxCount()
{
    return this->txCount;
}
Transaction Block::getTxByIndex(int index)
{
    return this->txVector[index];
}
char *Block::getMerkleTop()
{
    return this->merkleTop;
}
char *Block::getProof()
{
    return this->proof;
}
int Block::getHeight()
{
    return this->height;
}

#endif