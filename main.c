#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no
{
    int vaga;
    char nome [30];
    char placa[8];
    int hora,min;
    struct no *anterior;
    struct no *proximo;
} noptr;

float valor_arrecadado = 0.00;

void insere_lista(noptr **inifunc, noptr *novo, int vaga, char nome[],char placa[], int hora, int min)
{
    novo->vaga = vaga;
    strcpy(novo->placa,placa);
    strcpy(novo->nome,nome);
    novo->hora = hora;
    novo->min = min;
    noptr *aux;

    if(*inifunc==NULL)
    {
        novo->proximo = NULL;
        novo->anterior = NULL;
        *inifunc = novo;
    }
    else if(strcmp((*inifunc)->nome,novo->nome) > 0)
    {
        novo->proximo = *inifunc;
        (*inifunc)->anterior = novo;
        *inifunc = novo;
    }
    else
    {
        aux = *inifunc;
        while (aux->proximo && strcmp(novo->nome,aux->proximo->nome) >= 0)
            aux = aux->proximo;
        novo->proximo = aux->proximo;
        if(aux->proximo)
            aux->proximo->anterior = novo;
        novo->anterior = aux;
        aux->proximo = novo;
    }
}

void remover(noptr **lista, int num)
{
    noptr *aux, *remover = NULL;
    int hora_saida,min_saida;
    int min_total=0,horas_total=0;
    float reais;
    do{
    printf("Insira o Horario de saida.\nFormato(hh mm)\n::");
    scanf("%d %d",&hora_saida,&min_saida);
    }while(hora_saida >= 24 || hora_saida < 0 || min_saida >=60 || min_saida < 0);
    if(*lista)
    {
        if((*lista)->vaga == num)
        {
            remover = *lista;
            *lista = remover->proximo;
            if(*lista)
                (*lista)->anterior = NULL;
        }
        else
        {
            aux = *lista;
            while(aux->proximo && aux->proximo->vaga != num)
                aux = aux->proximo;
            if(aux->proximo)
            {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                if(aux->proximo)
                    aux->proximo->anterior = aux;
            }
        }
        if(hora_saida > remover->hora)
            horas_total = 60 * (hora_saida - remover->hora) ;
        else
            horas_total = 60 * (remover->hora - hora_saida) ;

        if(min_saida > remover->min)
            min_total = min_saida - remover->min;
        else
            min_total = remover->min - min_saida;
        reais = 0.1333 * (min_total + horas_total) ;

        free(remover);
        printf("\nTotal a pagar: R$%.2f\n",reais);
        valor_arrecadado = valor_arrecadado + reais;
    }
    return;
}

void print_reverso(noptr *inifunc)
{
    if(inifunc == NULL)
    {
        printf("\nLista vazia!\n");
        return;
    }
    noptr *p;
    p = inifunc;

    while(p->proximo)
    {
        p = p->proximo;
    }
    while(p!=inifunc->anterior){
        printf("\nNome do dono: %s",p->nome);
        printf("\nVaga estacionada: [%d]",p->vaga);
        printf("\nPlaca do carro: %s", p->placa);
        printf("\nHora de entrada: %d:%d",p->hora,p->min);
        printf("\n-------------------------------");
        p = p->anterior;
    }

}


int checa_vaga(noptr *inifunc, int vaga)
{
    if(inifunc == NULL)
    {
        return 0;
    }
    noptr *p;
    p=inifunc;
    while(p)
    {
        if(p->vaga == vaga)
            {
                printf("Vaga Ocupada.\n");
                return 1;
            }
        p = p->proximo;
    }
    return 0;

}

void lista_todos(noptr *inifunc)
{
    if(inifunc == NULL)
    {
        printf("\nLista vazia!\n");
        return;
    }
    noptr *p;
    p=inifunc;
    while(p)
    {
        printf("\nVaga estacionada: [%d]",p->vaga);
        printf("\nNome do dono: %s",p->nome);
        printf("\nPlaca do veiculo: %s", p->placa);
        printf("\nHora de entrada: %d:%d",p->hora,p->min);
        printf("\n-------------------------------");
        p = p->proximo;
    }
}

