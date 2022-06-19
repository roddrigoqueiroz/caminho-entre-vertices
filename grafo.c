#include <stdio.h>
#include <stdlib.h>

#define MAX 4 // MAX tem que ser igual ao número de caminhos possíveis, ou seja, qtd_aresta.

// O topo dessa pilha começa em -1. Pois quando formos usar Empilha, a informação inserida será em elementos[topo + 1]
struct pilha
{
    int topo; // topo é onde está o topo da minha pilha
    int *elementos; // elementos é o array com todos os elementos empilhados
    int tamanho;
};

typedef struct pilha Pilha;

// PROTÓTIPOS DAS FUNÇÕES

int **ler_grafo(int *vertice, int *qtd_aresta);
void printa_grafo(int vertice, int **grafo);
int zera_grafo(int vertice, int **grafo);
void destroi_grafo(int vertice, int **grafo);
int **cria_grafo(int vertice);

void destroi(Pilha *pilha);
int desempilha(Pilha *pilha, int *elementoDesempilhado);
int empilha(Pilha* pilha, int elemento);
int vazia(Pilha *pilha);
int cheia(Pilha *pilha);
Pilha *criaPilha(int qtd_arestas);
void printa_pilha(Pilha *pilha);

int existe_caminho(int vertice, int qtd_arestas, int **grafo);

int main(void)
{
    // No algoritmo devo empilhar todos os caminhos que forem vizinhos de N.
    // Para algo ser vizinho de N, tenho que grafo[N][i] != 0
    // Posso colocar essa condição dentro de um for com um empilha lá dentro.

    int vertice, qtd_arestas;

    int **grafo = ler_grafo(&vertice, &qtd_arestas);

    // printa_grafo(vertices, grafo);

    int resultado = existe_caminho(vertice, qtd_arestas, grafo);
    if (resultado > 0)
        printf("Resultado: %d\n", resultado);

    destroi_grafo(vertice, grafo);
    return 0;
}

// Por enquanto esta função só funciona com um caminho de 1 aresta de distancia
int existe_caminho(int vertice, int qtd_arestas, int **grafo)
{
    int v_saida, v_chegada; // Vertices de saída e chegada
    scanf("%d", &v_saida);
    scanf("%d", &v_chegada);

    if (v_saida < 0 || v_chegada < 0)
        return -1;
    if (v_saida > vertice || v_chegada > vertice)
        return -1;

    Pilha *pilha = criaPilha(qtd_arestas);
    if (pilha == NULL)
        return -2;

    int j, variavel;
    int caminho = 0;
    for(j = 0; j < vertice; j++)
    {
        if (grafo[v_saida][j] != 0)
            empilha(pilha, grafo[v_saida][j]);
        if (j == v_chegada)
        {
            desempilha(pilha, &variavel);
            caminho += variavel;
            destroi(pilha);
            return caminho;
        }
    }
    desempilha(pilha, &variavel);

    desempilha(pilha, &variavel);
    caminho += variavel;
    empilha(pilha, variavel);

    destroi(pilha);

    return caminho;
}

//
//
// FUNÇÕES QUE TRATAM A PILHA //
//
//

void printa_pilha(Pilha *pilha)
{
    int i;
    for (i = (pilha -> tamanho) - 1; i >= 0; i++)
    {
        printf("%d\n", pilha -> elementos[i]);
    }

    return;
}

Pilha *criaPilha(int tamanho)
{
    Pilha *pilha;

    pilha = (Pilha *) malloc(sizeof(Pilha));

    // Testando se a alocação deu certo
    if(pilha != NULL)
    {
        // qtd_arestas é a quantidade de arestas que o usuário inputou para mim.
        // É importante que a pilha comporte no máximo todas as arestas, assim o algoritmo de busca consegue
        // funcionar como foi planejado e a pilha não ficará sem espaço e nem desperdiçará muita memória.

        pilha -> tamanho = tamanho;
        pilha -> elementos = malloc(tamanho * sizeof(int));
        pilha -> topo = -1;
    }

    return pilha;
}

int cheia(Pilha *pilha)
{
    // Ocorreu algum erro na criação da pilha
    if(pilha == NULL)
        return -1;

    if(pilha -> topo == (pilha -> tamanho) - 1)
        return 1;
    else
        return 0;

}

