#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no
{
    char *rotulo;
    double valores [32];
    struct no *prox;
} no;

typedef struct lista
{
    no *cabeca;
    no *cauda;

} lista;

void InsereNaCauda (lista *aLista, no *novoNo)

{
    if (aLista->cabeca==NULL)
    {
        aLista-> cabeca = novoNo;
        aLista-> cauda = novoNo;
    }
    else
    {
        aLista->cauda->prox=novoNo;
        aLista->cauda=novoNo;

    }
}
void InsereNaCabeca(lista *aLista, no *novoNo)
{
    if(aLista->cabeca==NULL)
    {
        aLista-> cabeca = novoNo;
        aLista-> cauda = novoNo;
    }
    else
    {
        novoNo->prox=aLista->cabeca;
        aLista->cabeca=novoNo;

    }
}

no *ProcurarNo(lista *aLista, no *novoNo)
{
    no *aux=aLista->cabeca;

    while(aux!=NULL)
    {
        if(aux!=novoNo)
        {
            aux=aux->prox;
        }
        else
        {
            return aux;
        }
    }
    return aux;
}
void RemoverNo(lista *aLista, no *novoNo)
{

    if(aLista->cabeca==NULL)
    {
        return;
    }
    else if(aLista->cabeca==novoNo)
    {
        aLista->cabeca=novoNo->prox;
        free(novoNo);

        if(aLista->cabeca==NULL)
        {
            aLista->cauda=NULL;
        }
        return;
    }

    no *retirar=ProcurarNo(aLista,novoNo);
    no *temp=aLista->cabeca;

    while(temp->prox!=retirar)
    {
        temp=temp->prox;
    }

    temp->prox=retirar->prox;
    free(retirar);

    if(temp->prox==NULL)
    {
        aLista->cauda=temp;
    }
    return;
}

int distancia(int k, no *novoNo, lista *klistas)
{
    int j,m,poskl=0;
    double dist,sum,aux,temp;

    for(j=0; j<k; j++)
    {
        sum=0.0;
        dist=0.0;

        for(m=0; m<32; m++)
        {
            temp=((klistas[j].cabeca->valores[m])-(novoNo->valores[m]));
            sum=sum+(pow(temp,2));
        }
        dist=sqrt(sum);

        if(j==0)
        {
            aux=dist;
            poskl=j;
        }
        else if(dist<aux)
        {
            aux=dist;
            poskl=j;
        }

    }
    return poskl;

}

no *kmetoide(lista *klistas) // RETORNA O METOIDE DE UMA LISTA
{
    int i,j;

    long double distff=0.0,aux,disttotal=0.0,temp;

    no *posatual=klistas->cabeca, *poscorrent,*metoide;

    j=0;

    //tratar cabeca nula!!!

    while(posatual!=NULL)
    {
        poscorrent=klistas->cabeca;  //INICIALIZACAO DO NO CURSOR

        while(poscorrent!=NULL)
        {

            if(posatual==poscorrent)
            {
                poscorrent=poscorrent->prox;            // AVANCO DO NO CURSOR (AUXILIAR)
            }
            else
            {
                for(i=0; i<32; i++) // LOOPS PARA CALCULAR A DISTANCIA ENTRE DOIS NOS DE UMA MESMA LISTA
                {
                    temp=((posatual->valores[i])-(poscorrent->valores[i]));

                    distff=distff+fabsl(temp);

                }
                disttotal=disttotal+distff;
                distff=0.0;
                poscorrent=poscorrent->prox; // AVANCO DO NO CURSOR (AUXILIAR)
            }

        }
        if(j==0)            // ARMAZENA A DISTANCIA DA PRIMEIRA ITERACAO
        {
            aux=disttotal;
            metoide=posatual;
        }
        else if(disttotal<aux)      //COMPARA SE A DISTANCIA E MENOR QUE ANTERIOR E CASO SEJA MENOR E GUARDADO A SUA POSICAO
        {
            aux=disttotal;
            metoide=posatual;
        }
        disttotal=0.0;
        posatual=posatual->prox;  //AVANCAO DA POSICAO DE ANALISE
        j++;                        //MARCADOR DE ITERACAO
    }

    return metoide;
}

