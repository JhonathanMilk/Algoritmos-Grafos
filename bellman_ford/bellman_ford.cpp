#include<bits/stdc++.h>
#include <fstream>
#include <climits>
#define lli long long int
#define veci vector<int>
#define vecb vector<bool>
#define vecp vector<pair<int, int>>
using namespace std;

typedef struct {
    int v1, v2, weight;
} edge;

vector<edge> graph;

void bellman_ford(int numVertex, int numEdges, int initial, int final) {
    ofstream File(string("Saída.dat"));
    initial--;
    final--;
    veci d(numVertex, INT_MAX);
    d[initial] = 0;
    for (int i = 0; i<numVertex-1; ++i)
        for (int j=0; j<numEdges; ++j) {
            if (d[graph[j].v1] < INT_MAX) {
                d[graph[j].v2] = min(d[graph[j].v2], d[graph[j].v1] + graph[j].weight);
            }
        }
    cout << "Distancia do vértice inicial para cada vértice:\n";
    File << "Distancia do vértice inicial para cada vértice:\n";
    for (int i = 0; i < numVertex; i++) {
        cout << i+1  << ":" << d[i] << " ";
        File << i+1  << ":" << d[i] << " ";
    }
    cout << endl;
    File << endl;
    cout << "\nDistancia do vértice inicial ao final (" << initial+1 << " -> " << final+1 << "):\n" << d[final] << endl;
    File << "\nDistancia do vértice inicial ao final (" << initial+1 << " -> " << final+1 << "):\n" << d[final] << endl;
}


int main(int argc, char *argv[]) {
    int numVertex, numEdges; cin >> numVertex >> numEdges;
    edge new_edge;
    for (int i = 0; i < numEdges; i++) {
        int vertex1, vertex2, weight; cin >> vertex1 >> vertex2 >> weight;
        new_edge.v1 = vertex1-1;
        new_edge.v2 = vertex2-1;
        new_edge.weight = weight;
        graph.push_back(new_edge);
    }
    int i = 1, l = numVertex;            //Consideramos que o vertice inicial é o menor, e o vertice final o maior (numVertices)
    bellman_ford(numVertex, numEdges, i, l);
}