// Definição do main
  #ifndef MAIN
  #define MAIN
//=================================================================================
// Bibliotecas usadas
  #include <iostream>
//=================================================================================

// Namespace global para os métodos usados 
namespace teoriaDosNumeros{
    class mdc{
        private:
            // Atibutos internos que guardam os dados da classe
            int *restosResult;
            int *quocientesV;
            int *x;
            int a;
            int b;
            int *y;
            int mdcResult;
        public:
        // Construtores
        mdc();
        mdc(int a, int b);
        mdc(mdc &other);
        // getter's da classe
        int getA();
        int getB();
        int *getRestos();
        int *getQuocientes();
        int getMdcResult();

        // Setter's da classe
        void setA(int A);
        void setB(int B);
        // Os demais atributos são Read Only
        
        // Métodos internos da classe
        void calcula();
        void restos();
        void quocientes();
        void calc_x();
        void calc_y();
    }; // End mdc
    class mmc{
        private:
            int a;
            int b;
            int mmcResult;
        public:
            mmc(int a, int b);
            mmc (mdc d);
            void setA(int a);
            void setB(int b);
            
            int getA();
            int getB();
            int getMmcResult();
    }; // End mmc
}; // End namespace

#endif