#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <memory.h>
#include "pab.h"

int main() {
    char arq[50];
    strcpy(arq, "i01.txt");
    ler_dados(arq);
    strcpy(arq, "");
    testar_dados(arq);

    return 0;
}

void ler_dados(char* arq) {
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_nav, &num_ber);
    for(int k = 0; k <num_ber; k++) {
        for(int n = 0; n < num_nav; n++) {
            fscanf(f, "%d", &mat_tem_nav_ber[k][n]);
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
    FILE* f;
    if(strcmp(arq, "") == 0) {
        f = stdout;
    } else {
        f = fopen(arq, "w");
    }
    fprintf(f, "%d %d\n", num_nav, num_ber);
    for(int k = 0; k <num_ber; k++) {
        for(int n = 0; n < num_nav; n++) {
            fprintf(f, "%d ", mat_tem_nav_ber[k][n]);
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
    if(f != stdout) fclose(f);
}

void escrever_solucao(Solucao& s, char* arq) {
    FILE* f;
    if(strcmp(arq, "") == 0) {
        f = stdout;
    } else {
        f = fopen(arq, "w");
    }   
    fprintf(f, "FO: %d\n", s.fo);
    for(int k = 0; k < num_ber; k++) {
        fprintf(f, "Berco %d: ", k + 1);
        for(int i = 0; i < s.vet_qtd_ber[k]; i++) {
            fprintf(f, "%d ", s.mat_seq_ber[k][i] + 1);
        }
    }
    if(f != stdout) fclose(f);
}

void calcular_fo(Solucao& s) {
    s.fo = 0;
    for(int k = 0; k < num_ber; k++) {
        int tempo = vet_abe_ber[k];
        for(int i = 0; i < s.vet_qtd_ber[k]; i++) {
            if(vet_che_nav[i] > tempo) {
                tempo = vet_che_nav[i];
            }
            tempo += mat_tem_nav_ber[k][i];
            s.fo += tempo - vet_che_nav[i];
            if(tempo > vet_lim_nav[i]) {
                s.fo += PES_PRAZO_NAV * (tempo - vet_lim_nav[i]);
            }
        }
        if(tempo > vet_fec_ber[k]) {
            s.fo += PES_FEC_BER * (tempo - vet_fec_ber[k]);
        }
    }
}