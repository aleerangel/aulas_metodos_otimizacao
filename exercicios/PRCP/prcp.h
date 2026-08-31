#define MAX_PON 1000
#define MAX_POS 4

typedef struct tSolucao {
    int fo;
    int vet_sol[MAX_PON + 1];
} Solucao;

int num_pon;
int num_pos;
int vet_num_con_pos[MAX_PON * MAX_POS + 1];
int mat_con[MAX_PON * MAX_POS + 1][MAX_PON * MAX_POS + 1];


void ler_dados(char* arq);
void testar_dados(char* arq);
void escrever_solucao(Solucao& s, char* arq);
void calcular_fo(Solucao& s);