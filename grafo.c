#include <stdio.h>
#include <stdlib.h>

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

int zera_grafo(int vertice, int **grafo)
{
    if (vertice <= 0)
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

int **ler_grafo(void)
{
    // Inicia os vertices, arestas e grafos a serem utilizados
    int vertice = -1;
    scanf("%d", &vertice);

    int qtd_aresta = -1;
    scanf("%d", &qtd_aresta);

    if (vertice <= 0 || qtd_aresta <= 0)
        return NULL;

    // Cria um matriz chamada grafo usando alocação dinâmica
    int **grafo = cria_grafo(vertice);

    // if (zera_grafo(vertice, grafo) == -1)
    //     return NULL;

    int vertice_a = -1;
    int vertice_b = -1;
    int aresta = 0;

    // Lê as entradas do usuário e as coloca dentro do vetor grafo
    while(qtd_aresta > 0)
    {
        scanf("%d", &vertice_a);
        scanf("%d", &vertice_b);
        scanf("%d", &aresta);

        // Caso a leitura de alguma das variáveis dê erro, ou o usuário digite um número negativo, a função retorna erro
        if (vertice_a < 0 || vertice_b < 0)
            return NULL;

        // Caso o usuário resolva colocar o valor de um vertice inválido, a função retorna erro
        if (vertice_a == vertice_b || vertice_a >= vertice || vertice_b >= vertice)
            return NULL;

        grafo[vertice_a][vertice_b] = aresta;

        // Atualiza as variáveis para um novo ciclo de checagens
        vertice_a = -1;
        vertice_b = -1;
        qtd_aresta--;
    }

    // printa_grafo(vertice, grafo);

    return grafo;
}

int main(void)
{
    int **grafo = ler_grafo();

    printa_grafo(2, grafo);
}