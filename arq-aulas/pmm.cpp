#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "pmm.h"

int main() {
    char arq[50];
    strcpy(arq, "pmm1.txt");
    ler_dados(arq);
    strcpy(arq, "teste.txt");
    testar_dados(arq);
    
    SolucaoBIN solB;
    memset(&solB, 0, sizeof(SolucaoBIN));
    solB.mat_sol[0][0] = 1;
    solB.mat_sol[0][1] = 1;
    solB.mat_sol[1][0] = 1;
    solB.mat_sol[1][2] = 1;
    calcular_FOBIN(solB);
    escrever_solBIN(solB);

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

void escrever_solBIN(SolucaoBIN& s) {
    printf("\nFO: %d\n", s.fo);
    for(int i = 0; i < num_moc; i++) {
        for(int j = 0; j < num_obj; j++) {
            printf("%d ", s.mat_sol[i][j]);
        }
        printf("\n");
    }
}

void calcular_FOBIN(SolucaoBIN& s) {
    s.fo = 0;
    for(int i = 0; i < num_moc; i++) {
        for(int j = 0; j < num_obj; j++) {
            s.fo += vet_val_obj[j] * s.mat_sol[i][j];
        }
    }
}