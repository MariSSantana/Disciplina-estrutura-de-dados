// Trabalhando com arquivos - le Cadastro.csv e descobre tamanho máximo da linha

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    FILE *fp;

    int maxtam=0, tam;
    int conta=0;
    char area[10000];

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    if(fp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }

    while( !feof(fp) ) {
        conta++;
        fgets(area, 10000, fp);
        tam = strlen(area);
        if( tam > maxtam ) maxtam=tam;
    }

    printf("Tamanho da maior linha: %d\nNúmero de linhas: %d", maxtam, conta);

}

