#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//VETOR REFERÊNCIA
typedef struct vetref
{
    char *rotulo;
    double valores[64];
} vetref;

//NO PAR
struct no
{
    char *rotulo;
    double valores[64];
    struct no* prox;
};
typedef struct no No;

typedef struct listapilha
{
    No *cabeca;

} listapilha;

typedef struct listafila
{
    No *cabeca;
    No *cauda;

} listafila;

No* pilhapop(listapilha *lf)
{
    No *aux=lf->cabeca->prox;
    lf->cabeca->prox=aux->prox;
    aux->prox=NULL;

    return aux;
}
void InsereNaCauda (listafila *aLista, No *novoNo)

{
        aLista->cauda->prox=novoNo;
        aLista->cauda=novoNo;
}
void distancia(vetref *compara, listapilha *impar, listapilha *par, listafila *fila)
{
    int m;
    double distpar,distimpar,sum,temp;


        sum=0.0;


        for(m=0; m<64; m++)
        {
            temp=((compara->valores[m])-(impar->cabeca->prox->valores[m]));
            sum=sum+(pow(temp,2));
        }
        distimpar=sqrt(sum);

        sum=0.0;


        for(m=0; m<64; m++)
        {
            temp=((compara->valores[m])-(par->cabeca->prox->valores[m]));
            sum=sum+(pow(temp,2));
        }
        distpar=sqrt(sum);


   if(distpar>distimpar)
   {
       InsereNaCauda(fila,pilhapop(impar));
   }
   else
    {
    InsereNaCauda(fila,pilhapop(par));

    }

}

//CRIACAO DA PILHA
No* pilha_cria(void)
{
    No* p =(No*)malloc(sizeof(No));
    p->rotulo=(char*)malloc(50*sizeof(char));
    p->rotulo[0]='1';
    p->prox=NULL;

    return p;
}

//INSERE NA PILHA
void pilha_push(listapilha *pilha, No *no)
{
    no->prox=pilha->cabeca->prox;
    pilha->cabeca->prox=no;

}


No* filapop(listafila *lf)
{
    No *aux=lf->cabeca->prox;
    lf->cabeca->prox=aux->prox;
    aux->prox=NULL;

    return aux;
}

char* concatena (char *s, char c)
{
    int j;
    char copia[50];
    strcpy(copia,s);

    for(j=0;j<50;j++)
    {
        if(j==0)
            s[j]=c;
        else if(j<49)
        {
            s[j]=copia[j-1];
        }
    }
    return s;
}


//INSERE NA PILHA PAR

int main ()
{
    char aux,arquivo[30],c,auxiliar[50];
    int posicao,i;
    double valor;
    listapilha *pilhaimpar,*pilhapar;
    listafila *filaaux;

    scanf("%s",arquivo);
    FILE *fr;

    vetref *VetRef = (vetref*) malloc(sizeof(vetref));
    VetRef->rotulo=(char*)malloc(30*sizeof(char));

    pilhaimpar=(listapilha*)malloc(sizeof(listapilha));
    pilhaimpar->cabeca=pilha_cria();

    pilhapar=(listapilha*)malloc(sizeof(listapilha));
    pilhapar->cabeca=pilha_cria();

    filaaux=(listafila*)malloc(sizeof(listafila));
    filaaux->cabeca=pilha_cria();
    filaaux->cauda=filaaux->cabeca;


    fr=fopen(arquivo,"r");   //ABRE O ARQUIVO DE ENTRADA
    if(fr==NULL)
    {
        printf("Arquivo nulo\n");
        return 0;
    }
    else
    {
        fscanf(fr,"%s", VetRef->rotulo); // LE OS DADOS INCIAIS DO ARQUIVO
    }

    fscanf(fr, "%c", &aux);
    while(aux != '\n')
    {
        fscanf(fr,"%d:%lf",&posicao,&valor);
        VetRef->valores[posicao - 1] = valor;
        fscanf(fr, "%c", &aux);
    }

while((c=getc(fr))!=EOF)
    {
        No *novoNo = (No *) malloc(sizeof(No));
        novoNo->rotulo = (char *) malloc(50 * sizeof(char));
        fscanf(fr,"%s", auxiliar);
        novoNo->rotulo=concatena(auxiliar,c);
        for(i=0;i<64;i++)
        {
            novoNo->valores[i]=0;
        }

        char aux;
        fscanf(fr, "%c", &aux);

        while(aux != '\n')
        {
            fscanf(fr,"%d:%lf",&posicao,&valor);
            novoNo->valores[posicao - 1] = valor;
            fscanf(fr, "%c", &aux);
        }

        InsereNaCauda(filaaux, novoNo);
    }

i=1;
while((filaaux->cabeca->prox)!=NULL)
{
    if(i%2!=0)
    {
        pilha_push(pilhaimpar,filapop(filaaux));
    }
    else
        {
            pilha_push(pilhapar,filapop(filaaux));
        }
        i++;

}

free(filaaux);
 filaaux=(listafila*)malloc(sizeof(listafila));
    filaaux->cabeca=pilha_cria();
    filaaux->cauda=filaaux->cabeca;


No *aux1=pilhaimpar->cabeca->prox;
    while(aux1!=NULL)
    {
        if(aux1->prox!=NULL)
        printf("%s,",aux1->rotulo);
        else
            printf("%s",aux1->rotulo);
        aux1=aux1->prox;
    }
    printf("\n");

    No *aux2=pilhapar->cabeca->prox;
    while(aux2!=NULL)
    {
        if(aux2->prox!=NULL)
        printf("%s,",aux2->rotulo);
        else
            printf("%s",aux2->rotulo);
        aux2=aux2->prox;
    }printf("\n");

    while(((pilhaimpar->cabeca->prox)!=NULL)&&((pilhapar->cabeca->prox)!=NULL))
        {
        distancia(VetRef,pilhaimpar,pilhapar,filaaux);
        }
        if(pilhaimpar->cabeca->prox==NULL){
            filaaux->cauda->prox=pilhapar->cabeca->prox;
        }
        else{
            filaaux->cauda->prox=pilhaimpar->cabeca->prox;
        }

    aux2=filaaux->cabeca->prox;
    while(aux2!=NULL)
    {
        if(aux2->prox!=NULL)
        printf("%s,",aux2->rotulo);
        else
             printf("%s",aux2->rotulo);
        aux2=aux2->prox;
    }

free(pilhaimpar);
free(pilhapar);

    return 0;
}
