#include "transaction.h"
#include "utilities/md5.c"

#include <stdio.h>
#include <time.h>
#include <string.h>
Transaction::Transaction()
{
    this->data = "";
}
Transaction::Transaction(char *data)
{
    if (strlen(data) > 100)
    { 
        printf("Excedido o tamanho máximo!");
        return;
    }

    bytes2md5(data,HASH_LENGTH,this->hash);

    this->timeLock = time(NULL);
    this->data = data;
}

time_t Transaction::getTimeLock()
{
    return this->timeLock;
}

char *Transaction::getHash()
{
    return this->hash;
}

char *Transaction::getData()
{
    return this->data;
}
void Transaction::getRawData(char dest[1000])
{
    sprintf(dest, "%s%s%d", this->data, this->hash, this->timeLock);
}