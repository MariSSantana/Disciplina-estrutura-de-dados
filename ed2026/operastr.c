// Fazendo operações com strings

#include <stdio.h>
#include <string.h>

#define MAXIMOSTR 10

int main() {

    char cadcar[MAXIMOSTR];
    int i;

    printf("Qual o seu nome: ");
    fgets( cadcar, MAXIMOSTR, stdin);

    for(i=0; i<MAXIMOSTR; i++) {
        if(cadcar[i]=='\n') {
            cadcar[i]='\0';
            break;
        }
    }

    // isso:
    for(i=0;i<=MAXIMOSTR && cadcar[i]!='\0';i++);
    // e isso
    i=0;
    while(i<=MAXIMOSTR && cadcar[i]!='\0') i++;

    // equivale a:
    i = strlen(cadcar);

    printf("\nAlo %s!\nSeu nome tem %d caracteres\n", cadcar, i);


}
