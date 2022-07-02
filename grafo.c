/*
Alunos:

Daniel de Souza Cordeiro, 12111BSI244
Emanuel Henrique Vieira Dias, 12111BSI218,
Rodrigo Queiroz Neves, 12111BSI220
*/

#include <stdio.h>
#include <stdlib.h>

// O topo desta pilha começa em -1. Pois quando formos usar empilha, a informação inserida será em elementos[topo + 1]
struct pilha
{
    int topo; // topo é onde está o topo da minha pilha
    int *elementos; // elementos é o array com todos os elementos empilhados
    int tamanho; // tamanho é o tamanho da pilha
};

typedef struct pilha Pilha;

// PROTÓTIPOS DAS FUNÇÕES

// FUNÇÕES PARA MANIPULAR O GRAFO
int **ler_grafo(int *qtd_vertice, int *qtd_aresta);
void printa_grafo(int qtd_vertice, int **grafo);
int zera_grafo(int qtd_vertice, int **grafo);
void destroi_grafo(int qtd_vertice, int **grafo);
int **cria_grafo(int qtd_vertice);

// FUNÇÕES PARA MANIPULAR A PILHA
void destroi(Pilha *pilha);
int desempilha(Pilha *pilha, int *elementoDesempilhado);
int empilha(Pilha* pilha, int elemento);
int vazia(Pilha *pilha);
int cheia(Pilha *pilha);
Pilha *criaPilha(int qtd_arestas);
void printa_pilha(Pilha *pilha);

// FUNÇÕES PARA CHECAR A EXISTÊNCIA DE CAMINHO
int existe_caminho(int v_saida, int v_chegada, int qtd_vertice, int qtd_arestas, int **grafo);
int proximo_vertice(int qtd_vertice, int *v_saida, int **grafo);

int main(void)
{
    // No algoritmo devo empilhar todos os caminhos que forem vizinhos de N.
    // Para algo ser vizinho de N, tenho que grafo[N][i] != 0
    // Posso colocar essa condição dentro de um for com um empilha lá dentro.

    int qtd_vertice, qtd_arestas;

    int **grafo = ler_grafo(&qtd_vertice, &qtd_arestas);

    int v_saida, v_chegada; // Vertices de saída e chegada
    scanf("%d", &v_saida);
    scanf("%d", &v_chegada);

    int resultado = existe_caminho(v_saida, v_chegada, qtd_vertice, qtd_arestas, grafo);
    printf("%d\n", resultado);

    destroi_grafo(qtd_vertice, grafo);
    return 0;
}

int proximo_vertice(int qtd_vertice, int *v_saida, int **grafo)
{
    // Esta função se baseia no algoritmo indicado no trabalho, que funciona colocando todos
    // os vizinhos de um vértice na pilha e depois retirando o elemento do topo.
    // O problema deste algoritmo - e consequentemente desta função - é que caso um vértice possua apenas um vizinho
    // e este vizinho leve para o vértice de destino, a função - assim como o algoritmo - diz que não existe o próximo vértice,
    // uma vez que ele foi retirado da pilha no algoritmo e na função o contador nunca chegará a 2.

    int j;
    int contador = 0;
    // Percorre a base de dados buscando 2 arestas para pegar o índice da 2ª, uma vez que a primeira
    // foi retirada pelo desempilha e o indice dela não me é útil
    for (j = qtd_vertice - 1; j >= 0; j--)
    {
        // Checa se existe uma aresta na posição grafo[i][j] e atualiza o contador
        if (grafo[*v_saida][j] != 0)
        {
            contador++;
        }
        if (contador == 2)
        {
            *v_saida = j;
            return 1; // Deu certo
        }
    }
    return 0; // Deu errado. Não tem proximo qtd_vertice
}

// Esta função está limitada a buscar um caminho por vértices que tenham mais de um vizinho
int existe_caminho(int v_saida, int v_chegada, int qtd_vertice, int qtd_arestas, int **grafo)
{
    // Checa se os vértices são valores válidos
    if (v_saida <= 0 || v_chegada <= 0)
        return -1;
    if (v_saida > qtd_vertice || v_chegada > qtd_vertice)
        return -1;

    Pilha *pilha = criaPilha(qtd_arestas);
    if (pilha == NULL)
        return -2;

    int j;
    int desempilhado = -1;
    int custo_caminho = 0;
    int flag = 0;
    // Ajustando os valores dos vértices para manipular arrays
    v_saida--;
    v_chegada--;

    // Faço uma copia do vértice de saída para poder lembrar de qual vértice saí, caso não consiga achar
    // um caminho de primeira
    const int copia_v_saida = v_saida;

    empilha(pilha, v_saida);
    // Começa o loop direto, pois a pilha já inicia vazia
    do
    {
        // Percorre a base de dados buscando uma aresta
        for (j = 0; j < qtd_vertice; j++)
        {
            if (grafo[v_saida][j] != 0)
            {
                // Empilha a aresta
                empilha(pilha, j);
                flag = 1;
            }
            if (j == v_chegada && grafo[v_saida][j] != 0)
            {
                // Encontrou o custo_caminho requisitado
                desempilha(pilha, &desempilhado);
                custo_caminho += grafo[v_saida][desempilhado];
                destroi(pilha);
                return custo_caminho;
            }
        }
        if (flag == 0)
        {
            // Recomeço a procurar pelo próximo vértice na pilha
            if (desempilha(pilha, &desempilhado) == 0)
            {
                destroi(pilha);
                return -1; // Não há caminho, a pilha está vazia
            }
            v_saida = desempilhado;
            // Essa linha de código não garante que eu volte para o começo do meu programa e siga a partir dali.
            // Isso porquê, posso ter um vértice que não tem vizinhos e que o seu predecessor (o vértice anterior) não seja vizinho
            // do vértice de saída.
            // Eu tenho que garantir de alguma forma que o retorno seja feito de forma adequada, resultando numa soma correta.
            custo_caminho = grafo[copia_v_saida][desempilhado];
        }
        if (flag == 1)
        {
            desempilha(pilha, &desempilhado);
            custo_caminho += grafo[v_saida][desempilhado];
            v_saida = desempilhado;
            flag = 0;
        }
    } while(1);

    destroi(pilha);
    return -1; // Deu errado. Não há caminho.
}

