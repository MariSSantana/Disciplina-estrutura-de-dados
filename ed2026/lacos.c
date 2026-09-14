// Os diferentes laços em C

#include <stdio.h>

int main() {

    printf("Com WHILE:\n");
    int i=0;
    while(i<10) {
        printf("%d\n",i);
        i++;
    }

    printf("Com FOR:\n");
    for(int j=0;j<10;j++)
        printf("%d\n",j);

    printf("Com DO WHILE:\n");
    i=0;
    do{
        printf("%d\n",i);
        i++;
    } while(i<10);
}
