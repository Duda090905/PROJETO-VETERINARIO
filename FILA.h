#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <string.h>
#define y 50
#define x 30

/* FUN��ES DE MANIPULA��O DE PFILA

Fila* CriaFila()  CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA EST� VAZIA RETORNA 1 QUANDO EST� VAZIA

void InsereFila (Fila* f, int v) INSER��O

int RetiraFila (Fila* f) REMO��O

Fila* liberaFila (Fila* f) LIBERA A FILA

void imprimeFila (Fila* f)IMPRIME A FILA
*/
typedef struct {

int dia, mes,ano;

}Data;

typedef struct {
    int ID;
    char nome[y];
    char especie[x];
    int idade;
    Data nasc;          /* Data vem do seu FILA.h (dia, mes, ano) */
    int prioridade;     /* 0 = Emergência, 1 = Normal */
} Pet;

typedef struct nos
{
    Pet info;
    struct nos *prox;
}Nos;

typedef struct fila
{
    Nos * ini;
    Nos * fim;
} Fila;


int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}


Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* ins_fim (Nos *fim, int ID, char nome[], char especie[], int idade, int dia, int mes, int ano, int prioridade)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->info.ID = ID;
    strcpy(p->info.nome, nome);
    strcpy(p->info.especie, especie);
    p->info.idade = idade;
    p->info.nasc.dia = dia;
    p->info.nasc.mes = mes;
    p->info.nasc.ano = ano;
    p->info.prioridade = prioridade;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista n�o estava vazia */
    fim->prox = p;
    return p;
}

void insereCadastro (Fila* f, int ID, char nome[], char especie[], int idade, int dia, int mes, int ano, int prioridade)
{
    f->fim = ins_fim(f->fim, ID, nome, especie, idade, dia, mes, ano, prioridade);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Nos* retira_ini (Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

Nos* RetiraCadastro (Fila* f)
{
    Nos *v = (Nos*)malloc(sizeof(Nos));
    v->info.ID = f->ini->info.ID;
    strcpy(v->info.nome, f->ini->info.nome);
    strcpy(v->info.especie, f->ini->info.especie);
    v->info.idade = f->ini->info.idade;
    v->info.nasc.dia = f->ini->info.nasc.dia;
    v->info.nasc.mes = f->ini->info.nasc.mes;
    v->info.nasc.ano = f->ini->info.nasc.ano;
    v->info.prioridade = f->ini->info.prioridade;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimeFila (Fila* f)
{
    Nos* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%d - ",q->info.ID);
    }
    printf("\n");
}


Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q!=NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

/* “Ficha” do pet */
Nos* buscaPorID(Nos *L, int ID){
    for (Nos *p=L; p!=NULL; p=p->prox)
        if (p->info.ID==ID) return p;
    return NULL;
}

/* Gera IDs unicos e sequenciais (1, 2, 3...) para todos os pets,
   independente da fila em que forem cadastrados */
int proximoID(){
    static int ultimoID = 0;
    return ++ultimoID;
}

#endif // FILA_H_INCLUDED

