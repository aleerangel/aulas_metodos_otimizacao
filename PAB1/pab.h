#define MAX_NAV 100
#define MAX_BER 20
#define PES_PRAZO_NAV 100
#define PES_FEC_BER 100

typedef struct tSolucao{
    int fo;
    int mat_seq_ber[MAX_BER][MAX_NAV];
    int vet_qtd_ber[MAX_BER];
} Solucao;

int num_nav;
int num_ber;
int mat_tem_nav_ber[MAX_BER][MAX_NAV];
int vet_abe_ber[MAX_BER];
int vet_fec_ber[MAX_BER];
int vet_che_nav[MAX_NAV];
int vet_lim_nav[MAX_NAV];

void ler_dados(char* arq);
void testar_dados(char* arq);
void escrever_solucao(Solucao& s, char* arq);
void calcular_fo(Solucao& s);