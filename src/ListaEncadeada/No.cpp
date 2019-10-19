#include "No.h"
#include <iostream>

No::No(){
    this->data = 0;
    this->next = NULL;
}

void No::setData(int data){
    this->data = data;
}
void No::setNext(No *next){
    this->next = next;
}

int No::getData(){
    return this->data;
}

No* No::getNext(){
    return this->next;
}
