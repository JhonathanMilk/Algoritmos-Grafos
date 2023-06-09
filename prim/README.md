# Prim - Teoria dos Grafos

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
> **-i :** vértice inicial (valor padrão = 1)
  
Obrigatoriamente deve-se passar ao menos o inputData como parâmetro na execução do programa  
  
## Exemplos de execução:  
Imprime o custo do AGM representado no arquivo "inputData.txt":  
```
./prim.bin -f inputData.txt
```
  
Imprime a árvore geradora mínima (em ordem crescente):  
```
./prim.bin -f inputData.txt -s
```  

Imprime a árvore geradora mínima (em ordem crescente), iniciando a partir do vértice inicial (3):
```
./prim.bin -f inputData.txt -s -i 3
```  

Imprime o Help:  
```
./prim.bin -h
```  

Escreve no arquivo `output.txt` a AGM (árvore geradora mínima):  
```
./prim.bin -f inputData.txt -s -o output.txt
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

#### Grafo exemplo:  
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



