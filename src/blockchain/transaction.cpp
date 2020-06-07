#include "utilities/md5.c"

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "transaction.h"
#ifndef TRANSACTION_CPP
#define TRANSACTION_CPP
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

    this->timeLock = time(NULL);
    this->data = data;

    char _rawData[100];
    this->getRawData(_rawData);
    bytes2md5(_rawData,sizeof(char) * strlen(_rawData),this->hash);
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

#endif