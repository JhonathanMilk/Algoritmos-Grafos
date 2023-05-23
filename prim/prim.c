#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


struct Node
{
    int vertex;
    int weight;
    struct Node*next;    
}typedef Node;

struct Edge {
    int src, dest, weight;
}typedef Edge;

void addNewNode(Node *graph[],int vertex1,int vertex2,int edgeWeight){
        Node *new_node = (Node*) malloc(sizeof(Node));
        new_node->vertex = vertex2;
        new_node->weight = edgeWeight;
        new_node->next = NULL;

        if(graph[vertex1] == NULL){
            graph[vertex1] = new_node;
            return;
        }
        else{
            Node *nodeAux = graph[vertex1];
            while(nodeAux->next != NULL){
                nodeAux=nodeAux->next;
            }
            nodeAux->next = new_node;
        }
}

bool allVisited(int array[], int numVertex){
    for(int i=0; i<=numVertex; i++){
        if (array[i] == false) return false;
    }
    return true;
}

// comparar duas numEdges
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    if (edgeA->src == edgeB->src) {
        return edgeA->dest - edgeB->dest;
    }
    return edgeA->src - edgeB->src;
}

void printOut(Edge edges[], int inOrderAgm, int numVertex,int cost, int printTerminal, FILE *outputFile){
    // ordenar as numEdges pela sequência dos nós e seus pais - CASO FOR PASSADO O ARGUMENTO -s NA EXECUÇÃO
    if(inOrderAgm){
        qsort(edges, numVertex-1, sizeof(Edge), compareEdges);
    }
    // printOut a AGM na ordem desejada
    if(printTerminal){
        if(inOrderAgm){
                for (int i = 0; i < numVertex-1; i++) {
                    printf("(%d,%d) ", edges[i].src, edges[i].dest);
                }
                printf("\n");
                return;
        }
        printf("%d\n", cost);
    }
    else
    {
        printf("Saída escrita no arquivo \n");
        for (int i = 0; i < numVertex-1; i++) {
            fprintf(outputFile,"(%d,%d) ", edges[i].src, edges[i].dest);
        }
        fprintf(outputFile,"%d\n", cost);  
        fclose(outputFile);
    }
}

void prim(Node* graph[], Edge edges[], int start_vertex, int numVertex, int *cost) {
    int key[numVertex], visited[numVertex], parent[numVertex];
    //  inicializando...
    for (int i = 0; i <= numVertex; i++) {
        key[i] = (int)INFINITY;
        visited[i] = false;
        parent[i] = -1;
    }

    key[start_vertex] = 0;
    int count = 0;
    int edgeCount = 0;

    while (!allVisited(visited, numVertex)) {
        int u = -1;
        for (int i = 0; i <= numVertex; i++)
            if (!visited[i] && (u == -1 || key[i] < key[u]))
                u = i;                
        visited[u] = true;
        if (parent[u] != -1) {
            count++;
            *cost+=key[u];

            edges[edgeCount].src = parent[u];
            edges[edgeCount].dest = u;
            edges[edgeCount].weight = key[u];
            edgeCount++;
        }

        Node* temp = graph[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;
            if (!visited[v] && key[v] > w) {
                key[v] = w;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
}

int checkArguments(int argc, char *argv[], int *printTerminal, int *inOrderAgm, int *initial_vertex, FILE **inputFile, FILE **outputFile) {
    
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
            *printTerminal = 0;
            if (i < argc - 1) {
                char *fileName = argv[i+1];
                *outputFile = fopen(fileName, "w");
                if (*outputFile == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", fileName);
                    return 1;
                }
                i++;  // Avança para o próximo argumento, pois ja leu o argumento i+1
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
                i++;  // Avança para o próximo argumento, pois ja leu o argumento i+1
            } 
            else {
                printf("Erro: Faltando nome do arquivo de entrada depois do argumento -f\n");
                return 1;
            }
        } 
        else if (strcmp(argv[i], "-s") == 0) {
            *inOrderAgm = 1;
        } 
        else if (strcmp(argv[i], "-i") == 0) {
            if (i < argc - 1) {
                *initial_vertex = atoi(argv[i+1]);
                i++;  // Avança para o próximo argumento
            } 
            else {
                printf("Erro: Faltando um inteiro depois do argumento -i\n\nConsulte ajuda através do argumento -h\n");
                return 1;
            }
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    int initial_vertex = 1, numVertex, numEdges, vertex1, vertex2, edgeWeight, cost = 0;
    int inOrderAgm = 0;             //define se printa AGM em ordem ou não
    int printTerminal = 1;          //define onde será impresso
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    if (checkArguments(argc, argv, &printTerminal, &inOrderAgm, &initial_vertex, &inputFile, &outputFile) != 0) {
        return 1;
    }

    fscanf(inputFile, "%d %d", &numVertex, &numEdges);
    Node *graph[numVertex + 1];
    Edge edges[numVertex - 1];
    for (int i = 0; i <= numVertex; i++) {
        graph[i] = NULL;
    }
    while (fscanf(inputFile, "%d %d %d", &vertex1, &vertex2, &edgeWeight) != EOF) {
        addNewNode(graph, vertex1, vertex2, edgeWeight);
        addNewNode(graph, vertex2, vertex1, edgeWeight);
    }

    prim(graph, edges, initial_vertex, numVertex, &cost);
    printOut(edges, inOrderAgm, numVertex, cost, printTerminal, outputFile);

    fclose(inputFile);
    return 0;
}

