#include "ListaEncadeada.h"

int main(void){
    
    ListaEncadeada lista;
    lista.insert(1);
    lista.insert(2);
    lista.insert(3);
    lista.show();
    lista.remove(2);
    lista.show();

    return 0;
}