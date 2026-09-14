/* 
   DIRETIVAS DE PRÉ-PROCESSAMENTO (#include)
   Dizem ao compilador para carregar arquivos de cabeçalho padrão antes de compilar o código.
*/
#include <stdio.h>   // Standard Input/Output: fornece funções como printf e scanf
#include <stdlib.h>  // Standard Library: fornece malloc, free e a função qsort
#include <math.h>    // Math Library: fornece funções matemáticas como pow() e sqrt()

/*
   FUNÇÃO DE COMPARAÇÃO (Para o algoritmo de ordenação qsort)
   - int: Tipo de retorno. O qsort espera um número negativo, zero ou positivo.
   - comparar: Nome da função.
   - const void *a, *b: Ponteiros genéricos (void*) e protegidos contra modificação (const).
*/
int comparar(const void *a, const void *b) {
    /* 
       (double*)a: Converte o ponteiro genérico 'void*' para um ponteiro do tipo 'double*'.
       * (antes do parêntese): Operador de desreferenciação. Pega o valor real dentro do endereço.
    */
    double diff = (*(double*)a - *(double*)b);
    
    // if: Estrutura condicional ("se")
    // return: Devolve o resultado e encerra a função
    if (diff < 0) return -1; // Se o primeiro número for menor, retorna negativo
    if (diff > 0) return 1;  // Se o primeiro número for maior, retorna positivo
    return 0;                // Se forem iguais, retorna zero
}

/*
   FUNÇÃO PRINCIPAL (main)
   Porta de entrada obrigatória de qualquer programa em C.
*/
int main() {
    // DECLARAÇÃO DE VARIÁVEIS
    int n;             // Variável inteira para armazenar a quantidade N de elementos
    double *valores;   // O '*' indica um PONTEIRO para double. Guardará o endereço inicial do nosso vetor dinâmico
    
    // O '= 0.0' inicializa as variáveis para evitar "lixo de memória"
    double soma = 0.0, media = 0.0, mediana = 0.0;
    double soma_desvio_quad = 0.0, desvio_padrao = 0.0;
    double minimo, maximo;

    // LEITURA DO TAMANHO DA SÉRIE
    printf("Quantos números na sua série (N): "); // printf: Exibe o texto na tela
    
    /*
       - scanf: Lê dados do teclado.
       - "%d": Especificador de formato para ler um número INTEIRO.
       - &n: O '&' (comercial) extrai o endereço de memória de 'n' para que o scanf saiba onde salvar o valor.
       - != 1: Se o scanf não conseguir ler exatamente 1 número inteiro (ex: se o usuário digitar uma letra).
       - ||: Operador lógico OU (OR).
    */
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade inválida.\n"); // \n: Caractere especial para quebra de linha
        return 1; // Retornar qualquer número diferente de 0 indica erro ao Sistema Operacional
    }

    /*
       ALOCAÇÃO DINÂMICA DE MEMÓRIA
       - malloc: Solicita um bloco consecutivo de memória RAM na área do Heap.
       - sizeof(double): Descobre o tamanho em bytes que um 'double' ocupa (geralmente 8 bytes).
       - (double *): Faz a conversão (cast) do ponteiro genérico do malloc para o tipo que precisamos.
    */
    valores = (double *)malloc(n * sizeof(double));
    
    /* 
       ==: Operador de comparação de igualdade.
       NULL: Constante que representa um ponteiro nulo (vazio). Se for NULL, a memória acabou.
    */
    if (valores == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // ENTRADA DOS NÚMEROS DA SÉRIE
    printf("Entre com números:\n");
    
    /*
       for: Laço de repetição dividido em 3 partes:
       1) int i = 0: Inicializa o contador 'i' em zero.
       2) i < n: Condição de parada (roda enquanto 'i' for menor que 'n').
       3) i++: Incremento (soma +1 em 'i' a cada fim de volta).
    */
    for (int i = 0; i < n; i++) {
        printf("> ");
        /*
           - "%lf": Especificador de formato para ler um número do tipo DOUBLE (long float).
           - valores[i]: Acessa a posição 'i' do vetor.
           - &valores[i]: Passa o endereço de memória exato daquela posição para o scanf salvar o dado.
        */
        if (scanf("%lf", &valores[i]) != 1) {
            printf("Entrada inválida.\n");
            free(valores); // free: Libera a memória antes de fechar para evitar vazamento de memória
            return 1;
        }
        soma += valores[i]; // +=: Operador cumulativo. Equivale a: soma = soma + valores[i];
    }

    /*
       ORDENAÇÃO DO VETOR
       - qsort: Função embutida do C que ordena a lista usando QuickSort. Recebe:
         1) O vetor (valores), 2) O total de itens (n), 3) O tamanho de cada item, 4) A função de comparação.
    */
    qsort(valores, n, sizeof(double), comparar);

    // CÁLCULOS ESTATÍSTICOS BÁSICOS
    minimo = valores[0];       // Com o vetor ordenado, a posição 0 é obrigatoriamente o menor valor
    maximo = valores[n - 1];   // A última posição (n - 1) é o maior valor
    media = soma / n;          // '/': Operador de divisão

    // CÁLCULO DA MEDIANA
    // %: Operador de resto da divisão inteira. Se o resto por 2 for 0, o número N é PAR.
    if (n % 2 == 0) {
        // Se N for par, a mediana é a média dos dois valores centrais
        mediana = (valores[n / 2 - 1] + valores[n / 2]) / 2.0;
    } else {
        // Se N for ímpar, pega exatamente o valor do meio
        mediana = valores[n / 2];
    }

    // CÁLCULO DO DESVIO PADRÃO POPULACIONAL
    for (int i = 0; i < n; i++) {
        // pow(base, expoente): Eleva o desvio (valor - média) ao quadrado (2)
        soma_desvio_quad += pow(valores[i] - media, 2);
    }
    // sqrt: Calcula a raiz quadrada do somatório dividido por N
    desvio_padrao = sqrt(soma_desvio_quad / n);

    // IMPRESSÃO DOS RESULTADOS FORMATADOS
    // %.1f: Formata para exibir apenas 1 casa decimal
    printf("Valor mínimo: %.1f\n", minimo);
    printf("Valor Máximo: %.1f\n", maximo);
    
    // %.2f: Formata para exibir exatamente 2 casas decimais
    printf("Média: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);
    
    // %.13f: Formata para exibir com 13 casas decimais (conforme o exemplo do enunciado)
    printf("Desvio padrão: %.13f\n", desvio_padrao);

    // FINALIZAÇÃO E DESALOCAÇÃO
    free(valores); // Devolve a memória RAM que o malloc pegou de volta para o sistema operacional

    return 0; // Retorna 0 para dizer ao sistema que o programa rodou perfeitamente até o fim
}
