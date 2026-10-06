#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include "pab.h"

#define MAX(A, B) ((A > B) ? A : B) 

int main() {
    srand(time(NULL));
    char arq[50];
    strcpy(arq, "i01.txt");
    ler_dados(arq);
    strcpy(arq, "teste1.txt");
    testar_dados(arq);
    Solucao sol;
    memset(sol.vet_seq_ber, -1, sizeof(sol.vet_seq_ber));
    memset(sol.vet_qtd_ber, 0, sizeof(sol.vet_qtd_ber));
    calcular_fo(sol);
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
        fprintf(f, "Berco %d: ", k + 1);
        for(int i = 0; i < s.vet_qtd_ber[k]; i++) {
            fprintf(f, "%d ", s.vet_seq_ber[k][i] + 1);
        }
        fprintf(f, "\n");
    }

    if(strcmp(arq, "") != 0) {
        fclose(f);
    } 
}

void calcular_fo(Solucao& s) {
    s.fo = 0;
    for(int k = 0; k < num_ber; k++) {
        int tempo = vet_abe_ber[k];
        for(int j = 0; j < s.vet_qtd_ber[k]; j++) {
            int nav = s.vet_seq_ber[k][j];
            if(tempo < vet_che_nav[nav]) {
                tempo = vet_che_nav[nav];
            }
            tempo += mat_tem_ate[k][nav];
            s.fo += tempo - vet_che_nav[nav];
            if(tempo > vet_lim_nav[nav]) {
                s.fo += PES_PRAZO_NAV * (tempo - vet_lim_nav[nav]);
            }
        }
        if(tempo > vet_fec_ber[k]) {
            s.fo += PES_FEC_BER * (tempo - vet_fec_ber[k]);
        }
    }
}

void heu_con_ale(Solucao& s) {
    //para cada navio, escolhe um berco aleatoriamente e insere ao final 
    memset(s.vet_qtd_ber, 0, sizeof(s.vet_qtd_ber));
    for(int n = 0; n < num_nav; n++) {
        int berco;
        do{
            berco = rand() % num_ber;
        } while (mat_tem_ate[berco][n] == 0);
        s.vet_seq_ber[berco][s.vet_qtd_ber[berco]] = n;
        s.vet_qtd_ber[berco]++;
    }
}

void ordenar_navios() {
    //ordena por horario de chegada
    for(int n = 0; n < num_nav; n++) {
        vet_nav_ord[n] = n;
    }
    int flag = 1;
    while(flag) {
        flag = 0;
        for(int j = 0; j < num_nav - 1; j++) {
            if(vet_che_nav[vet_nav_ord[j]] > vet_che_nav[vet_nav_ord[j + 1]]) {
                int aux = vet_nav_ord[j + 1];
                vet_nav_ord[j + 1] = vet_nav_ord[j];
                vet_nav_ord[j] = aux;
                flag = 1;
            }
        }
    }
}

void heu_con_gul(Solucao& s) {
    //aloca os navios por ordem de chegada de maneira sequencial nos bercos disponiveis
    memset(s.vet_qtd_ber, 0, sizeof(s.vet_qtd_ber));
    ordenar_navios();
    int berco_atual = 0;
    for(int n = 0; n < num_nav; n++) {
        while(mat_tem_ate[berco_atual][vet_nav_ord[n]] == 0) {
            berco_atual = (berco_atual + 1) % num_ber;
        }
        s.vet_seq_ber[berco_atual][s.vet_qtd_ber[berco_atual]] = vet_nav_ord[n];
        s.vet_qtd_ber[berco_atual]++;
        berco_atual = (berco_atual + 1) % num_ber;
    }
}

void heu_con_ale_gul(Solucao& s, const int per_ale) {
    memset(s.vet_qtd_ber, 0, sizeof(s.vet_qtd_ber));
    ordenar_navios();
    int vet_aux[MAX_NAV];
    memcpy(&vet_aux, &vet_nav_ord, sizeof(vet_nav_ord));
    int qtde = MAX(1, (per_ale / 100.0) * num_nav);
    for(int i = 0; i < qtde; i++) {
        int pos = i + rand() % (num_nav - i);
        int aux = vet_aux[i];
        vet_aux[i] = vet_aux[pos];
        vet_aux[pos] = aux;
    }
    int berco_atual = 0;
    for(int n = 0; n < num_nav; n++) {
        while(mat_tem_ate[berco_atual][vet_aux[n]] == 0) {
            berco_atual = (berco_atual + 1) % num_ber;
        }
        s.vet_seq_ber[berco_atual][s.vet_qtd_ber[berco_atual]] = vet_aux[n];
        s.vet_qtd_ber[berco_atual]++;
        berco_atual = (berco_atual + 1) % num_ber;
    }
}

void gerar_vizinha(Solucao& s) {
    //escolhe um berco aleatorio 
    int ber_ori;
    do {
        ber_ori = rand() % num_ber;
    } while (s.vet_qtd_ber[ber_ori] == 0); 
    //escolhe um navio aleatorio do berco
    int pos_nav = rand() % s.vet_qtd_ber[ber_ori];
    int nav = s.vet_seq_ber[ber_ori][pos_nav];
    //remove o navio do berco
    for(int i = pos_nav; i < s.vet_qtd_ber[ber_ori] - 1; i++) {
        s.vet_seq_ber[ber_ori][i] = s.vet_seq_ber[ber_ori][i + 1];
    }
    s.vet_qtd_ber[ber_ori]--;
    //escolhe outro berco aleatorio que possa atender o navio
    //se for escolhido o mesmo berco, verifica se o navio ja esta na ultima posicao
    int ber_des;
    do {
        ber_des = rand() % num_ber;
    } while (mat_tem_ate[ber_des][nav] == 0 || (ber_des == ber_ori && pos_nav == s.vet_qtd_ber[ber_des]));
    //insere o navio no final do berco 
    s.vet_seq_ber[ber_des][s.vet_qtd_ber[ber_des]] = nav;
    s.vet_qtd_ber[ber_des]++; 
}