// Biblioteca padrão de entrada e saída (para usar o printf)
#include <stdio.h>
// Biblioteca para alocação dinâmica de memória (para usar o malloc e free)
#include <stdlib.h>
// Biblioteca para manipulação de strings (não usada aqui, mas mantida do original)
#include <string.h>

// Define a estrutura de cada nó (elemento) da nossa Fila
typedef struct FILA {
    int valor;             // Guarda o dado inteiro deste nó
    struct FILA *proximo;  // Ponteiro que aponta para o próximo nó da fila
} Fila;                     // Cria o apelido "Fila" para a estrutura struct FILA

// Operação: enfileirar (Insere um novo elemento sempre no FINAL da fila)
void enfileirar(Fila **f, int valor) {
    Fila *novo; // Declara um ponteiro para o novo nó que será criado
    Fila *ptr;  // Declara um ponteiro auxiliar para navegar pela fila

    novo = malloc(sizeof(Fila)); // Aloca memória dinamicamente para o novo nó
    if (!novo) { // Se 'novo' for NULL, significa que o sistema ficou sem memória
        printf("Erro de alocação.\n"); // Exibe uma mensagem de erro na tela
        exit(-1);    // Encerra a execução do programa com código de erro
    }
    novo->valor = valor;     // Salva o valor recebido dentro do novo nó
    novo->proximo = NULL;    // Como ele será o último da fila, o próximo dele é NULL

    if (*f == NULL) {        // Se a fila estiver completamente vazia...
        *f = novo;           // ...o ponteiro da fila passa a apontar diretamente para ele
        return;              // Encerra a função mais cedo, pois o trabalho acabou
    }
    ptr = *f;                // Se não estava vazia, o ponteiro auxiliar começa no início
    while (ptr->proximo != NULL) // Enquanto não chegar no último elemento da fila...
        ptr = ptr->proximo;  // ...avança o ponteiro auxiliar para o próximo nó
    ptr->proximo = novo;     // O antigo último elemento agora aponta para o novo nó
}

// Operação: desenfileirar (Remove e retorna o elemento do INÍCIO da fila)
int desenfileirar(Fila **f) {
    Fila *p; // Declara um ponteiro temporário para guardar o nó que será removido
    int val; // Declara uma variável para guardar o valor do nó antes de apagá-lo

    if (*f == NULL) return -99999; // Se a fila estiver vazia, retorna um código de erro
    p = *f;    // O ponteiro temporário aponta para o primeiro elemento atual
    *f = p->proximo; // O início da fila agora passa a ser o segundo elemento

    val = p->valor; // Guarda o valor numérico que estava no nó que vai sumir
    free(p);        // Libera a memória do nó antigo da fila para o sistema operacional
    return val;     // Retorna o valor que acabou de ser retirado da fila
}

// Operação: filavazia (Verifica se a fila não possui nenhum elemento)
int filavazia(Fila *f) {
    return f == NULL; // Retorna 1 (verdadeiro) se for NULL, ou 0 (falso) caso contrário
}

// Operação: frente / peek (Apenas olha o primeiro da fila sem removê-lo)
int frente(Fila *f) {
    if (f == NULL) return -99999; // Se a fila estiver vazia, retorna o código de erro
    return f->valor; // Retorna o valor contido no primeiro elemento
}

// Função auxiliar para contar a quantidade de elementos na fila
int tamanho(Fila *f) {
    int tam = 0; // Inicializa o contador de tamanho em zero
    while (f) {  // Enquanto o ponteiro 'f' não for NULL (não chegar ao fim)...
        tam++;   // Incrementa em 1 o contador de elementos
        f = f->proximo; // Avança o ponteiro para analisar o próximo nó
    }
    return tam;  // Retorna a quantidade total de nós encontrados
}

// Função principal onde o programa começa a ser executado
int main() {
    Fila *fila = NULL; // Cria um ponteiro de Fila e inicializa como vazia (NULL)

    // Exibe se a fila está vazia no começo (vai imprimir "Sim")
    printf("A fila está vazia? %s\n", filavazia(fila) ? "Sim" : "Não");

    // Adiciona quatro elementos seguidos no final da fila (10, depois 20, 30, 40)
    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);
    enfileirar(&fila, 40);

    // Exibe se a fila está vazia agora (vai imprimir "Não")
    printf("A fila está vazia agora? %s\n", filavazia(fila) ? "Sim" : "Não");
    // Mostra qual é o primeiro elemento (vai imprimir 10) sem tirá-lo dali
    printf("Elemento na frente (peek): %d\n", frente(fila));

    // Remove e exibe os três primeiros da fila (vai tirar o 10, depois o 20, depois o 30)
    printf("Retirado: %d\n", desenfileirar(&fila));
    printf("Retirado: %d\n", desenfileirar(&fila));
    printf("Retirado: %d\n", desenfileirar(&fila));

    // Mostra quem sobrou na frente da fila (vai imprimir 40)
    printf("Elemento na frente após remoções: %d\n", frente(fila));

    // Adiciona mais dois elementos no fim da fila (50 e depois 60)
    enfileirar(&fila, 50);
    enfileirar(&fila, 60);

    // Loop que continua rodando enquanto a fila NÃO estiver vazia
    while (!filavazia(fila)) {
        // Remove e imprime o próximo elemento da vez (vai imprimir 40, 50 e 60)
        printf("Retirado: %d\n", desenfileirar(&fila));
    }

    return 0; // Informa ao sistema que o programa terminou perfeitamente
}
