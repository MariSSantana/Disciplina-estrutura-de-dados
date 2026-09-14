// Usando strings

#include <stdio.h>

#define MAXIMOSTR 10

int main() {

    char cadcar[MAXIMOSTR];
    int i;


    printf("Qual o seu nome: ");
    fgets( cadcar, MAXIMOSTR, stdin);
    printf("\nAlo %s!\n\n", cadcar);

    printf("Qual o seu nome: ");
    scanf( "%s", cadcar);
    printf("\nAlo %s!\n\n", cadcar);

    printf("Qual o seu nome: ");
    for(i=0; i<9; i++) {
        cadcar[i] = getchar();
    }
    cadcar[i]='\0';
    printf("\nAlo %s!\n\n", cadcar);

}







