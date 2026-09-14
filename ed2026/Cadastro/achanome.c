// Trabalhando com arquivos - le Cadastro.csv 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"

#define MAXLIN 1000

char *pegacampo(char *a, int i){
    char *ptr, *aux;
    int ncpo=0;
    aux = a;

    if(*aux!='"') {
        printf("ERRO - não sei o que aconteceu...\n");
        exit(-1);
    }

    while(1){
        aux++;
        ptr = aux;
        while(*aux!='"' && *aux!='\0') aux++;
        *aux='\0';
        if(ncpo==i)
            return ptr;
        aux++;
        while(*aux!='"' && *aux!='\0') aux++;
        if(*aux=='\0') return NULL;
        ncpo++;
    }

}

int main() {

    FILE *fp;

    int maxtam=0, tam;
    int conta=0;
    char area[MAXLIN];
    char query[100];

    char *p;

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    if(fp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }

    printf("Entre com parte do nome: ");
    scanf("%s", query);

    while( !feof(fp) ) {
        fgets(area, MAXLIN, fp);
        p = pegacampo(area, NOME);
        
        if( strstr(p, query) ) {
	    printf("-----------------------------------------\n");
            printf("%s\n", p);
            printf("%s\n", pegacampo(area, DESCRICAO_CARGO));
            printf("%s\n", pegacampo(area, ORG_LOTACAO));
            printf("%s\n\n", pegacampo(area, ATIVIDADE));
        }

    }
}

