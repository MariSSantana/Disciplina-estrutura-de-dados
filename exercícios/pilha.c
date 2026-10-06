// Resolução EP2 - Pilha interativa com menu para o usuário e documentação detalhada
#include <stdio.h>   // Biblioteca padrão para entrada e saída de dados (printf, scanf)
#include <stdlib.h>  // Biblioteca padrão que contém as funções malloc e free

// Definição da estrutura que representará cada elemento (nó) da nossa Pilha
typedef struct PILHA {
    float valor;            // Variável para armazenar o dado numérico do nó
    struct PILHA *proximo;  // Ponteiro que guarda o endereço de memória do próximo elemento abaixo dele
} Pilha;                    // Renomeia a estrutura 'struct PILHA' simplesmente para 'Pilha'

// --- OPERAÇÃO PUSH (Insere um elemento sempre no topo) ---
// Usamos ponteiro para ponteiro (**p) porque precisamos alterar o endereço para onde a raiz aponta na main
void push(Pilha **p, float valor) {
    Pilha *novo; // Cria um ponteiro temporário para gerenciar o novo nó

    novo = malloc(sizeof(Pilha)); // Aloca memória dinamicamente no sistema para o tamanho de uma struct Pilha
    if(!novo) { // Verifica se o ponteiro 'novo' é nulo (caso o sistema fique sem memória)
        printf("\n[ERRO] Falha crítica de alocação de memória.\n"); // Exibe mensagem de erro crítico
        exit(-1); // Aborta a execução do programa imediatamente retornando o código de erro -1
    }
    
    novo->valor = valor; // Salva o valor digitado pelo usuário dentro do novo nó recém-criado
    novo->proximo = *p;  // O novo nó aponta para quem era o atual topo da pilha (faz a ligação encadeada)
    *p = novo;           // Atualiza o topo oficial da pilha na main para ser esse novo nó inserido
    
    printf("\nValor %.2f empilhado com sucesso!\n", valor); // Confirma a operação bem-sucedida para o usuário
}

// --- OPERAÇÃO POP (Remove e retorna o elemento que está no topo) ---
float pop(Pilha **p) {
    Pilha *temp; // Cria um ponteiro temporário para segurar o nó que será excluído da memória
    float val;   // Cria uma variável para salvar o número guardado no nó antes de excluí-lo

    if(*p == NULL) return -99999; // Se a pilha estiver vazia (topo apontando para NULL), retorna o código de erro
    
    temp = *p;          // Faz o ponteiro temporário apontar para o nó que está no topo atual
    *p = temp->proximo; // O topo oficial da pilha avança/desce para o próximo nó da lista encadeada

    val = temp->valor;  // Copia o valor numérico do nó antigo para a nossa variável de retorno
    free(temp);         // Libera o espaço de memória que o nó removido estava ocupando (evita vazamento de memória)
    return val;         // Retorna o valor numérico removido para quem chamou a função
}

// --- OPERAÇÃO PEEK (Apenas visualiza o elemento do topo sem removê-lo) ---
float peek(Pilha *p) {
    if(p == NULL) return -99999; // Se a pilha estiver vazia, retorna o código padrão de erro
    return p->valor;             // Apenas retorna o valor armazenado no nó do topo, mantendo a estrutura intacta
}

// --- FUNÇÃO AUXILIAR PARA EXIBIR A PILHA ---
void imprimirPilha(Pilha *p) {
    if(p == NULL) { // Verifica se a pilha passada como parâmetro está vazia
        printf("\nA pilha está vazia!\n"); // Informa ao usuário que não há elementos
        return; // Interrompe a execução da função e retorna para o menu
    }
    printf("\n--- ESTADO ATUAL DA PILHA ---\n"); // Cabeçalho visual da pilha
    while(p) { // Executa o laço de repetição enquanto o ponteiro de navegação 'p' não for nulo (NULL)
        printf("[ %.2f ]\n", p->valor); // Imprime o valor do nó atual formatado entre colchetes
        p = p->proximo; // Avança o ponteiro de navegação para o próximo elemento de baixo
    }
    printf("-----------------------------\n"); // Linha de fechamento visual da pilha
}

