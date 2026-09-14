// Uso de "struct"

#include <stdio.h>
#include <stdlib.h>

int main(){
    long int n=0;
    int d,m,a;

    typedef struct DATA {
        short dia; // 1..31
        short mes; // 1..12
        short ano;
    } Data;

    Data d1;

    d1.ano = 1966;
    d1.mes = 8;
    d1.dia = 9;

    printf("Tamanho do tipo 'Data': %ld bytes\n", sizeof(Data) );

    Data vetorDatas[1000];

    printf("Tamanho do vetor de datas vetorDatas: %ld bytes\n", sizeof(vetorDatas) );

    Data *popNasc = NULL;

    printf("Entre com tamanho da população: ");
    scanf("%ld", &n);

    printf("Alocando espaço para %ld datas.\n", n);
    popNasc = malloc( n * sizeof(Data) );
    if(!popNasc){    // ERRO - retorna ponteiro NULL
        printf("ERRO de alocação de memória.\n");
    }

    printf("Tamanho de popNasc: %ld bytes\n", sizeof(popNasc) );

    Data *p;
    p = popNasc;

    printf("Entre com as datas\n ");
    for(int i=0; i<n; i++){
        printf("Dia: ");
        scanf("%d", &d);   
        printf("Mês: ");
        scanf("%d", &m); 
        printf("Ano: ");
        scanf("%d", &a); 
        printf("----- %ld -----\n", (long int) p);
        p->dia = d;   
        p->mes = m;
        p->ano = a;
        // popNasc[i].dia=d;
        // popNasc[i].mes = m;
        // popNasc[i].ano = a;
        p++;
    }

    free(popNasc);

}