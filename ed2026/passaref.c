// Passando parametro por referência

#include <stdio.h>

int fatorial(int x) {
    if(x>1)
        return x * fatorial(x-1);
    return 1;
}

int main() {
    int numero;

    printf("Entre com número: ");
    scanf("%d", &numero );

    printf("Fatorial de %d é %d\n", numero, fatorial(numero));

    printf("Endereço da variável numero: %ld\n",(long int) &numero);


}