// --- FUNÇÃO PRINCIPAL DE CONTROLE (MENU INTERATIVO) ---
int main(){
    Pilha *pilha = NULL; // Declara o ponteiro base da nossa pilha iniciando como NULL (pilha vazia)
    int opcao;           // Variável para armazenar a opção do menu escolhida pelo usuário
    float valorDigitado; // Variável para receber temporariamente o número que o usuário digitar

    do { // Inicia o laço de repetição do menu principal (garante a execução pelo menos uma vez)
        printf("\n======= MENU DA PILHA ======="); // Exibe o título do menu interativo
        printf("\n1 - PUSH (Inserir elemento)");       // Opção 1: Empilhar
        printf("\n2 - POP (Remover do topo)");         // Opção 2: Desempilhar
        printf("\n3 - PEEK (Espiar o topo)");          // Opção 3: Olhar o topo
        printf("\n4 - Mostrar Pilha Completa");        // Opção 4: Visualizar toda a estrutura
        printf("\n0 - Sair");                          // Opção 0: Terminar o programa
        printf("\nEscolha uma opção: ");               // Solicita a entrada do usuário

        // CORREÇÃO: O espaço em " %d" limpa qualquer espaço ou caractere Enter pendente no terminal
        if (scanf(" %d", &opcao) != 1) {
            printf("\nEntrada inválida! Digite apenas números.\n");
            while(getchar() != '\n'); // Limpa completamente o buffer caso o usuário digite letras
            opcao = -1; // Força uma opção inválida para repetir o menu
            continue;
        }

        switch(opcao) { // Avalia qual opção foi selecionada pelo usuário no menu
            case 1: // Caso o usuário tenha escolhido PUSH
                printf("Digite o valor (float) para inserir: "); // Solicita o número float
                if (scanf(" %f", &valorDigitado) == 1) {
                    push(&pilha, valorDigitado);                    
                } else {
                    printf("\n[ERRO] Valor inválido. Digite um número decimal.\n");
                    while(getchar() != '\n'); // Limpa o buffer se o usuário digitar letras
                }
                break; // Sai do switch e volta para o início do loop do menu

            case 2: // Caso o usuário tenha escolhido POP
                valorDigitado = pop(&pilha); // Executa a remoção e armazena o retorno na variável
                if(valorDigitado == -99999) { // Se o retorno foi o código de erro, a pilha estava vazia
                    printf("\n[AVISO] A pilha está vazia! Não há o que desempilhar.\n"); // Informa o usuário
                } else { // Caso contrário, a remoção ocorreu com sucesso
                    printf("\nElemento desempilhado (POP): %.2f\n", valorDigitado); // Exibe o valor removido
                }
                break; // Sai do switch e volta para o início do loop do menu

            case 3: // Caso o usuário tenha escolhido PEEK
                valorDigitado = peek(pilha); // Chama a função que apenas espia o topo sem remover
                if(valorDigitado == -99999) { // Se retornar o código de erro, a estrutura está vazia
                    printf("\n[AVISO] A pilha está vazia!\n"); // Alerta o usuário
                } else { // Caso contrário, exibe o valor encontrado no topo
                    printf("\nElemento no topo atual (PEEK): %.2f\n", valorDigitado); // Mostra o topo
                }
                break; // Sai do switch e volta para o início do loop do menu

            case 4: // Caso o usuário tenha escolhido mostrar toda a pilha
                imprimirPilha(pilha); // Chama a função que exibe todos os nós formatados
                break; // Sai do switch e volta para o início do loop do menu

            case 0: // Caso o usuário escolha encerrar o programa
                printf("\nEncerrando o programa... Liberando memória restante.\n"); // Exibe aviso de encerramento
                while(pop(&pilha) != -99999); // Executa um laço desempilhando tudo para garantir que nenhum nó fique perdido na RAM
                break; // Sai do switch para que a condição de parada encerre o loop

            default: // Caso o usuário digite um número que não esteja mapeado nas opções
                printf("\nOpção inválida! Tente novamente.\n"); // Avisa sobre a digitação incorreta
        }
    } while(opcao != 0); // O loop continuará rodando infinitamente enquanto o usuário não digitar 0

    return 0; // Finaliza a função main com sucesso retornando 0 para o sistema operacional
}