//
//
// FUNÇÕES QUE TRATAM A PILHA //
//
//

void printa_pilha(Pilha *pilha)
{
    // Printa a pilha como se fosse uma coluna
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
    if(pilha == NULL)
        return NULL;

    // A variável "tamanho" é a quantidade de arestas que o usuário inputou para mim.
    // É importante que a pilha comporte no máximo todas as arestas, assim o algoritmo de busca consegue
    // funcionar como foi planejado e a pilha não ficará sem espaço e nem desperdiçará muita memória.

    pilha -> tamanho = tamanho;
    pilha -> elementos = malloc(tamanho * sizeof(int));
    pilha -> topo = -1;

    return pilha;
}

int cheia(Pilha *pilha)
{
    // Ocorreu algum erro na criação da pilha
    if(pilha == NULL)
        return -1;

    if(pilha -> topo == (pilha -> tamanho) - 1)
        return 1; // A pilha está cheia, True
    else
        return 0; // A pilha não está cheia, False

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
    // Checa se os valores são válidos
    if(pilha == NULL || vazia(pilha) == 1)
        return 0; // Desempilha deu errado

    // Pega o elemento do topo da pilha
    *elementoDesempilhado = pilha -> elementos[pilha -> topo];

    // Decrementando o topo da pilha
    pilha -> topo = pilha -> topo - 1;

    return 1;

}

void destroi(Pilha *pilha)
{
    free(pilha -> elementos);
    free(pilha);
}

//
//
// FUNÇÕES QUE TRATAM O GRAFO //
//
//

// Na prática esta função cria uma matriz quadrada de tamanho vértice usando alocação dinâmica
int **cria_grafo(int qtd_vertice)
{
    // Aloca memória para um ponteiro que guardará vértices de tamanho int * (ponteiro pra inteiro)
    int **grafo = malloc(qtd_vertice * sizeof(int *));
    if (grafo == NULL)
        return NULL;

    // Aloca memória para um ponteiro para inteiro de tamanho vértice
    int i;
    for (i = 0; i < qtd_vertice; i++)
    {
        grafo[i] = malloc(qtd_vertice * sizeof(int));
        if (grafo[i] == NULL)
            return NULL;
    }

    return grafo;
}

void destroi_grafo(int qtd_vertice, int **grafo)
{
    int i;
    for (i = 0; i < qtd_vertice; i++)
    {
        // Libera cada vetor alocado para grafo
        free(grafo[i]);
    }
    // Libera o vetor de vetores grafo
    free(grafo);

    return;
}

int zera_grafo(int qtd_vertice, int **grafo)
{
    // Checa se o vértice ou grafo são válidos
    if (qtd_vertice <= 0 || grafo == NULL)
        return -1;

    // Zera o grafo
    int i, j;
    for (i = 0; i < qtd_vertice; i++)
    {
        for (j = 0; j < qtd_vertice; j++)
        {
            grafo[i][j] = 0;
        }
    }

    return 1;
}

void printa_grafo(int qtd_vertice, int **grafo)
{
    int i, j;

    // Checa se o vértice ou grafo são válidos
    if (qtd_vertice <= 0 || grafo == NULL)
        return;

    // Printa o grafo na tela como uma matriz
    printf("\n");
    for (i = 0; i < qtd_vertice; i++)
    {
        for (j = 0; j < qtd_vertice; j++)
        {
            printf("%d ", grafo[i][j]);
        }

        printf("\n");
    }
}

int **ler_grafo(int *qtd_vertice, int *qtd_aresta)
{
    // Inicia os vertices, arestas e grafos a serem utilizados
    *qtd_vertice = -1;
    scanf("%d", qtd_vertice);

    *qtd_aresta = -1;
    scanf("%d", qtd_aresta);

    if (*qtd_vertice <= 0 || *qtd_aresta <= 0)
        return NULL;

    // Cria um matriz chamada grafo usando alocação dinâmica
    int **grafo = cria_grafo(*qtd_vertice);

    if (zera_grafo(*qtd_vertice, grafo) == -1)
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
        if (vertice_a <= 0 || vertice_b <= 0)
            return NULL;

        // Caso o usuário resolva colocar o valor de um vertice inválido, a função retorna erro
        if (vertice_a == vertice_b || vertice_a > *qtd_vertice || vertice_b > *qtd_vertice)
            return NULL;

        // Coloca as arestas nas posições correspondentes do grafo
        grafo[vertice_a - 1][vertice_b - 1] = aresta;

        // Atualiza as variáveis para um novo ciclo de checagens
        vertice_a = -1;
        vertice_b = -1;
        copia_qtd_aresta--;
    }

    return grafo;
}
