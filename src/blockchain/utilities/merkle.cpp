#include "transaction.h"
#include "utilities/md5.c"
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_LEVELS 100
#define MAX_BUFFER_SIZE 10000
/**
 * Cada posição do vetor tree corresponde a um nível da árvore, o cálculo para alocação é feito o seguinte:
 * Cada hash possui 32 caracteres (33 com o \0), após isso o operador ternário navega pelos níveis.
 * No nível 0 (considerando a árvor de ponta-cabeça), a árvore tem txCount elementos, e o nível também.
 * No nível 1, a árvore tem txCount / 2 * i(1) ou seja, metade do item anterior.
 * E assim por diante.
 * A árvore também nescessita que o número de elementos seja par
*/
void getTxPairHash(char *dest, Transaction t1, Transaction t2)
{
    char buffer[MAX_BUFFER_SIZE], aux[MAX_BUFFER_SIZE];
    t1.getRawData(buffer);
    t2.getRawData(aux);
    strcat(buffer, aux);
    bytes2md5(buffer, 32, dest);
}
void getHashPairHash(char *dest, char *h1, char *h2)
{
    char buffer[MAX_BUFFER_SIZE];
    strcat(buffer, h1);
    strcat(buffer, h2);
    bytes2md5(buffer, 32, dest);
    dest = buffer;
}
void createMerkleTree(Transaction *txList, int txCount, char *topDest)
{
    if (txCount % 2 == 1)
    {
        txList[txCount] = txList[txCount - 1];
        txCount++;
    }
    char **tree[MAX_TREE_LEVELS];

    tree[0] = (char **) malloc((sizeof(char) * 33) * txCount);  

    register int i = 1, levelElementsCount = txCount;
    do
    {
        levelElementsCount = levelElementsCount/2*i;
        tree[i] = (char **) malloc((sizeof(char) * 33) * levelElementsCount);                                          
        for (int register j = 0; j < levelElementsCount; j += 2)
            if (i == 1)
                getTxPairHash(tree[i][j], txList[j], txList[j+1]);
            else
                getHashPairHash(tree[i][j], tree[i-1][j], tree[i-1][j+1]);
    }while (levelElementsCount > 1);

    topDest = tree[i][0];
}
