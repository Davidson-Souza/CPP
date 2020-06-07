#include "../transaction.h"
#include "md5.c"
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_LEVELS 100
#define MAX_BUFFER_SIZE 10000

/**
 * Cria uma Hash à partir de um conjunto de transações t1 e t2, e o salva em dest.
 */
char *getTxPairHash(Transaction t1, Transaction t2)
{
    char buffer[MAX_BUFFER_SIZE], aux[MAX_BUFFER_SIZE];
    t1.getRawData(buffer);
    t2.getRawData(aux);
    strcat(buffer, aux);
    char *_buff = new char[100];
    bytes2md5(buffer, 32, _buff);
    return _buff;
}
/**
 *  Cria uma hash à partir de um par de outras hashs informadas por h1 e h2, e a salva em dest  
 */
char *getHashPairHash( char *h1, char *h2)
{
    char buffer[MAX_BUFFER_SIZE], *aux = new char[MAX_BUFFER_SIZE];
    strcat(buffer, h1);
    strcat(buffer, h2);
    bytes2md5(buffer, 32, aux);
    return aux;
}

char *getNextLayer(char **lastLayer, int txCount)
{
    char **_lastLayer;
    if (txCount % 2 == 1)
    {
        _lastLayer = new char*[txCount + 1];
        for (register unsigned int i = 0; i < txCount; i++)
            _lastLayer = lastLayer;
        _lastLayer[txCount] = lastLayer[txCount-1];
        txCount++;
    }
    else
    {
        _lastLayer = lastLayer;
    }
    char *_layer[txCount];

    for (register int i = 0; i<txCount/2; i++)
    {
        _layer[i] = getHashPairHash(_lastLayer[2*i], _lastLayer[(2*i)+1]);
    }
    if (txCount < 2)
       getNextLayer(_layer, txCount/2);
    else
        return _layer[0];
}

/**
 * Cria uma nova árvore usando a lista de transações disponíveis em txList. Também deve ser passado
 * o número de transações (txCount) e um buffer que receberá o topo da árvore.
 */
char *createMerkleTree(Transaction *txList, int txCount)
{
    /**
     * Toda árvore Merkle deve ter um número par de folhas
     */
    Transaction *_txList;
    if (txCount % 2 == 1)
    {
        _txList = new Transaction[txCount+1];
        for (register unsigned int i = 0; i < txCount; i++)
            _txList[i] = txList[i];
        _txList[txCount] = txList[txCount-1];
        txCount++;
    }
    else
    {
        _txList = txList;
    }
    // Buffer que armazenará a árvore em sí
    char *_layer[MAX_BUFFER_SIZE];
    
    for (int register i = 0; i < txCount/2; i += 1)
    {
        _layer[i] = getTxPairHash(_txList[2*i], _txList[(2*i)+1]);
    }
    return getNextLayer(_layer, txCount/2);
}
