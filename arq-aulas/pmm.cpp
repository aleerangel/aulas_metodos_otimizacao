#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pmm.h"

int main() {
    char arq[50];
    strcpy(arq, "pmm3.txt");
    ler_dados(arq);
    strcpy(arq, "teste.txt");
    testar_dados(arq);
    return 0;
}

void ler_dados(char* arq) {
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_obj, &num_moc);
    for(int j = 0; j < num_obj; j++) {
        fscanf(f, "%d", &vet_val_obj[j]);
    }
    for(int j = 0; j < num_obj; j++) {
        fscanf(f, "%d", &vet_pes_obj[j]);
    }
    for(int i = 0; i < num_moc; i++) {
        fscanf(f, "%d", &vet_cap_moc[i]);
    }
    fclose(f);
}

void testar_dados(char* arq) {
    FILE* f;
    if(strcmp(arq, "") == 0) {
        f = stdout;
    } else {
        f = fopen(arq, "w");
    }
    fprintf(f, "%d %d\n", num_obj, num_moc);
    for(int j = 0; j < num_obj; j++) {
        fprintf(f, "%d ", vet_val_obj[j]);
    }
    fprintf(f, "\n");
    for(int j = 0; j < num_obj; j++) {
        fprintf(f, "%d ", vet_pes_obj[j]);
    }
    fprintf(f, "\n");
    for(int i = 0; i < num_moc; i++) {
        fprintf(f, "%d ", vet_cap_moc[i]);
    }
    if(strcmp(arq, "") != 0) {
        fclose(f);
    }
}