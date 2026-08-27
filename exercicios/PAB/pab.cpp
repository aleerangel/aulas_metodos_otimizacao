#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "pab.h"

int main() {
    char arq[50];
    strcpy(arq, "i01.txt");
    ler_dados(arq);
    strcpy(arq, "teste1.txt");
    testar_dados(arq);
    Solucao sol;
    memset(&sol, 0, sizeof(sol));
    escrever_sol(sol, "");

    return 0;
}

void ler_dados(char* arq) {
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_nav, &num_ber);
    for(int k = 0; k < num_ber; k++) {
        for(int n = 0; n < num_nav; n++) {
            fscanf(f, "%d", &mat_tem_ate[k][n]);
        }
    }
    for(int k = 0; k < num_ber; k++) {
        fscanf(f, "%d %d", &vet_abe_ber[k], &vet_fec_ber[k]);
    }
    for(int n = 0; n < num_nav; n++) {
        fscanf(f, "%d", &vet_che_nav[n]);
    }
    for(int n = 0; n < num_nav; n++) {
        fscanf(f, "%d", &vet_lim_nav[n]);
    }

    fclose(f);
}

void testar_dados(char* arq) {
    FILE* f = fopen(arq, "w");
    fprintf(f, "%d %d\n", num_nav, num_ber);
    for(int k = 0; k < num_ber; k++) {
        for(int n = 0; n < num_nav; n++) {
            fprintf(f, "%d ", mat_tem_ate[k][n]);
        }
        fprintf(f, "\n");
    }
    for(int k = 0; k < num_ber; k++) {
        fprintf(f, "%d %d\n", vet_abe_ber[k], vet_fec_ber[k]);
    }
    for(int n = 0; n < num_nav; n++) {
        fprintf(f, "%d ", vet_che_nav[n]);
    }
    fprintf(f, "\n");
    for(int n = 0; n < num_nav; n++) {
        fprintf(f, "%d ", vet_lim_nav[n]);
    }

    fclose(f);
}

void escrever_sol(Solucao& s, char* arq) {
    FILE* f;
    if(strcmp(arq, "") == 0) {
        f = stdout;
    } else {
        f = fopen(arq, "w");
    }
    
    fprintf(f, "FO: %d\n", s.fo);
    for(int k = 0; k < num_ber; k++) {
        for(int n = 0; n < num_nav; n++) {
            fprintf(f, "%d ",s.mat_sol[k][n]);
        }
        fprintf(f, "\n");
    }

    if(strcmp(arq, "") != 0) {
        fclose(f);
    } 
}

void calcular_fo(Solucao& s) {

}
