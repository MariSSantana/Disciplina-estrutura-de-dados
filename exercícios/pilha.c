// Biblioteca padrão de entrada e saída, necessária para usar a função printf
#include <stdio.h>
// Biblioteca para alocação de memória e controle do sistema (malloc, free e exit)
#include <stdlib.h>
// Biblioteca para manipulação de strings (mantida do código original da aula)
#include <string.h>

// Definição da estrutura que representa cada nó (elemento) dentro da nossa lista
typedef struct NO {
    float valor;           // Variável do tipo float que armazena o dado numérico do nó
    struct NO *proximo;    // Ponteiro que aponta para o endereço do próximo nó da lista
} No;                      // Define o apelido "No" para simplificar a criação de variáveis

// --- OPERAÇÕES DA FILA SOLICITADAS PELO EXERCÍCIO ---

// Operação: enfileirar (Insere um novo elemento sempre no FINAL da lista encadeada)
// Recebe um ponteiro para ponteiro (**f) para poder modificar o início da fila se necessário
void enfileirar(No **f, float valor) {
    No *novo; // Declaração de um ponteiro auxiliar para criar o novo nó
    No *ptr;  // Declaração de um ponteiro auxiliar para navegar pela lista existente

    novo = malloc(sizeof(No)); // Solicita ao sistema memória dinamicamente para o novo nó
    if (!novo) { // Verifica se 'novo' é NULL, o que significa falta de memória no sistema
        printf("Erro de alocação de memória.\n"); // Exibe uma mensagem de erro na tela
        exit(-1);    // Encerra imediatamente o programa com um código de falha (-1)
    }

    novo->valor = valor; // Atribui o número float recebido ao campo 'valor' do novo nó
    novo->proximo = NULL; // Como este nó entrará no fim, o próximo dele deve apontar para NULL   

    if (*f == NULL) {  // Verifica se o ponteiro que indica o começo da fila está vazio (NULL)
        *f = novo;     // Se estiver vazia, o início da fila passa a apontar direto para o novo nó
        return;        // Finaliza a execução da função mais cedo, pois a inserção acabou
    }

    ptr = *f; // Se a fila não estava vazia, o ponteiro auxiliar começa a busca do início (*f)
    while (ptr->proximo != NULL) { // Laço que se repete até encontrar o nó cujo próximo seja NULL
        ptr = ptr->proximo;        // Avança o ponteiro auxiliar para o próximo nó da lista
    }
    
    ptr->proximo = novo; // O antigo último nó agora deixa de apontar para NULL e aponta para o novo nó
}

// Operação: desenfileirar (Remove e retorna o elemento localizado no INÍCIO da lista)
// Recebe um ponteiro para ponteiro (**f) para poder atualizar o início da fila após a remoção
float desenfileirar(No **f) {
    No *p;     // Declara um ponteiro temporário para segurar o nó que será deletado
    float val; // Declara uma variável para salvar o dado numérico antes de apagar o nó

    if (*f == NULL) { // Verifica se a fila está vazia antes de tentar remover
        return -99999.0; // Retorna um número sentinela que indica código de erro para fila vazia
    }
    
    p = *f;          // O ponteiro temporário 'p' recebe o endereço do primeiro elemento atual
    *f = p->proximo; // O ponteiro real do início da fila avança e assume o endereço do segundo nó

    val = p->valor;  // Transfere o dado numérico float do nó removido para a variável 'val'
    free(p);         // Libera o espaço de memória ocupado por aquele nó antigo de volta ao sistema
    return val;      // Retorna o valor float que acabou de ser retirado da fila
}

// Operação: filavazia (Verifica se a fila possui ou não algum elemento)
int filavazia(No *f) {
    return f == NULL; // Retorna 1 (verdadeiro) se o ponteiro for NULL, ou 0 (falso) caso contrário
}

// Operação: frente / peek (Permite visualizar o dado do início da fila sem removê-lo)
float frente(No *f) {
    if (f == NULL) { // Verifica se a fila está vazia antes de acessar o dado
        return -99999.0; // Retorna o código sentinela de erro indicando que não há dados
    }
    return f->valor; // Retorna o número que está salvo dentro do primeiro nó da fila
}

// Função auxiliar da aula para medir a quantidade total de elementos na lista
int len(No *p) {
    int conta = 0; // Inicializa a variável contadora com o valor zero
    if (p == NULL) return 0; // Se a listas estiver vazia, retorna zero de imediato
    do { // Inicia um bloco de repetição que executa pelo menos uma vez
        conta++; // Adiciona mais 1 unidade ao contador de elementos
        p = p->proximo; // Move o ponteiro para o próximo nó da sequência
    } while (p); // O loop continua rodando enquanto o ponteiro 'p' for diferente de NULL
    return conta; // Retorna o total acumulado de nós encontrados na lista
}

// Função principal, ponto onde o programa inicia a execução no computador
int main() {
    No *fila = NULL; // Declara o ponteiro base da fila e o inicializa como vazio (NULL)

    // Testa se a função filavazia funciona na fila recém-criada (vai imprimir "Sim")
    printf("A fila está inicialmente vazia? %s\n", filavazia(fila) ? "Sim" : "Não");

    // Executa inserções na fila passando o endereço do ponteiro (&fila) e os dados float
    enfileirar(&fila, 10.5); // Insere o valor 10.5 (se torna o primeiro)
    enfileirar(&fila, 20.0); // Insere o valor 20.0 no final
    enfileirar(&fila, 35.7); // Insere o valor 35.7 no final
    enfileirar(&fila, 40.0); // Insere o valor 40.0 no final

    // Verifica se a fila mudou de estado com as inserções (vai imprimir "Não")
    printf("Fila está vazia após inserções? %s\n", filavazia(fila) ? "Sim" : "Não");
    // Imprime a quantidade de elementos que foram inseridos com sucesso (deve dar 4)
    printf("Quantidade de elementos na fila: %d\n", len(fila));
    
    // Testa a operação frente (peek) que deve apenas ler o primeiro dado (vai exibir 10.50)
    printf("Primeiro elemento da fila (frente): %.2f\n", frente(fila));

    // Executa e testa as remoções da fila (Devem sair na ordem correta de entrada: FIFO)
    printf("Item removido: %.2f\n", desenfileirar(&fila)); // Remove e exibe o 10.5
    printf("Item removido: %.2f\n", desenfileirar(&fila)); // Remove e exibe o 20.0

    // Verifica quem herdou o primeiro lugar da fila após as duas remoções (deve ser 35.70)
    printf("Nova frente após remoções: %.2f\n", frente(fila)); 

    // Imprime um cabeçalho estético para indicar o esvaziamento total no terminal
    printf("\n--- Esvaziando a Fila ---\n");
    while (!filavazia(fila)) { // Enquanto a função filavazia retornar falso (0), continua o loop
        // Remove o elemento da vez e o imprime imediatamente na tela (exibe 35.70 e depois 40.00)
        printf("Item removido: %.2f\n", desenfileirar(&fila));
    }

    return 0; // Retorna o código 0 para indicar que o programa finalizou com absoluto sucesso
}
