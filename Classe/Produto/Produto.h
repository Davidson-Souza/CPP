#ifndef PRODUTO
#define PRODUTO
#include <iostream>

class Produto{
    public:
    Produto();
    Produto(Produto &outro);

    Produto(int tam);

    int getCodigo();
    
    void setCodigo(int codigo);

    private:
    int codigo;
};
#endif