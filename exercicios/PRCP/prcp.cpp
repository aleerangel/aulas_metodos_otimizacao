#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "prcp.h"

int main() {
    char arq[50];
    strcpy(arq, "inst1.txt");
    ler_dados(arq);
    strcpy(arq, "teste.txt");
    testar_dados(arq);
    return 0;
}

void ler_dados(char* arq) {
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d", &num_pon);
    fscanf(f, "%d", &num_pos);
    for(int n = 1; n <= num_pon; n++){
        for(int m = 1; m <= num_pos; m++) {
            fscanf(f, "%d", &vet_num_con_pos[(n - 1) * num_pos + m]);
            for(int i = 1; i <= vet_num_con_pos[(n - 1) * num_pos + m]; i++) {
                fscanf(f, "%d", &mat_con[(n - 1) * num_pos + m][i]);
            }
        }
    }
    fclose(f);
}

void testar_dados(char* arq) {
    FILE* f;
    if(strcmp(arq, "") == 0) {
        f = stdout;
    } else f = fopen(arq, "w");
    fprintf(f, "%d\n", num_pon);
    fprintf(f, "%d\n",num_pos);
    for(int n = 1; n <= num_pon; n++){
        for(int m = 1; m <= num_pos; m++) {
            fprintf(f, "%d\n", vet_num_con_pos[(n - 1) * num_pos + m]);
            for(int i = 1; i <= vet_num_con_pos[(n - 1) * num_pos + m]; i++) {
                fprintf(f, "%d ", mat_con[(n - 1) * num_pos + m][i]);
            }
            fprintf(f, "\n");
        }
    }
    if(strcmp(arq, "") != 0) fclose(f);
}

void escrever_solucao(Solucao& s, char* arq) {
    FILE* f;
    if(strcmp(arq, "") == 0) {
        f = stdout;
    } else f = fopen(arq, "w");
    fprintf(f, "FO: %d", s.fo);
    for(int n = 1; n <= num_pon; n++) {
        fprintf(f, "%d ", s.vet_sol[n]);
    }
    if(strcmp(arq, "") != 0) fclose(f);
}

void calcular_fo(Solucao& s) {
    s.fo = num_pon;
    for(int n = 1; n <= num_pon; n++) {
        int id = (n - 1) * num_pos + s.vet_sol[n];
        for(int m = 1; m <= vet_num_con_pos[id]; m++) {
            if(s.vet_sol[(mat_con[id][m] - 1) / num_pos + 1] == (mat_con[id][m] - 1) % num_pos + 1) {
                s.fo --;
                break;
            }
        }
    }
}
