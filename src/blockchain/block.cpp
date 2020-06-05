#include "block.h"
#include "utilities/merkle.cpp"
Block::Block(char *previusHash)
{
    this->txCount = 0;
    this->merkleTop = "";
    this->previusHash = previusHash;
    this->nonce = 0;
    this->timestamp = time(NULL);
}
void Block::mining(Mempool &currentMempool,void (*callback)(void))
{
    this->txCount = currentMempool.getTxCount() > MAX_SIZE ? MAX_SIZE : currentMempool.getTxCount();
    for (register int i = 0; i < this->txCount; i++)
        this->txVector[i] = currentMempool.getTxById(i);
    
    char *rawData, *hash, *rawHeader;
    this->getRawData(rawData);
    this->merkleTop = createMerkleTree()
    long int i;
    do
    {
        this->getRawHeader(rawHeader);
        strcat(rawData, rawHeader);
        bytes2md5(rawData, 32, hash);
        i = strtol(hash, &hash, 16);
    }
    while(i<TARGET_NUM);
    this->proof = hash;
    callback();
}

void Block::getRawData(char *buffer)
{
    char rawData[MAX_DATA_SIZE];
    for (register int i = 0; i < this->txCount; i++)
    {
        char *txData;
        this->txVector[i].getRawData(txData);
        sprintf(rawData, "%s", txData);
    }
    buffer = rawData;
}
void Block::getRawHeader(char *header)
{
    char blockHeader[MAX_HEADER_SIZE];
    sprintf(blockHeader, "%s%d%d%d", this->previusHash, this->timestamp, this->txCount, this->nonce);
    header = blockHeader;
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

