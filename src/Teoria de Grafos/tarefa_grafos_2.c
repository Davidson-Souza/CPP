/**
 * Davidson Lucas de Souza
 * Teoria de Grafos - 5º Período do curso de Bacharelado em Ciência da Computação
 * Atividade ERE - Semana 06
*/
/**
 * @note: Deve ser executado junto a um arquivo chamado grafo.txt.
 * Exemplo de arquivo:
 * 8
 * 10
 * 1;2
 * 1;3
 * 2;4
 * 2;5
 * 3;4
 * 4;5
 * 4;6
 * 6;7
 * 6;8
 * 7;8
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **readFromDisk(int *vertexCount, int *edges, int graphType);
void writeToDisk(int vertexCount, int **graph);
int getDegree(int vertexCount, int **graph);
int isSimple(int vertexCount, int **graph);
void showIncidency(int vertex, int edges, int **graph);
void show(int vertexCount, int **graph);
void addEdge(int vertexCount, int **graph, int a, int b);
int isComplete(int vertexCount, int **graph);
void showDegree(int vertexCount, int **graph);
int haveWalk(int vertexCount, int a, int b, int **graph, int *visited);
int isConnected(int vertexCount, int **graph);
int main()
{
    int v, e;
    int **graph = readFromDisk(&v, &e, 1);
    showIncidency(v,e, graph);
    printf("\n-------------------------------------------\n");
    free(graph);
    graph = readFromDisk(&v, &e, 0);
    show(v, graph);

    showDegree(v, graph);
    printf("-------------------------------------\n");
    printf(" --> O grafo %s completo\n", isComplete(v, graph) ? "é":"não é");
    printf(" --> O grafo %s simples\n", isSimple(v, graph)? "é":"não é");
    printf(" --> O grafo %s conexo\n", isConnected(v, graph) > 0? "é": "não é");
    
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

int vertDegree(int vert, int vertexCount, int **graph)
{
    int degree = 0;
    for(unsigned register int i = 0; i<vertexCount; i++)
    {
        degree += graph[vert][i];
    }
    return degree;
}
void showDegree(int vertexCount, int **graph)
{
    printf("-------------------------------------\n");
    printf("Mostrando o grau de cada vértice\n");
    for(unsigned register int i = 0; i<vertexCount; i++)
    {
        printf("%d: %d\n", i, vertDegree(i, vertexCount, graph));
    }
}
/** Show the graph (as a incidence matrix) */
void showIncidency(int vertex, int edges, int **graph)
{
    printf("Matriz de incidência\n  ");

    for(unsigned register int i = 0; i<vertex; i++)
        printf(" %d", i + 1);
    
    printf("\n  ");

    for(unsigned register int i = 0; i<vertex; i++)
    {
        printf("──");
    }
    for(unsigned register int i = 0; i<edges; i++)
    {
        printf("\n%c| ",'A' + i);
        for(unsigned register int j = 0; j<vertex; j++)
        {
            printf("%d ", graph[i][j]);
        }
    }
}
void show(int vertexCount, int **graph)
{
    printf("Matriz de Adjacência\n   ");
    for(unsigned register int i = 0; i<vertexCount; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n  ");

    for(unsigned register int i = 0; i<vertexCount; i++)
    {
        printf("──");
    }
    printf("\n");
    for(unsigned register int i = 0; i< vertexCount;i++)
    {
        printf("%d| ", i + 1);
        for(unsigned register int j = 0; j< vertexCount;j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}
/** Returns whether the graph is regular or not (i.e all vertex have the same degree)*/
int isRegular(int vertexCount, int **graph)
{
    int degree = getDegree(0, graph);
    for(unsigned register int i = 1; i<vertexCount; i++)
        if(degree != getDegree(i, graph));
            return 0;
    return 1;
    
}
/** Returns whether the graph is complete or not (i.e all vertex are connected each other)*/
int isComplete(int vertexCount, int **graph)
{
    for(unsigned register int i = 1; i<vertexCount; i++)
        for(unsigned register int j=0; j<vertexCount; j++)
            if(i!=j && graph[i][j] <= 0)
                return 0;
    return 1;
}

/** Recursively find a walk between two points, not return the walk, but only if exists or not*/
int haveWalk(int vertexCount, int a, int b, int **graph, int *visited)
{
    visited[a] = 1;
    int res = 0;
    if(graph[a][b] > 0)
        return 2;
    for(unsigned register int i = 0; i<vertexCount; i++)
        if(graph[a][i] > 0 && visited[i] != 1)
        {
            res = haveWalk(vertexCount, i, b, graph, visited);
            if(res == 2)
                return 2;
        }
    return res;
}
/** For all vertex a and b in G, there should exists at least one walk between then */
int isConnected(int vertexCount, int **graph)
{
    int visited[vertexCount];

    for(unsigned register int i = 1; i<vertexCount; i++)
    {
        memset(visited, 0x00, sizeof(int) * vertexCount);
        if(haveWalk(vertexCount, 0, i, graph, visited) == 0)
        {
            printf("The fault is: %d\n", i);
            return 0;
        }
    }

    return 1;
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
                return 0;
    return 1;
}
/** Write the graph as an adjacency matrix */
void writeToDisk(int vertexCount, int **graph)
{
    char *buffer = malloc((vertexCount * 4) + 3);
    memset(buffer, 0, (vertexCount * 4) + 3);
    FILE *graphFile = fopen("grafo.txt", "w");

    if(graphFile == NULL)
    {
        printf("Error reading the file!\n");
        return ;
    }
    fprintf(graphFile, "%d\n", vertexCount);
    for(unsigned register int i = 0; i<vertexCount;i++)
        for(unsigned register int j = 0; j<vertexCount;j++)
            fprintf(graphFile, "%d ", graph[i][j]);

    fprintf(graphFile, "%s", buffer);
    fclose(graphFile);
}

/** Read the file */
int **readFromDisk(int *vertexCount, int *edges, int graphType)
{
    int a, b, vertex, edge;

    FILE *graphFile = fopen("grafo.txt", "r");
    if(graphFile == NULL)
        return NULL;
    
    fscanf(graphFile, "%d", &vertex);
    fscanf(graphFile, "%d", &edge);
    
    int **readGraph;
    
    if(graphType == 0)
    {
        readGraph = (int **) malloc(vertex * sizeof(int *));

        for(unsigned register int i = 0; i<vertex; i++)
        {
            readGraph[i] = (int *) malloc(vertex * sizeof(int));
            memset(readGraph[i], 0x00, vertex * sizeof(int));
        }
    
        for(unsigned register int j = 0; j<edge;j++)
        {
            fscanf(graphFile, "%d;%d", &a, &b);
            if(a > vertex || b > vertex)
            {
                continue;   
            }
            readGraph[a - 1][b - 1] += 1;
            readGraph[b - 1][a - 1] += 1;
        }
    }
    else
    {
        readGraph = (int **) malloc(edge * sizeof(int *));
        for(unsigned register int i = 0; i<edge; i++)
            readGraph[i] = (int *) malloc(vertex * sizeof(int *));
        
        for(unsigned register int i = 0; i<edge;i++)
        {
            fscanf(graphFile, "%d;%d", &a, &b);
            readGraph[i][a - 1] += 1;
            readGraph[i][b - 1] += 1;
        }
    }
    if(vertexCount != NULL)
        *vertexCount = vertex;
    if(edges != NULL)
        *edges = edge;
    fclose(graphFile);
    return readGraph;
}