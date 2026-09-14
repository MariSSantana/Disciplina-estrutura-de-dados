#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
    char cadstr[10];
    int i;

    struct termios old, new;
    char c;

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    for (i=0; i<9; i++) {
        c = getchar();
        if( c=='\n')
            break;
        cadstr[i] = c;
        printf("%c",c);
    }
    cadstr[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    printf("\nVocê teclou: %s\n", cadstr);
    return 0;
}
