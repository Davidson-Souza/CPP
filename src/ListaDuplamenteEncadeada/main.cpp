#include "ListaDuplamenteEncadeada.h"
#include <iostream>
int main(void){
    ListaDuplamenteEncadeada lista;
    lista.insert('A');
    lista.show();
    Node * elemento = lista.getElemento(1);
    std::cout << elemento->getData();
    return 0;
}