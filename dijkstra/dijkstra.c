#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct Node {
    int vertex;
    int distance;
    struct Node *next;
}typedef Node;

// Encontra o nó com a menor distância
Node * shortestDistance(Node *distances[], int visited[], int numVertex) {
    Node *less = NULL;
    int min_value = (int) INFINITY;

    for (int i = 0; i<numVertex; i++) {
        if (distances[i] != NULL && visited[i] == 0 && distances[i]->distance < min_value) {
            min_value = distances[i]->distance;
            less = distances[i];
        }
    }
    return less;
}

void dijkstra(int numVertex, int graph[][numVertex], int src) {
    Node *distances[numVertex];
    int visited[numVertex];
    for (int i = 0; i < numVertex; i++) {
        distances[i] = NULL;
        visited[i] = 0;
    }
    distances[src] = (Node*) malloc(sizeof(Node));
    distances[src]->vertex = src;
    distances[src]->distance = 0;
    distances[src]->next = NULL;

    // Encontra o caminho mais curto para cada nó
    for (int i = 0; i < numVertex-1; i++) {
        Node *atual = shortestDistance(distances, visited, numVertex);
        visited[atual->vertex] = 1;
      
        for (int j = 0; j < numVertex; j++) {

            if (graph[atual->vertex][j] != 0 && visited[j] == 0) {
                int newDistance = atual->distance + graph[atual->vertex][j];
                if (distances[j] == NULL) {
                    distances[j] = (Node*) malloc(sizeof(Node));
                    distances[j]->vertex = j;
                    distances[j]->distance = newDistance;
                    distances[j]->next = NULL;
                } else if (newDistance < distances[j]->distance) {
                    distances[j]->distance = newDistance;
                }
            }
            
        }
    }
    // Imprime as distâncias
    for (int i = 1; i < numVertex; i++) {
        if (distances[i] == NULL) {
            printf("%d: -1 ", i);       //se não alcança o vertice, a distance é -1.
        } else {
            printf("%d:%d ", i, distances[i]->distance);
        }
    }
    printf("\n");
}

int checkArguments(int argc, char *argv[], int *printTerminal, int *initialVertex, FILE **inputFile, FILE **outputFile){
    if (argc < 2) {
        printf("Por favor use por exemplo: %s -f arquivo-entrada.dat\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-h") == 0) {
            printf("*******Help ******\n\nVocê pode usar os seguintes argumentos ao executar o programa:\n\n"
                    "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                    "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                    "-s : mostra a solução (em ordem crescente)\n"
                    "-i : vértice inicial\n\n"
                    "Exemplo de uso:\nPara calcular o custo da AGM com o grafo de entrada \"arquivo-entrada.dat\" e vértice inicial 1:\n"
                    "$ ./prim -f arquivo-entrada.dat -i 1\n");
            return 1;
        } 

        else if (strcmp(argv[i], "-o") == 0) {
            if (i < argc - 1) {
                char *fileName = argv[i+1];
                *outputFile = fopen(fileName, "w");

                if (*outputFile == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", fileName);
                    return 1;
                }
                i++;
            } 
            else {
                printf("Erro: Faltando nome do arquivo de saída depois do argumento -o\n");
                return 1;
            }
        } 

        else if (strcmp(argv[i], "-f") == 0) {
            if (i < argc - 1) {
                char *fileName = argv[i+1];
                *inputFile = fopen(fileName, "r");

                if (*inputFile == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", fileName);
                    return 1;
                }
                i++;
            } 
            else {
                printf("Erro: Faltando nome do arquivo de entrada depois do argumento -f\n");
                return 1;
            }
        } 

        else if (strcmp(argv[i], "-i") == 0) {
            if (i < argc - 1) {
                *initialVertex = atoi(argv[i+1]);
            } 
            else {
                printf("Erro: Faltando um inteiro depois do argumento -i\n\nConsulte ajuda atraves do argumento -h\n");
                return 1;
            }
        }
    }    
    return 0;
}

int main(int argc, char *argv[]) {
    int initialVertex=1;
    int numVertex, numEdges, vertexa1, vertex2, distEdge;
    int printTerminal = 1;
    FILE *inputFile=NULL, *outputFile=NULL;

    //verificar argumentos enviados na execução...
    checkArguments(argc, argv, &printTerminal, &initialVertex, &inputFile, &outputFile);

    fscanf(inputFile, "%d %d", &numVertex, &numEdges);
    int graph[numVertex+1][numVertex+1];
    memset(graph, 0, sizeof(graph));
    
    while (fscanf(inputFile, "%d %d %d", &vertexa1, &vertex2, &distEdge) != EOF) {
        graph[vertexa1][vertex2] = distEdge;
        graph[vertex2][vertexa1] = distEdge;
    }

    dijkstra(numVertex+1, graph, initialVertex);

    fclose(inputFile);
    return 0;
}
