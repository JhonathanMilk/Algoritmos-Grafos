# Dijkstra - Teoria dos Grafos

## Compilando

```
make compile
```

## Executando
São aceitos os seguintes parâmetros na execução:
> **-h :** mostra o help  
> **-o < *output* > :** redireciona a saida do programa para o ‘‘output’’  
> **-f < *inputData* > :** indica o arquivo que contém o grafo de entrada  
> **-s** : mostra a solução (em ordem crescente)
  
Obrigatoriamente deve-se passar ao menos o inputData como parâmetro na execução do programa  
  
## Exemplos de execução:  
Imprime o custo do grafo representado no arquivo "inputData.txt":  
```
./kruskal -f inputData.txt
```
  
Imprime a árvore geradora mínima (em ordem crescente):  
```
./kruskal -f inputData.txt -s
```  

Imprime o Help:  
```
./kruskal -h
```  

Escreve no arquivo `output.txt` a AGM (árvore geradora mínima):  
```
./dijkstra -f inputData.txt -s -o output.txt
```

## Informações importantes  

### Formato da entrada (grafo):  
A primeira linha da entrada deve possuir dois números inteiros: **n** e **m**. Onde :
- **n** = número de vértices
- **m** = número de arestas.  

Em seguida, deve ter **m** linhas, que representam as arestas do grafo, cada linha possui três inteiros: **u**, **v** e **w**. Onde:
- **u** = vértice 1 pertencente a aresta
- **v** = vértice 2 pertencente a aresta 
- **w** = peso da aresta.

Lembrando que para o algoritmo funcionar corretamente os vérticos devem ser de 1 a n.


