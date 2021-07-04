/**
 * Davidson Lucas de Souza
 * Teoria de Grafos - 5º Período do curso de Bacharelado em Ciência da Computação
 * Atividade ERE - Semana XXXX 
 * Esse arquivo faz manipulações básicas em grafos. Os grafos são representados com uma
 * matriz de correspondência M x M, onde o elemento ij indica quantas ligações existem
 * entre o vértice da linha i com o vértice da coluna j. O código vem com um grafo simples
 * no arquivo "grafo.txt" e mostra algumas informações dele na tela, bem como adiciona
 * um novo vértice e salva o novo grafo no disco.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **readFromDisk(int *vertexCount);
void writeToDisk(int vertexCount, int **graph);
int getDegree(int vertexCount, int **graph);
int isSimple(int vertexCount, int **graph);
void show(int vertexCount, int **graph);
void addEdge(int vertexCount, int **graph, int a, int b);
int isComplete(int vertexCount, int **graph);

int main()
{
    int vertexCount;
    
    printf("Lendo o grafo do disco...\n");
    /** Lê o grafo do disco */
    int **graph = readFromDisk(&vertexCount);

    /** Mostra o grafo lido */
    show(vertexCount, graph);

    /** Verifica o grau do grafo */
    printf("\n--> O grau do grafo é: %d\n", getDegree(vertexCount, graph));
    
    /** Verificando se o grafo é simples */
    printf("--> O grafo %s simples\n", isSimple(vertexCount, graph) ? "não é" : "é");
    
    /** Verifica se o grafo é completo*/
    printf("--> O grafo %s completo\n", isComplete(vertexCount, graph) ? "é" : "não é");

    printf("\n\n----------------- Adicionando uma aresta entre 0 e 2 ------------------\n\n");
    
    /** Adiciona uma aresta entre 0 - 2 */
    addEdge(vertexCount, graph, 0, 2);
    
    /** Mostra o grafo */
    show(vertexCount, graph);
    
    /** Mostra o grau do novo grafo*/
    printf("\n--> O grau do novo grafo é: %d\n", getDegree(vertexCount, graph));
    
    /** Verifica se o novo grafo é completo*/
    printf("--> O novo grafo %s completo\n", isComplete(vertexCount, graph) ? "é" : "não é");

    /** Verificando se o grafo é simples */
    printf("--> O novo grafo %s simples\n", isSimple(vertexCount, graph) ? "não é" : "é");
    
    printf("Salvando o grafo...\n");
    /** Escreve ele no disco */
    writeToDisk(vertexCount, graph);

    return 0;
}
/** Adiciona uma aresta entre "a" e "b" */
void addEdge(int vertexCount, int **graph, int a, int b)
{
    if(a >= vertexCount || b >= vertexCount)
    {
        return ;
    }
    graph[a][b] += 1;
    graph[b][a] += 1;
}
int isComplete(int vertexCount, int **graph)
{
    for(unsigned register int i = 0; i<vertexCount; i++)
        for(unsigned register int j = 0; j<vertexCount; j++)
                if (graph[i][j] == 0 && i != j)
                    return 0;
    return 1;
}
/** Mostra o grafo na tela */
void show(int vertexCount, int **graph)
{
    printf("Mostrando o grafo: \n   ");
    for(unsigned register int i = 0; i<vertexCount; i++)
    {
        printf("%d ", i);
    }
    printf("\n  ");

    for(unsigned register int i = 0; i<vertexCount; i++)
    {
        printf("──");
    }
    printf("\n");
    for(unsigned register int i = 0; i< vertexCount;i++)
    {
        printf("%d| ", i);
        for(unsigned register int j = 0; j< vertexCount;j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}
/** Retorna o grau de um grafo */
int getDegree(int vertexCount, int **graph)
{
    int degree = 0;
    for(unsigned register int i = 0; i<vertexCount; i++)
        for(unsigned register int j = 0; j<vertexCount; j++)
                degree+= graph[i][j];
    return degree;
}
/** Retorna se ele é simples ou não */
int isSimple(int vertexCount, int **graph)
{
    for(unsigned register int i = 0; i<vertexCount;i++)
        for(unsigned register int j = 0; j<vertexCount;j++)
            if(graph[i][j] > 1)
                return 1;
    return 0;
}
/** Escrevendo o grafo no disco */
void writeToDisk(int vertexCount, int **graph)
{
    char *buffer = malloc((vertexCount * 4) + 3);
    memset(buffer, 0, (vertexCount * 4) + 3);
    FILE *graphFile = fopen("grafo.txt", "w");
    if(graphFile == NULL)
    {
        printf("Erro ao ler o arquivo!\n");
        return ;
    }
    fprintf(graphFile, "%d\n", vertexCount);
    for(unsigned register int i = 0; i<vertexCount;i++)
        for(unsigned register int j = 0; j<vertexCount;j++)
        {
            fprintf(graphFile, "%d ", graph[i][j]);
        }

    fprintf(graphFile, "%s", buffer);
    fclose(graphFile);
}
/** Lendo do disco */
int **readFromDisk(int *vertexCount)
{
    FILE *graphFile = fopen("grafo.txt", "r");
    int **readGraph = (int **) malloc(*vertexCount);
    fscanf(graphFile, "%d", vertexCount);

    for(unsigned register int i = 0; i<*vertexCount; i++)
        readGraph[i] = (int *) malloc(*vertexCount);
           
    for(unsigned register int i = 0; i<*vertexCount;i++)
        for(unsigned register int j = 0; j<*vertexCount;j++)
            fscanf(graphFile, "%d", &readGraph[i][j]);
    fclose(graphFile);
    return readGraph;
}