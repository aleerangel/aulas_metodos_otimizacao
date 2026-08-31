#define MAX_NAV 100
#define MAX_BER 20

typedef struct tSolucao{
    int vet_seq_ber[MAX_BER][MAX_NAV];
    int vet_qtd_ber[MAX_BER];
    int fo; 
} Solucao;

int num_nav;
int num_ber;
int mat_tem_ate[MAX_BER][MAX_NAV];
int vet_abe_ber[MAX_BER];
int vet_fec_ber[MAX_BER];
int vet_che_nav[MAX_NAV];
int vet_lim_nav[MAX_NAV];

void ler_dados(char* arq);
void testar_dados(char* arq);
void escrever_sol(Solucao& s, char* arq);
void calcular_fo(Solucao& s);