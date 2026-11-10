#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#include "pmm.h"

#define MAX(X,Y) ((X > Y) ? X : Y)

int main()
{
    srand(time(NULL));
    char arq[50];
    strcpy(arq, "pmm3.txt");
    ler_dados(arq);
    //strcpy(arq, "");
    //testar_dados(arq);

    ordenar_objetos();
    //for (int j = 0; j < num_obj; j++)
    //    printf("%d  ", vet_ind_obj_ord[j]);

    Solucao sra, smm, spm, spmnd;
    heu_con_ale(sra);
    calcular_FO(sra);
    memcpy(&smm, &sra, sizeof(Solucao));
    memcpy(&spm, &sra, sizeof(Solucao));
    memcpy(&spmnd, &sra, sizeof(Solucao));

    printf("\n\nOR: %d\t", sra.fo);
    heu_bl_rand(sra, 3 * num_obj * num_moc);
    heu_bl_mm(smm);
    heu_bl_pm(spm);
    heu_bl_pm_nd(spmnd);

    printf("RA: %d\tMM: %d\tPM: %d\tND: %d\n", sra.fo, smm.fo,
           spm.fo, spmnd.fo);



/*
    Solucao sol, viz;
    heu_con_ale(sol);
    calcular_FO(sol);
    memcpy(&viz, &sol, sizeof(Solucao));
    gerar_vizinha(viz);
    calcular_FO(viz);
    escrever_sol(sol);
    escrever_sol(viz);


    /*
    clock_t h;
    double tempoA, tempoG, tempoAG;
    Solucao solA, solG, solAG;

    h = clock();
    for (int r = 0; r < 10000; r++)
        heu_con_ale(solA);
    tempoA = ((double)(clock() - h)) / CLOCKS_PER_SEC;

    h = clock();
    for (int r = 0; r < 10000; r++)
        heu_con_gul(solG);
    tempoG = ((double)(clock() - h)) / CLOCKS_PER_SEC;

    h = clock();
    for (int r = 0; r < 10000; r++)
        heu_con_ale_gul(solAG, 10);
    tempoAG = ((double)(clock() - h)) / CLOCKS_PER_SEC;

    calcular_FO(solA);
    calcular_FO(solG);
    calcular_FO(solAG);
    printf("FOA: %d\tTempo: %.5f\n", solA.fo, tempoA);
    printf("FOG: %d\tTempo: %.5f\n", solG.fo, tempoG);
    printf("FOAG: %d\tTempo: %.5f\n", solAG.fo, tempoAG);


    /*
    SolucaoBIN solB;
    memset(&solB, 0, sizeof(SolucaoBIN));
    solB.mat_sol[0][0] = 1;
    solB.mat_sol[0][1] = 1;
    //solB.mat_sol[1][0] = 1;
    solB.mat_sol[1][2] = 1;

    clock_t h;
    h = clock();
    for (int r = 0; r < 1000; r++)
        calcular_FOBIN(solB);
    double tempo = ((double)(clock() - h)) / CLOCKS_PER_SEC;
    printf("FO: %d\tTempo: %.5f\n", solB.fo, tempo);


    Solucao sol;
    sol.vet_sol[0] = 0;
    sol.vet_sol[1] = 0;
    sol.vet_sol[2] = 1;
    sol.vet_sol[3] = -1;

    h = clock();
    for (int r = 0; r < 1000; r++)
        calcular_FO(sol);
    tempo = ((double)(clock() - h)) / CLOCKS_PER_SEC;
    printf("FO: %d\tTempo: %.5f\n", sol.fo, tempo);


    for (int i = 0; i < num_moc; i++)
        for (int j = 0; j < num_obj; j++)
            solB.mat_sol[i][j] = rand() % 2;
    calcular_FOBIN(solB);
    //escrever_solBIN(solB);

    for (int j = 0; j < num_obj; j++)
        sol.vet_sol[j] = rand() % (num_moc + 1) - 1;
    calcular_FO(sol);
    //escrever_sol(sol);
    */

    return 0;
}


void heu_bl_rand(Solucao& s, const int iter)
{
    Solucao s_aux;
    INICIO : ;
    for (int i = 0; i < iter; i++)
    {
        memcpy(&s_aux, &s, sizeof(Solucao));
        gerar_vizinha(s_aux);
        calcular_FO(s_aux);
        if (s_aux.fo > s.fo)
        {
            memcpy(&s, &s_aux, sizeof(Solucao));
            goto INICIO;
        }
    }
}

void heu_rand(Solucao& s, const int iter) {
    Solucao sol_aux;
    INICIO : ; 
    for(int i = 0; i < iter; i++) {
        memcpy(&sol_aux, &s, sizeof(Solucao));
        gerar_vizinha(sol_aux);
        calcular_FO(sol_aux);
        if(sol_aux.fo > s.fo) {
            memcpy(&s, &sol_aux, sizeof(Solucao));
            goto INICIO;
        }
    }
}

