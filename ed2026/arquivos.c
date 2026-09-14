// Trabalhando com arquivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *fp;

    char s[] = "Esse é um teste.";
    char area[100];
    int tamlido=0;

    fp = fopen("/tmp/teste", "w");

    if(fp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }

    fwrite(s, strlen(s),1,fp);
    fputs("Qualquer string aqui.",fp);
    fputc('A', fp);
    fputc(66, fp);
    fclose(fp);

    strcpy( area, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    fp = fopen("/tmp/teste","r");
    tamlido = fread(area, 1, 99, fp);
    // area[tamlido]='\0';

    printf("String lido (%d bytes): |%s|\n", tamlido, area);

    strcpy( area, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    fseek(fp, 0, SEEK_SET);
    fgets(area,100,fp);
    printf("String lido pelo fgets: |%s|\n", area);

    fclose(fp);
}