int vazia(Pilha *pilha)
{
    // Ocorreu algum problema na criação da pilha
    if(pilha == NULL)
        return -1;

    if(pilha -> topo == -1)
        return 1; // A pilha está vaiza, True
    else
        return 0; // A pilha não está vazia, False
}

int empilha(Pilha* pilha, int elemento)
{
    // Ocorreu algum problema na criação da pilha
    if(pilha == NULL) return 0;

    // Se a pilha estiver cheia nao terá como empilhar
    if(cheia(pilha)) return 0;

    // Incrementando o topo da pilha
    pilha -> topo = pilha -> topo + 1;

    // Colocando o elemento no topo
    pilha -> elementos[ pilha -> topo ] = elemento;

    return 1;

}

int desempilha(Pilha *pilha, int *elementoDesempilhado)
{
    if(pilha == NULL || pilha -> topo == -1)
        return 0;

    *elementoDesempilhado = pilha -> elementos[pilha -> topo];

    // Decrementando o topo da pilha
    pilha -> topo = pilha -> topo - 1;

    return 1;

}

void destroi(Pilha *pilha)
{
    free(pilha);
}

//
//
// FUNÇÕES QUE TRATAM O GRAFO //
//
//

int **cria_grafo(int vertice)
{
    int **grafo = malloc(vertice * sizeof(int *));
    if (grafo == NULL)
        return NULL;

    int i;
    for (i = 0; i < vertice; i++)
    {
        grafo[i] = malloc(vertice * sizeof(int));
        if (grafo[i] == NULL)
            return NULL;
    }

    return grafo;
}

void destroi_grafo(int vertice, int **grafo)
{
    int i;
    for (i = 0; i < vertice; i++)
    {
        // Libera cada vetor alocado para grafo
        free(grafo[i]);
    }
    // Libera o vetor de vetores grafo
    free(grafo);

    return;
}

int zera_grafo(int vertice, int **grafo)
{
    if (vertice <= 0 || grafo == NULL)
        return -1;

    int i, j;
    for (i = 0; i < vertice; i++)
    {
        for (j = 0; j < vertice; j++)
        {
            grafo[i][j] = 0;
        }
    }

    return 1;
}

void printa_grafo(int vertice, int **grafo)
{
    int i, j;

    if (grafo == NULL)
        return;

    printf("\n");
    for (i = 0; i < vertice; i++)
    {
        for (j = 0; j < vertice; j++)
        {
            printf("%d ", grafo[i][j]);
        }

        printf("\n");
    }
}

int **ler_grafo(int *vertice, int *qtd_aresta)
{
    // Inicia os vertices, arestas e grafos a serem utilizados
    *vertice = -1;
    scanf("%d", vertice);

    *qtd_aresta = -1;
    scanf("%d", qtd_aresta);

    if (*vertice <= 0 || *qtd_aresta <= 0)
        return NULL;

    // Cria um matriz chamada grafo usando alocação dinâmica
    int **grafo = cria_grafo(*vertice);

    if (zera_grafo(*vertice, grafo) == -1)
        return NULL;

    int vertice_a = -1;
    int vertice_b = -1;
    int aresta = 0;
    int copia_qtd_aresta = *qtd_aresta;

    // Lê as entradas do usuário e as coloca dentro do vetor grafo
    while(copia_qtd_aresta > 0)
    {
        scanf("%d", &vertice_a);
        scanf("%d", &vertice_b);
        scanf("%d", &aresta);

        // Caso a leitura de alguma das variáveis dê erro, ou o usuário digite um número negativo, a função retorna erro
        if (vertice_a < 0 || vertice_b < 0)
            return NULL;

        // Caso o usuário resolva colocar o valor de um vertice inválido, a função retorna erro
        if (vertice_a == vertice_b || vertice_a >= *vertice || vertice_b >= *vertice)
            return NULL;

        grafo[vertice_a][vertice_b] = aresta;

        // Atualiza as variáveis para um novo ciclo de checagens
        vertice_a = -1;
        vertice_b = -1;
        copia_qtd_aresta--;
    }

    return grafo;
}