no *copia(no *nocopiado)        //COPIAS OS DADOS DE UM NO PARA UM NOVO NO
{
    int i;

    no *novoNo = (no *) malloc(sizeof(no));
    novoNo->rotulo = (char *) malloc(50 * sizeof(char));

    novoNo->rotulo=nocopiado->rotulo;
    novoNo->prox=NULL;
    for(i=0; i<32; i++)
    {
        novoNo->valores[i]=nocopiado->valores[i];
    }
    return novoNo;
}

int main ()
{
    int n,k,i=0,j;
    int posicao,poscopia;
    double valor;
    char arquivo[50];

    lista *klistas;
    lista *klistacopia;

    scanf("%s",arquivo);
    FILE *fr;


    fr=fopen(arquivo,"r");   //ABRE O ARQUIVO DE ENTRADA
    if(fr==NULL)
    {
        printf("Arquivo nulo\n");
        return 0;
    }
    else
    {
        fscanf(fr,"%d %d", &n, &k); // LE OS DADOS INCIAIS DO ARQUIVO
    }

    klistas = (lista *) calloc(k, sizeof(lista));

    for(i=0; i<k; i++)
    {
        klistas[i].cabeca=NULL;
        klistas[i].cauda=NULL;
    }
//LOOP ---> INSERE AS CABECAS INICIAIS NO VETOR KLISTAS

    for(i=0; i<k; i++)
    {


        no *novoNo = (no *) malloc(sizeof(no));
        novoNo->rotulo = (char *) malloc(50 * sizeof(char));
        fscanf(fr,"%s", novoNo->rotulo);

        char aux;
        fscanf(fr, "%c", &aux);
        while(aux != '\n')
        {
            fscanf(fr,"%d:%lf",&posicao,&valor);
            novoNo->valores[posicao - 1] = valor;
            fscanf(fr, "%c", &aux);
        }

        InsereNaCauda(&(klistas[i]), novoNo);
    }
// LOOP --> CRIA E ALOCA OS NOS E OS INSERE EM SUAS RESPECTIVAS LISTAS
    for(i=0; i<(n-k); i++)
    {
        int posk;

        no *novoNo = (no *) malloc(sizeof(no));
        novoNo->rotulo = (char *) malloc(50 * sizeof(char));
        fscanf(fr,"%s", novoNo->rotulo);

        char aux;
        fscanf(fr, "%c", &aux);
        while(aux != '\n')
        {
            fscanf(fr,"%d:%lf",&posicao,&valor);
            novoNo->valores[posicao - 1] = valor;
            fscanf(fr, "%c", &aux);
        }

        posk=distancia(k, novoNo, klistas);
        InsereNaCauda(&(klistas[posk]), novoNo);


    }

    // LOOP PARA IMPRIMIR A PRIMEIRA INTERACAO!

    for(i=0; i<k; i++)
    {
        no *current=klistas[i].cabeca;

        while(current!=NULL)

        {
            if(current->prox!=NULL)
                printf("%s,",current->rotulo);
            else
                printf("%s",current->rotulo);

            current=current->prox;
        }
        printf("\n");

    }

// ****PRIMEIRA ITERACAO DO METOIDE******
for(j=0;j<5;j++)
{

    //DECLARACAO DE UM VETOR PARA COPIAR A KLISTA
    klistacopia=(lista *) calloc(k, sizeof(lista));         //ALOCACAO DA LISTA COPIA
    no *metoide;                         //DECLARACAO DO NO QUE RECEBERA O METOIDE A SER COPIADO PARA KLISTACOPIA

    for(i=0; i<k; i++)

    {
        klistacopia[i].cabeca=NULL;
        klistacopia[i].cauda=NULL;

        metoide=kmetoide(&(klistas[i]));                 //OBTENCAO DO METOIDE DA I-ESIMA LISTA DO VETOR KLISTA

        InsereNaCauda(&(klistacopia[i]), copia(metoide));     // INSERCAO DO METOIDE NO VETOR COPIA DE KLISTA
        RemoverNo(&(klistas[i]),metoide);

    } //*****FINAL DA ITERACAO DO METOIDE******

// *****ITERACOES PARA ALOCAR A LISTA COPIADA******

    for(i=0; i<k; i++)                                              //ERRO!!!!!!!!!!!!!!
    {
        no *cursorklista=klistas[i].cabeca;
        no *cursorlista=cursorklista;

        while(cursorlista!=NULL)
        {
            poscopia=distancia(k,cursorlista,klistacopia);
            //printf("poscopia=%d\n",poscopia);
            //printf("%s\n",copia(cursorlista)->rotulo);
            InsereNaCauda(&(klistacopia[poscopia]),copia(cursorlista));
            RemoverNo(&(klistas[i]),cursorlista);
            cursorlista=cursorlista->prox;
        }
        //printf("i= %d\n",i);
    }
//**** FIM  ITERACOES PARA ALOCAR A LISTA COPIADA*****

// *************IMPRESSOES DO PRIMEIRA ITERACAO COM O NOVO METOIDE************************
    for(i=0; i<k; i++)
    {
        no *current=klistacopia[i].cabeca;

        while(current!=NULL)

        {
            if(current->prox!=NULL)
                printf("%s,",current->rotulo);
            else
                printf("%s",current->rotulo);

            current=current->prox;

        }
        printf("\n");

    }  // ************* FIM DAS IMPRESSOES DA PRIMEIRA ITERACAO COM O NOVO METOIDE************************
    free(klistas);
    klistas=klistacopia;
    klistacopia=NULL;


}

    return 0;

}
/*

 for(j=0; j<4; j++)     ******* QUATRO ITERACAOES PARA AJUSTAR A LISTA**********

   {
        ECLARACAO DE UM VETOR PARA COPIAR A KLISTA

        klistacopia=(lista *) calloc(k, sizeof(lista));         //ALOCACAO DA LISTA COPIA
        no *metoide;                         //DECLARACAO DO NO QUE RECEBERA O METOIDE A SER COPIADO PARA KLISTACOPIA

        for(i=0; i<k; i++)

        {
            klistacopia[i].cabeca=NULL;
            klistacopia[i].cauda=NULL;

            metoide=kmetoide(&(klistas[i]));                 //OBTENCAO DO METOIDE DA I-ESIMA LISTA DO VETOR KLISTA

            InsereNaCauda(&(klistacopia[i]), copia(metoide));     // INSERCAO DO METOIDE NO VETOR COPIA DE KLISTA
            RemoverNo(&(klistas[i]),metoide);

        }

iteracoes para alocar a lista copiada.



        for(i=0; i<k; i++)
        {
            no *cursorklista=klistas[i].cabeca;
            no *cursorlista=cursorklista;

            while(cursorlista!=NULL)
            {
                poscopia=distancia(k,cursorlista,&(klistacopia[i]));
                InsereNaCauda(&(klistacopia[poscopia]),copia(cursorlista));
                RemoverNo(&(klistas[i]),cursorlista);
                cursorlista=cursorlista->prox;
            }


        }
*************IMPRESSAO DE QUATRO ITERACOES******************
        for(i=0; i<k; i++)
        {
            no *current=klistacopia[i].cabeca;

            while(current!=NULL)

            {
                if(current->prox!=NULL)
                    printf("%s,",current->rotulo);
                else
                    printf("%s",current->rotulo);

                current=current->prox;

            }
            printf("\n");

        }


    } ****** FIM DA QUATRO ITERACAOES PARA AJUSTAR A LISTA**********
 MPRESSAO DA KLISTACOPIA.

*/