void heu_bl_mm(Solucao& s)
{
    int mel_fo, mel_obj, mel_moc;
    mel_fo = s.fo;
    while (1)
    {
        int flag = 0;
        for (int j = 0; j < num_obj; j++)
        {
            int moc_ori = s.vet_sol[j];
            int fo_ori = s.fo;
            for (int i = -1; i < num_moc; i++)
            {
                if (moc_ori != i)
                {
                    s.vet_sol[j] = i;
                    calcular_FO(s);
                    if (s.fo > mel_fo)
                    {
                        mel_fo = s.fo;
                        mel_obj = j;
                        mel_moc = i;
                        flag = 1;
                    }
                }
            }
            s.vet_sol[j] = moc_ori;
            s.fo = fo_ori;
        }
        if (flag)
        {
            s.vet_sol[mel_obj] = mel_moc;
            s.fo = mel_fo;
        }
        else
            break;
    }
}

void heu_melhor_melhora(Solucao& s) {
    //percorre cada objeto
        //percorre cada mochila para o objeto 
        //troca a mochila do objeto na solucao original (copiada para se manter integra)
        //calcula fo com a mochila trocada
            //se melhorar a fo, salva em melhor_fo, melhor_objeto e melhor_mochila
        //volta para a mochila e fo original
        //passa para o proximo objeto e repete
        //depois de percorrer todas combinacoes possiveis, se mantem na que teve melhor melhora
        //recomeca
            //se nao melhorar apos todas combinacoes, e otimo local 
    int mel_fo, mel_obj, mel_moc;
    mel_fo = s.fo;
    while(1) {
        int flag = 0;
        for(int j = 0; j < num_obj; j++) {
            int moc_ori = s.vet_sol[j];
            int fo_ori = s.fo;
            for(int i = -1; i < num_moc; i++) {
                if(i != moc_ori) {
                    s.vet_sol[j] = i;
                    calcular_FO(s);
                    if(s.fo > mel_fo) {
                        mel_fo = s.fo;
                        mel_obj = j; 
                        mel_moc = i;
                        flag = 1;
                    }
                }
            }
            s.vet_sol[j] = moc_ori;
            s.fo = fo_ori;
        }
        if(flag) {
            s.vet_sol[mel_obj] = mel_moc;
            s.fo = mel_fo;
        } else break;
    }
}

void heu_bl_pm(Solucao& s)
{
    INICIO : ;
    int mel_fo = s.fo;
    for (int j = 0; j < num_obj; j++)
    {
        int moc_ori = s.vet_sol[j];
        int fo_ori = s.fo;
        for (int i = -1; i < num_moc; i++)
        {
            if (moc_ori != i)
            {
                s.vet_sol[j] = i;
                calcular_FO(s);
                if (s.fo > mel_fo)
                    goto INICIO;
            }
        }
        s.vet_sol[j] = moc_ori;
        s.fo = fo_ori;
    }
}

void heu_bl_pm_nd(Solucao& s)
{
    int vet_aux[MAX_OBJ];
    for (int j = 0; j < num_obj; j++)
        vet_aux[j] = j;

    INICIO : ;
    int mel_fo = s.fo;
    for (int j = 0; j < num_obj; j++)
    {
        int pos = j + rand() % (num_obj - j);
        int obj = vet_aux[pos];

        int moc_ori = s.vet_sol[obj];
        int fo_ori = s.fo;
        for (int i = -1; i < num_moc; i++)
        {
            if (moc_ori != i)
            {
                s.vet_sol[obj] = i;
                calcular_FO(s);
                if (s.fo > mel_fo)
                    goto INICIO;
            }
        }
        s.vet_sol[obj] = moc_ori;
        s.fo = fo_ori;

        int aux = vet_aux[j];
        vet_aux[j] = vet_aux[pos];
        vet_aux[pos] = aux;
    }
}



void gerar_vizinha(Solucao& s)
{
    int obj = rand() % num_obj;
    int moc;
    do
        moc = rand() % (num_moc + 1) - 1;
    while(moc == s.vet_sol[obj]);
    s.vet_sol[obj] = moc;
}

void heu_con_ale(Solucao& s)
{
    for (int j = 0; j < num_obj; j++)
        s.vet_sol[j] = rand() % (num_moc + 1) - 1;
}

void heu_con_gul(Solucao& s)
{
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int j = 0; j < num_obj; j++)
    {
        int obj = vet_ind_obj_ord[j];
        for (int i = 0; i < num_moc; i++)
        {
            if (vet_pes_obj[obj] + s.vet_pesos[i] <= vet_cap_moc[i])
            {
                s.vet_sol[obj] = i;
                s.vet_pesos[i] += vet_pes_obj[obj];
                break;
            }
        }
    }
}

