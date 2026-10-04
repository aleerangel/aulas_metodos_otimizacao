#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include "pmm.h"

#define MAX(X, Y) ((X > Y) ? X : Y)

int main() {
    ler_dados("pmm1.txt");
    Solucao sol, viz;
    heu_con_ale(sol);
    calcular_FO(sol);
    memcpy(&viz, &sol, sizeof(Solucao));
    gerar_vizinha(viz);
    calcular_FO(viz);
    escrever_sol(sol);
    escrever_sol(viz);

    return 0;
}

void ler_dados(char* arq) {
    srand(time(NULL));
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

void calcular_FOBIN(SolucaoBIN& s) {
    s.fo = 0;
    for(int i = 0; i < num_moc; i++) {
        int peso = 0;
        for(int j = 0; j < num_obj; j++) {
            s.fo += vet_val_obj[j] * s.mat_sol[i][j];
            peso += vet_pes_obj[j] * s.mat_sol[i][j];
        }
        s.fo -= PESO_CAP * MAX(0, peso - vet_cap_moc[i]);
    }

    
    for(int j = 0; j < num_obj; j++) {
        int qtd = 0;
        for(int i = 0; i < num_moc; i++) {
            qtd += s.mat_sol[i][j];
        }
        s.fo -= PESO_DUP * MAX(0, qtd - 1);
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

void calcular_FO(Solucao& s) {
    s.fo = 0;
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));

    for(int j = 0; j < num_obj; j++) {
        int moc = s.vet_sol[j];
        if(moc == -1) continue;
        s.fo += vet_val_obj[j];
        s.vet_pesos[moc] += vet_pes_obj[j];
    }

    for(int i = 0; i < num_moc; i++) {
        s.fo -= PESO_CAP * MAX(0, s.vet_pesos[i] - vet_cap_moc[i]);
    } 
}

void escrever_sol(Solucao& s) {
    printf("\nFO: %d\n", s.fo);
    for(int j = 0; j < num_obj; j++) {
        printf("%d ", s.vet_sol[j]);
    }
    printf("\n");   
}

void gerar_vizinha(Solucao& s) {
    int obj = rand() % num_obj;
    int moc;
    do {
        moc = rand() % (num_moc + 1) - 1;
    } while (moc == s.vet_sol[obj]);
    s.vet_sol[obj] = moc;
}


void heu_con_ale(Solucao& s) {
    for(int j = 0; j < num_obj; j++) {
        s.vet_sol[j] = rand() % (num_moc + 1) - 1;
    }
}

void heu_con_gul(Solucao& s) {
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for(int j = 0; j < num_obj; j++) {
        int obj = vet_ind_obj_ord[j];
        for(int i = 0; i < num_moc; i++) {
            if(vet_pes_obj[j] + s.vet_pesos[i] <= vet_cap_moc[i]) {
                s.vet_sol[obj] = i;
                s.vet_pesos[i] += vet_pes_obj[j];
                break;
            }
        }
    }
}

void heu_con_ale_gul(Solucao& s, const int per_ale) {
    int vet_aux[MAX_OBJ];
    memcpy(&vet_aux, &vet_ind_obj_ord, sizeof(vet_ind_obj_ord));
    int qtde = MAX(1, (per_ale / 100.0) * num_obj);
    for(int i = 0; i < qtde; i++) {
        int pos = i + rand() % (num_obj - i);
        int aux = vet_aux[i];
        vet_aux[i] = vet_aux[pos];
        vet_aux[pos] = aux;
    }
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for(int j = 0; j < num_obj; j++) {
        int obj = vet_aux[j];
        for(int i = 0; i < num_moc; i++) {
            if(vet_pes_obj[j] + s.vet_pesos[i] <= vet_cap_moc[i]) {
                s.vet_sol[obj] = i;
                s.vet_pesos[i] += vet_pes_obj[j];
                break;
            }
        }
    }
}

void ordenar_objetos() {
    for(int j = 0; j < num_obj; j++) {
        vet_ind_obj_ord[j] = j;
    }
    int flag = 1;
    while(flag) {
        flag = 0;
        for(int j = 0; j < num_obj - 1; j++) {
            if((double)vet_val_obj[vet_ind_obj_ord[j]] / vet_pes_obj[vet_ind_obj_ord[j]] < (double)vet_val_obj[vet_ind_obj_ord[j + 1]] / vet_pes_obj[vet_ind_obj_ord[j + 1]]) {
                int aux = vet_ind_obj_ord[j]; 
                vet_ind_obj_ord[j] = vet_ind_obj_ord[j + 1];
                vet_ind_obj_ord[j + 1] = aux;
                flag = 1;
            }
        }
    }
}