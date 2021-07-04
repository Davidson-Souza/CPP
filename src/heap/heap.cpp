#include <stdio.h>
static void troca(int *e1, int *e2)
{
    int aux;
    aux = *e1;
    *e1 = *e2;
    *e2 = aux;
}
static void 
constroiHeap (int m, int v[])
{
   for (int k = 1; k < m; ++k) {                   
      // v[1..k] é um heap
      int f = k+1;
      while (f > 1 && v[f/2] < v[f]) {  // 5
         troca (&v[f/2], &v[f]);        // 6
         f /= 2;                        // 7
      }
   }

}
static void 
peneira (int m, int v[]) {
   int f = 2;
   while (f <= m) {
      if (f < m && v[f] < v[f+1]) ++f;
      // f é o filho mais valioso de f/2
      if (v[f/2] >= v[f]) break;
      troca (&v[f/2], &v[f]);
      f *= 2;
   }
}

int main()
{
    int vet[] = {1, 7, 2, 3, 1, 0};
    constroiHeap(4, vet);
    peneira(4, vet);
    for (unsigned register int i = 0; i<5; i++)
        printf("%d ", vet[i]);
    printf("\n");
    return 0;
}