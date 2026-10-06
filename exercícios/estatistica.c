/* 
   DIRETIVAS DE PRÉ-PROCESSAMENTO (#include)
   Dizem ao compilador para carregar arquivos de cabeçalho padrão antes de compilar o código.
*/
#include <stdio.h>   // Standard Input/Output: fornece funções como printf e scanf
#include <stdlib.h>  // Standard Library: fornece malloc, free e a função qsort
#include <math.h>    // Math Library: fornece funções matemáticas como pow() e sqrt()

/*
   FUNÇÃO DE COMPARAÇÃO (Para o algoritmo de ordenação qsort)
*/
int comparar(const void *a, const void *b) {
    double diff = (*(double*)a - *(double*)b);
    if (diff < 0) return -1; 
    if (diff > 0) return 1;  
    return 0;                
}

/*
   FUNÇÃO PRINCIPAL (main)
*/
int main() {
    // DECLARAÇÃO DE VARIÁVEIS
    int n;             
    double *valores;   
    
    double soma = 0.0, media = 0.0, mediana = 0.0;
    double soma_desvio_quad = 0.0, desvio_padrao = 0.0;
    double minimo, maximo;

    // LEITURA DO TAMANHO DA SÉRIE
    printf("Quantos números na sua série (N): "); 
    
    /*
       CORREÇÃO NO SCANF: Adicionado um espaço antes do %d (" %d") para descartar 
       qualquer quebra de linha ('\n') ou lixo deixado no terminal.
    */
    if (scanf(" %d", &n) != 1 || n <= 0) {
        printf("Quantidade inválida. Digite apenas números inteiros maiores que 0.\n"); 
        return 1; 
    }

    /*
       ALOCAÇÃO DINÂMICA DE MEMÓRIA
    */
    valores = (double *)malloc(n * sizeof(double));
    
    if (valores == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // ENTRADA DOS NÚMEROS DA SÉRIE
    printf("Entre com os %d números da sua série:\n", n);
    
    for (int i = 0; i < n; i++) {
        printf("Número %d de %d > ", i + 1, n);
        
        /*
           CORREÇÃO NO SCANF: Adicionado o espaço antes do %lf (" %lf").
           Se o usuário acidentalmente apertar Enter sozinho ou deixar espaços, 
           o programa irá ignorar a sujeira e esperará o número real ser digitado.
        */
        if (scanf(" %lf", &valores[i]) != 1) {
            printf("\n[ERRO] Entrada inválida detectada.\n");
            
            // Limpa o buffer de sujeiras (como letras) caso o usuário tenha digitado errado
            while(getchar() != '\n'); 
            
            // Decrementa o índice para forçar o usuário a digitar novamente a mesma posição
            i--; 
            continue; 
        }
        soma += valores[i]; 
    }

    /*
       ORDENAÇÃO DO VETOR
    */
    qsort(valores, n, sizeof(double), comparar);

    // CÁLCULOS ESTATÍSTICOS BÁSICOS
    minimo = valores[0];       
    maximo = valores[n - 1];   
    media = soma / n;          

    // CÁLCULO DA MEDIANA
    if (n % 2 == 0) {
        mediana = (valores[n / 2 - 1] + valores[n / 2]) / 2.0;
    } else {
        mediana = valores[n / 2];
    }

    // CÁLCULO DO DESVIO PADRÃO POPULACIONAL
    for (int i = 0; i < n; i++) {
        soma_desvio_quad += pow(valores[i] - media, 2);
    }
    desvio_padrao = sqrt(soma_desvio_quad / n);

    // IMPRESSÃO DOS RESULTADOS FORMATADOS
    printf("\n======= RESULTADOS =======\n");
    printf("Valor mínimo: %.1f\n", minimo);
    printf("Valor Máximo: %.1f\n", maximo);
    printf("Média: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);
    printf("Desvio padrão: %.13f\n", desvio_padrao);

    // FINALIZAÇÃO E DESALOCAÇÃO
    free(valores); 

    return 0; 
}
