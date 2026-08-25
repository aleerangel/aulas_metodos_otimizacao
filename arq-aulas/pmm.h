#define MAX_OBJ 500
#define MAX_MOC 50

const int PESO_CAP = 10;
const int PESO_DUP = 100;

typedef struct tSolucaoBIN{
    int mat_sol[MAX_OBJ][MAX_MOC];
    int fo;
}SolucaoBIN;

typedef struct tSolucao{
    int vet_pesos[MAX_MOC];
    int vet_sol[MAX_OBJ];
    int fo;
}Solucao;

int num_obj;
int num_moc;
int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];

void ler_dados(char* arq);
void testar_dados(char* arq);
void calcular_FOBIN(SolucaoBIN& s);
void escrever_solBIN(SolucaoBIN& s);
void calcular_FO(Solucao& s);
void escrever_sol(Solucao& s);