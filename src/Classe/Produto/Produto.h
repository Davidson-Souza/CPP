#ifndef PRODUTO
#define PRODUTO
#include <iostream>

class Produto{
    public:
        Produto();
        Produto(Produto &outro);

        Produto(int tam);

        void fill();
        void show();

        int getCodigo();
        int getEstoque();
        float getPreco();
        float getCusto();
    
        void setCodigo(int codigo);
        void setEstoque(int estoque);
        void setPreco(float preco);
        void setCusto(float custo);
    
    
    private:
        int codigo;
        float preco;
        int estoque;
        float custo;
};
#endif