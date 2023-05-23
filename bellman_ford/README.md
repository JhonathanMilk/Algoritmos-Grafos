# Dijkstra - Teoria dos Grafos

## Compilando

```
make compile
```

## Executando
**Podemos executar de duas maneiras:**  

Passando o grafo manualmente:  
```
./bellman_ford.bin
```  

Passando um arquivo que contém o grafo  
```
./bellman_ford.bin < inputData.txt
```  

## Informações importantes  

#### Formato da entrada (grafo):  
A primeira linha da entrada deve possuir dois números inteiros: **n** e **m**. Onde :
- **n** = número de vértices
- **m** = número de arestas.  

Em seguida, deve ter **m** linhas, que representam as arestas do grafo, cada linha possui três inteiros: **u**, **v** e **w**. Onde:
- **u** = vértice 1 pertencente a aresta
- **v** = vértice 2 pertencente a aresta 
- **w** = peso da aresta.

Lembrando que para o algoritmo funcionar corretamente os vérticos devem ser de 1 a n.  

#### Grafo exemplo::  
```
6 8
1 2 5
1 3 4
1 4 2
1 6 6
2 4 1
2 5 7
3 5 6
4 6 1
```  

#### Grafos para testes (inputData):  

O diretório `input-graphs` possui 20 arquivos no formato ```.mtx``` para testar o programa.
Podemos então, por exemplo, executar o programa com o comando:  
```
./bellman_ford.bin < input-graphs/grafo1.mtx
```  





