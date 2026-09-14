// Trabalhando com ponteiros

#include <stdio.h>

int main() {

    char vet[20];
    int dia=12345;

    int *p=NULL;

    p = &dia;

    printf("valor em pint: \t%d\n", *p);

    printf("Tamanho vet: %ld\n ", sizeof(vet));
    printf("Tamanho &vet: %ld\n ", sizeof(&vet));

    printf("Tamanho dia: %ld\n ", sizeof(dia));
    printf("Tamanho &dia: %ld\n ", sizeof(&dia));
  
    printf("Valor em &dia %ld\n", (long int) &dia );

    printf("Valor em vet %ld\n",  (long int) vet );
    printf("Valor em &vet %ld\n",  (long int) &vet );

    p = 0;
    printf("valor em pint: \t%d", *p);
}
