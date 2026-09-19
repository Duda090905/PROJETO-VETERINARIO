#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "FILA.h"

/* Le uma linha com limite de tamanho e remove o '\n' do final */
void lerTexto(char *destino, int tamanho){
    if (fgets(destino, tamanho, stdin) == NULL){
        destino[0] = '\0';
        return;
    }
    size_t len = strlen(destino);
    if (len > 0 && destino[len-1] == '\n'){
        destino[len-1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); /* descarta o excesso */
    }
}


void cabecFilas(){
    printf("ID | Nome    | Espécie  | Idade | Data de Nascimento | Prioridade (Emergência = 0 || Normal = 1)\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}
void linhaPetFila(Nos *p){
    printf("%3d| %-28s | %-18s | %5d | %02d/%02d/%04d      | %d\n",
           p->info.ID, p->info.nome, p->info.especie, p->info.idade,
           p->info.nasc.dia, p->info.nasc.mes, p->info.nasc.ano, p->info.prioridade);
}


void cadastrarPet(Fila *E, Fila *N){
    system ("cls");
    char nome[y],especie[x];
    int idade,dia,mes,ano,prioridade,ID;
    printf("Tipo de atendimento (0=Emergência, 1=Normal): ");
    while (scanf("%d",&prioridade)!=1 || (prioridade!=0 && prioridade!=1)){
        while(getchar()!='\n');
        printf("Valor inválido. Digite 0 ou 1: ");
    }
    while(getchar()!='\n');

    printf("Nome (até %d): ", y-1);
    lerTexto(nome, sizeof(nome));
    printf("Espécie (até %d): ", x-1);
    lerTexto(especie, sizeof(especie));

    printf("Idade (inteiro): ");
    while (scanf("%d",&idade)!=1){
        while(getchar()!='\n');
        printf("Idade inválida. Tente de novo: ");
    }

    printf("Data de nascimento\n");
    printf("  Dia: ");
    while (scanf("%d",&dia)!=1 || dia<1 || dia>31){
        while(getchar()!='\n');
        printf("  Dia 1..31: ");
    }

    printf("  Mês: ");
    while (scanf("%d",&mes)!=1 || mes<1 || mes>12){
        while(getchar()!='\n');
        printf("  Mês 1..12: ");
    }

    printf("  Ano: ");
    while (scanf("%d",&ano)!=1 || ano<1900 || ano>2100){
        while(getchar()!='\n');
        printf("  Ano 1900..2100: ");
    }

    while(getchar()!='\n');

    if(prioridade < 1){
        ID = proximoID();
        printf("\nPet inserido na FILA DE EMERGÊNCIA.");
        insereCadastro(E, ID, nome, especie, idade, dia, mes, ano, prioridade);
        system("pause");
    }
    else{
        ID = proximoID();
        printf("\nPet inserido na FILA NORMAL.");
        insereCadastro(N, ID, nome, especie, idade, dia, mes, ano, prioridade);
        system("pause");
    }
}

void atenderPet(Fila *E, Fila *N, Fila *A){
    system ("cls");
    Nos *aux;
    if (VaziaFila(E) < 1){ // se VaziaFila < 1 -> Não esta vazio
        aux = RetiraCadastro(E);
    }
    else if (VaziaFila(N) < 1){
        aux = RetiraCadastro(N);
    }
    else {
        printf("\n\n\tNão há pets nas filas.");
        system("pause");
        return;
    }

    printf("\n=== ATENDIMENTO REALIZADO ===\n");
    printf("ID: %d\nNome: %s\nEspécie: %s\nIdade: %d\nPrioridade: %d\n",
           aux->info.ID, aux->info.nome, aux->info.especie, aux->info.idade, aux->info.prioridade);


           //Enfileira o pet na fila de Atendidos (A)
    insereCadastro(A,aux->info.ID, aux->info.nome, aux->info.especie, aux->info.idade,
                   aux->info.nasc.dia, aux->info.nasc.mes, aux->info.nasc.ano, aux->info.prioridade);
    free(aux); // libera a copia criada por RetiraCadastro
    system("pause");
}


void buscarPet(Fila *E, Fila *N, Fila *A){
   system ("cls");
    int modo;
    printf("Buscar por (1) ID, (2) Nome, (3) Ambos: ");
    while (scanf("%d",&modo)!=1 || modo<1 || modo>3){
        while(getchar()!='\n');
        printf("Opção inválida. 1/2/3: ");
    }
    while(getchar()!='\n');

    int ID=-1; char nome[y]={0};
    if (modo==1 || modo==3){
        printf("ID: ");
        scanf("%d",&ID);
        while(getchar()!='\n');
    }
    if (modo==2 || modo==3){
        printf("Nome (ou parte): ");
        lerTexto(nome, sizeof(nome));
    }

    int nada=0;
    for (Nos *p=E->ini; p!=NULL; p=p->prox){
        int ok = 1;
        if (modo==1 && p->info.ID!=ID) ok=0;
        if (modo==2 && strstr(p->info.nome, nome)==NULL) ok=0;
        if (modo==3 && (p->info.ID!=ID || strstr(p->info.nome, nome)==NULL)) ok=0;

        if (ok){
            printf("\nID: %d\nNome: %s\nEspécie: %s\nPrioridade: %d\nAtendido: %s\n",
                   p->info.ID, p->info.nome, p->info.especie,
                   p->info.prioridade, "Não");
            nada++;
        }
    }
    for (Nos *p=N->ini; p!=NULL; p=p->prox){
        int ok = 1;
        if (modo==1 && p->info.ID!=ID) ok=0;
        if (modo==2 && strstr(p->info.nome, nome)==NULL) ok=0;
        if (modo==3 && (p->info.ID!=ID || strstr(p->info.nome, nome)==NULL)) ok=0;

        if (ok){

            printf("\nID: %d\nNome: %s\nEspécie: %s\nPrioridade: %d\nAtendido: %s\n",
                   p->info.ID, p->info.nome, p->info.especie,
                   p->info.prioridade, "Não");
            nada++;
        }
    }
    for (Nos *p=A->ini; p!=NULL; p=p->prox){
        int ok = 1;
        if (modo==1 && p->info.ID!=ID) ok=0;
        if (modo==2 && strstr(p->info.nome, nome)==NULL) ok=0;
        if (modo==3 && (p->info.ID!=ID || strstr(p->info.nome, nome)==NULL)) ok=0;

        if (ok){

            printf("\nID: %d\nNome: %s\nEspécie: %s\nPrioridade: %d\nAtendido: %s\n",
                   p->info.ID, p->info.nome, p->info.especie,
                   p->info.prioridade, "Sim");
            nada++;
        }
    }
    if (nada == 0) {

        printf("\n\n\tNenhum pet encontrado.");
    }
    system("pause");
}


void relatorioFilas(Fila *E, Fila *N){
    system ("cls");
    cabecFilas();

    for (Nos *q=E->ini; q!=NULL; q=q->prox){
        Nos *n = buscaPorID(E->ini, q->info.ID);
        linhaPetFila(n);
    }

    for (Nos *q=N->ini; q!=NULL; q=q->prox){
        Nos *n = buscaPorID(N->ini, q->info.ID);
        linhaPetFila(n);
    }
    system("pause");
}


void mostrarProximo(Fila *E, Fila *N){

    system ("cls");
    if (VaziaFila(E) < 1){
        int ID = E->ini->info.ID;
        Nos *n = buscaPorID(E->ini, ID);
        if (n){
            printf("Nome: %s\nEspécie: %s\nTipo: Emergência\n", n->info.nome, n->info.especie);
            system("pause");
            return;
        }
    }
    if (!VaziaFila(N)){
        int ID = N->ini->info.ID;
        Nos *n = buscaPorID(N->ini, ID);
        if (n){
            printf("Nome: %s\nEspécie: %s\nTipo: Normal\n", n->info.nome, n->info.especie);
            system("pause");
            return;
        }
    }
    printf("\n\n\tNão há pets nas filas.");
    system("pause");
}


void relatorioAtendidos(Fila *A){
    system ("cls");

    if (VaziaFila(A) == 1 ){
        printf("\n\n\tNenhum pet atendido ainda.");
        system("pause");
        return;
    }
    printf("ID | Nome    | Espécie   | Idade | Prioridade(Emergência = 0 || Normal = 1)\n");
    printf("-----------------------------------------------------------------------------\n");
    for (Nos *a=A->ini; a!=NULL; a=a->prox){
        printf("%3d| %-28s | %-18s | %5d | %d\n",
               a->info.ID, a->info.nome, a->info.especie, a->info.idade,
               a->info.prioridade);
    }
    system("pause");
}


int menu(){
    int op;
    puts("\n==================== MENU ====================");
    puts("1 - Inserir Pet (Emergência/Normal)");
    puts("2 - Atender Pet (prioriza Emergência)");
    puts("3 - Buscar Pet por Nome e/ou ID");
    puts("4 - Relatório das filas (Emergência e Normal)");
    puts("5 - Mostrar próximo a ser atendido");
    puts("6 - Relatório dos atendidos");
    puts("7 - Finalizar");
    printf("Escolha: ");

    if (scanf("%d",&op)!=1)
    {
        while(getchar()!='\n');
        return -1;
    }
    while(getchar()!='\n');
    return op;
}

int main(){
    setlocale(LC_ALL,"Portuguese");

    Fila *emerg = CriaFila();
    Fila *normal = CriaFila();
    Fila *atendido = CriaFila();

    int op;
    do{
        system("cls");
        op = menu();
        switch(op){
            case 1: cadastrarPet(emerg, normal);                      break;
            case 2: atenderPet(emerg, normal, atendido);              break;
            case 3: buscarPet(emerg, normal, atendido);               break;
            case 4: relatorioFilas(emerg, normal);                    break;
            case 5: mostrarProximo(emerg, normal);                    break;
            case 6: relatorioAtendidos(atendido);                   break;
            case 7: printf("Encerrando...");system("pause");         break;
            default: printf("\n\n\tOpção inválida.");system("pause");break;
        }
    }while(op!=7);


    emerg  = liberaFila(emerg);
    normal = liberaFila(normal);
    atendido = liberaFila(atendido);

    return 0;
}