noptr *cria_no()
{
    noptr *info=(struct no *)malloc(sizeof(noptr));
    if(!info)
    {
        printf("\nSem memoria!!");
        return;
    }
    return info;
}

void main()
{
    int recebe=1;
    int op,cont=0;
    char nome[30];
    char placa[8];
    int hora,min,vaga;
    noptr *inicio;
    inicio = NULL;
    do
    {
        printf("\n1 - Inserir veiculo no estacionamento.");
        printf("\n2 - Mostrar em Ordem Crescente(A-Z).");
        printf("\n3 - Mostrar em Ordem Decrescente(Z-A).");
        printf("\n4 - Remover veiculo do estacionamento.");
        printf("\n5 - [TestDrive] Insere Ordenado");
        printf("\n6 - [TestDrive] Remover");
        printf("\n0 - Sair.");
        printf("\nValor total arrecadado R$%.2f",valor_arrecadado);
        printf("\n\n Digite uma opcao: ");
        scanf("%d", &recebe);
        printf("\n\n");
        switch(recebe)
        {
        case 1:
            setbuf(stdin,NULL);
            printf("Nome:");
            fgets(nome,29,stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Placa:");
            fgets(placa,8,stdin);
            placa[strcspn(placa, "\n")] = 0;
            do{
            printf("Insira o Horario de Entrada.\nFormato(hh mm)\n::");
            scanf("%d %d",&hora, &min);
            }while(hora >= 24 || hora < 0 || min>=60 || min < 0);
            do{
                printf("Vaga:");
                scanf("%d",&vaga);
            }while(checa_vaga(inicio,vaga) != 0);
            insere_lista(&inicio,cria_no(),vaga,nome,placa,hora,min);
            break;
        case 2:
            lista_todos(inicio);
            break;
        case 3:
            print_reverso(inicio);
            break;
        case 4:
            lista_todos(inicio);
            if (inicio)
            {
                printf("\nInsira a vaga a ser removida: ");
                scanf("%d",&vaga);
                remover(&inicio,vaga);
            }
            break;
        case 5:
            insere_lista(&inicio,cria_no(),0,"Bruno","AAA1234",20,30);
            printf("\nInseriu: 0,Bruno, AAA1234, 20:30");
            insere_lista(&inicio,cria_no(),1,"Alberto","BBB1234",20,30);
            printf("\nInseriu: 1,Alberto, BBB1234, 20:30");
            insere_lista(&inicio,cria_no(),2,"Caio","CCC1234",20,30);
            printf("\nInseriu: 2,Caio, CCC1234, 20:30");
            insere_lista(&inicio,cria_no(),3,"Acriziomar","DDD1234",20,30);
            printf("\nInseriu: 3,Acriziomar, DDD1234, 20:30");
            insere_lista(&inicio,cria_no(),4,"Danilo","EEE1234",20,30);
            printf("\nInseriu: 4,Danilo, EEE1234, 20:30");
            insere_lista(&inicio,cria_no(),5,"Ziro","FFF1234",20,30);
            printf("\nInseriu: 5,Ziro, FFFF1234, 20:30 \n\n");
            break;
        case 6:
            remover(&inicio,2);
            printf("\nremover: 2,Caio, CCC1234\n");
            remover(&inicio,0);
            printf("\nremover: 0,Bruno, AAA1234\n");
            remover(&inicio,1);
            printf("\nremover: 1,Alberto, BBB1234\n");
            remover(&inicio,3);
            printf("\nremover: 3,Acriziomar, DDD1234\n");
            remover(&inicio,4);
            printf("\nremover: 4,Danilo, EEE1234\n");
            remover(&inicio,5);
            printf("\nremover: 5,Ziro, FFF1234\n\n");
            break;
        }
    }
    while(recebe!=0);
    return;
}
