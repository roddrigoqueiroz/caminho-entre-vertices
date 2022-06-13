#include <stdio.h>
#include <stdlib.h>

#define MAX 2

struct pilha {
    int topo;
    int elementos[MAX];
};

typedef struct pilha Pilha;

int CriaPilha(){
    Pilha *pilha;

    pilha = (Pilha *) malloc(sizeof(Pilha));

    // Testando se a alocação deu certo
    if(pilha != NULL){
        pilha -> topo = 0;
    };

    return pilha;
}

int Cheia(Pilha *pilha){
    // Ocorreu algum erro na criação da pilha
    if(pilha == NULL){
        return -1;
    }

    int pilhaCheia = pilha -> topo == MAX;

    if(pilhaCheia){
        return 1;
    } else {
        return 0;
    }

}

int Vazia(Pilha *pilha){

    // Ocorreu algum problema na criação da pilha
    if(pilha == NULL){
        return -1;
    }

    int pilhaVazia = pilha -> topo == 0;
    
    if( pilhaVazia ){
        return 1;
    } 
    else {
        return 0;
    }
}

int Empilha(Pilha* pilha, int elemento){

    // Ocorreu algum problema na criação da pilha
    if(pilha == NULL) return 0;
    
    // Se a pilha estiver cheia nao terá como empilhar
    if( Cheia(pilha) ) return 0;

    // Incrementando o topo da pilha 
    pilha -> topo++;
    
    // Colocando o elemento no topo
    pilha -> elementos[ pilha -> topo ] = elemento;
    
    return 1; 

}

int Desempilha(Pilha *pilha){

    if(pilha == NULL || pilha -> topo == 0){
        return 0;
    }

    pilha -> topo--;

    return 1;

}

int TamanhoPilha(Pilha* pilha) {
    if(pilha == NULL){
        return - 1;
    }
    else 
        return pilha -> topo;
}

void Destroi(Pilha *pilha){
    free(pilha);
}

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

    destroi_grafo(2, grafo);
}