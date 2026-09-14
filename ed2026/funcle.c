// Função para ler strings de tamanhos pré-definidos

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define TRUE 1

int funcle(char *ponde, int tamanho, int eco) {
    int i;
    char *p;

    struct termios old, new;
    char c;

    if( tamanho <1){
        printf("Tamanho inválido (<1).\n");
        return 0;
    }

    p = ponde;

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    for (i=0; i<tamanho-1; i++) {
        c = getchar();
        if( c=='\n')
            break;
        *p = c;
        p++;
        if(eco)
            printf("%c",c);
    }
    if(tamanho==1) {
        *p = getchar();
        if(eco)
            printf("%c",*p);
    }
    else
        *p = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return 1;
}


int main(){
    char nome[10];
    char c;

    printf("Qual o seu nome? ");

    funcle(nome, sizeof(nome), TRUE);

    printf("\nNome: %s\n", nome);

    printf("Está feliz (S/N)?");
    funcle(&c, 1, TRUE);

    printf("\nVocê digitou: %c\n", c);


}
