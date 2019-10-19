#include "ListaEncadeada.h"
int main(){
    ListaEncadeada lista;
    lista.insert(1);
    lista.insert(2);
    lista.insert(3);
    lista.insert(4);
    lista.insert(5);

    lista.show();
    lista.remove(3);
    lista.show();
}