void heu_con_ale_gul(Solucao& s, const double per_ale)
{
    int vet_aux[MAX_OBJ];
    memcpy(&vet_aux, &vet_ind_obj_ord, sizeof(vet_ind_obj_ord));
    int qtde = MAX(1, (per_ale / 100) * num_obj);
    for (int i = 0; i < qtde; i++)
    {
        int pos = i + rand() % (num_obj - i);
        int aux = vet_aux[i];
        vet_aux[i] = vet_aux[pos];
        vet_aux[pos] = aux;
    }
    // codigo da gulosa
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int j = 0; j < num_obj; j++)
    {
        int obj = vet_aux[j]; // troquei o vetor ordenado pelo embaralhado
        for (int i = 0; i < num_moc; i++)
        {
            if (vet_pes_obj[obj] + s.vet_pesos[i] <= vet_cap_moc[i])
            {
                s.vet_sol[obj] = i;
                s.vet_pesos[i] += vet_pes_obj[obj];
                break;
            }
        }
    }
}

void ordenar_objetos()
{
    for (int j = 0; j < num_obj; j++)
        vet_ind_obj_ord[j] = j;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int j = 0; j < num_obj - 1; j++)
        {
            if ((double)vet_val_obj[vet_ind_obj_ord[j]] / vet_pes_obj[vet_ind_obj_ord[j]] <
                (double)vet_val_obj[vet_ind_obj_ord[j + 1]] / vet_pes_obj[vet_ind_obj_ord[j + 1]])
            {
                int aux = vet_ind_obj_ord[j];
                vet_ind_obj_ord[j] = vet_ind_obj_ord[j + 1];
                vet_ind_obj_ord[j + 1] = aux;
                flag = 1;
            }
        }
    }
}














void calcular_FO(Solucao& s)
{
    s.fo = 0;
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));
    for (int j = 0; j < num_obj; j++)
    {
        int moc = s.vet_sol[j];
        if (moc == -1)
            continue;
        s.fo += vet_val_obj[j];
        s.vet_pesos[moc] += vet_pes_obj[j];
    }
    for (int i = 0; i < num_moc; i++)
        s.fo -= PESO_CAP * MAX(0, s.vet_pesos[i] - vet_cap_moc[i]);
}

void escrever_sol(Solucao& s)
{
    printf("\n\nFO: %d\n", s.fo);
    for (int j = 0; j < num_obj; j++)
        printf("%d ", s.vet_sol[j]);
}

void calcular_FOBIN(SolucaoBIN& s)
{
    s.fo = 0;
    for (int i = 0; i < num_moc; i++)
    {
        int peso = 0;
        for (int j = 0; j < num_obj; j++)
        {
            //if (s.mat_sol[i][j] == 1)
            //    s.fo += vet_val_obj[j];
            s.fo += vet_val_obj[j] * s.mat_sol[i][j];
            peso += vet_pes_obj[j] * s.mat_sol[i][j];
        }
        //if (peso > vet_cap_moc[i])
        //    s.fo -= PESO_CAP * (peso - vet_cap_moc[i]);
        s.fo -= PESO_CAP * MAX(0, peso - vet_cap_moc[i]);
    }
    //---
    for (int j = 0; j < num_obj; j++)
    {
        int qtd = 0;
        for (int i = 0; i < num_moc; i++)
            qtd += s.mat_sol[i][j];
        s.fo -= PESO_DUP * MAX(0, qtd - 1);
    }
}

void escrever_solBIN(SolucaoBIN& s)
{
    printf("\n\nFO: %d\n", s.fo);
    for (int i = 0; i < num_moc; i++)
    {
        for (int j = 0; j < num_obj; j++)
            printf("%d ", s.mat_sol[i][j]);
        printf("\n");
    }
}

void testar_dados(char* arq)
{
    FILE* f;
    if (strcmp(arq, "") == 0)
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d %d\n", num_obj, num_moc);
    for (int j = 0; j < num_obj; j++)
        fprintf(f, "%d ", vet_val_obj[j]);
    fprintf(f, "\n");
    for (int j = 0; j < num_obj; j++)
        fprintf(f, "%d ", vet_pes_obj[j]);
    fprintf(f, "\n");
    for (int i = 0; i < num_moc; i++)
        fprintf(f, "%d ", vet_cap_moc[i]);
    if (strcmp(arq, "") != 0)
        fclose(f);
}

void ler_dados(char* arq)
{
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_obj, &num_moc);
    for (int j = 0; j < num_obj; j++)
        fscanf(f, "%d", &vet_val_obj[j]);
    for (int j = 0; j < num_obj; j++)
        fscanf(f, "%d", &vet_pes_obj[j]);
    for (int i = 0; i < num_moc; i++)
        fscanf(f, "%d", &vet_cap_moc[i]);
    fclose(f);
}
