#include "main.h"
int main(void){
    ListaContigua lista;
    
    lista.insert('a');
    lista.insert('b');
    lista.show();
    lista.del(1);
    lista.show();

    return 0;
}