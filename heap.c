#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct  elemento
{
    char *rotulo;
    double freq;
} Elemento;

Elemento *cria_elemento(void)
{
    Elemento *sub;

    sub=(Elemento*)malloc(sizeof(Elemento));
    sub->rotulo=(char*)malloc(30*sizeof(char));

    return sub;
}

void Particao(int Esq, int Dir, int *i, int *j, Elemento **A)
{
    Elemento *x, *aux;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j)/2];
    do
    {
        while (x->freq > A[*i]->freq) (*i)++;
        while (x->freq < A[*j]->freq) (*j)--;
        if (*i <= *j)
        {
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++;
            (*j)--;
        }
    }
    while (*i <= *j);
}

// Entra aqui o procedimento Particao
void Ordena(int Esq, int Dir, Elemento **A)
{
    int i,j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}
void QuickSort(Elemento **A, int n)
{
    Ordena(1, n, A);
    //Ordena(1, n-1, A);
}
int main()

{
    int i,n,j,teste,k;
    //int t;
    char arquivo[30],aux;
    double valor;
    FILE *fr;
    Elemento **vetor,**vetor2,*aux1,*Newelement,*Newelement1;

    scanf("%s",arquivo);

    fr=fopen(arquivo,"r");   //ABRE O ARQUIVO DE ENTRADA
    if(fr==NULL)
    {
        printf("Arquivo nulo\n");
        return 0;
    }
    else
    {
        fscanf(fr,"%d",&n); // LE OS DADOS INCIAIS DO ARQUIVO
    }

    vetor=(Elemento**)calloc((n+1),sizeof(Elemento*));

    for(i=1; i<(n+1); i++)
    {
        vetor[i]=cria_elemento();
        fscanf(fr,"%s",vetor[i]->rotulo);
        fscanf(fr, "%c", &aux);
        fscanf(fr,"%lf",&valor);
        vetor[i]->freq=valor;
    }

    QuickSort(vetor,n);

    for (i=n; i>=1; i--)
    {
        for(j=1; j!=i; j++)
        {

            teste=0;
            if((vetor[i]->freq)==(vetor[j]->freq))
            {
                teste=strcmp((vetor[j]->rotulo),(vetor[i]->rotulo) );
                if(teste>0)
                {
                    aux1=cria_elemento();
                    aux1=vetor[i];
                    vetor[i]=vetor[j];
                    vetor[j]=aux1;
                }
            }
        }
    }
    k=n+1;
    int contador=0,w;
    while((k)>1)
    {
        k=k-1;
        if(k==1)
            return 0;

        if(contador%2==0)
        { //printf("iteracao %d k=%d\n",contador,k);

            Newelement=cria_elemento();
            Newelement->rotulo=strcat(vetor[1]->rotulo,vetor[2]->rotulo);
            Newelement->freq=((vetor[1]->freq)+(vetor[2]->freq));
            printf("%s ", Newelement->rotulo);
            printf("%.5lf\n", Newelement->freq);
            vetor2=(Elemento**)malloc(k*sizeof(Elemento*));
            for(i=1;i<k;i++)
            {
                vetor2[i]=cria_elemento();
            }
            for(w=1; w<=(k-2); w++)
            {

                vetor2[w]->rotulo=vetor[w+2]->rotulo;
                vetor2[w]->freq=vetor[w+2]->freq;
            }
            vetor2[k-1]->rotulo=Newelement->rotulo;
            vetor2[k-1]->freq=Newelement->freq;

            QuickSort(vetor2,k-1);
            for (i=k-1; i>=1; i--)
            {
                for(j=1; j!=i; j++)
                {

                    teste=0;
                    if((vetor2[i]->freq)==(vetor2[j]->freq))
                    {
                        teste=strcmp((vetor2[j]->rotulo),(vetor2[i]->rotulo) );
                        if(teste>0)
                        {
                            aux1=cria_elemento();
                            aux1=vetor2[i];
                            vetor2[i]=vetor2[j];
                            vetor2[j]=aux1;
                        }
                    }
                }
            }
          //  for(t=1; t<(k); t++)
            //{
            //    printf("%s ", vetor2[t]->rotulo);
            //}
            //printf("\n");
            for(i=0;i<n;i++)
            free(vetor[i]);
            contador=contador+1;
        }
        else
        {   //printf("iteracao %d k=%d\n",contador,k);
            Newelement1=cria_elemento();
            Newelement1->rotulo=strcat(vetor2[1]->rotulo,vetor2[2]->rotulo);
            Newelement1->freq=((vetor2[1]->freq)+(vetor2[2]->freq));
            printf("%s ", Newelement1->rotulo);
            printf("%.5lf\n", Newelement1->freq);
            vetor=(Elemento**)malloc(k*sizeof(Elemento*));

            n=k;
            for(w=1; w<=(k-2); w++)
            {
                vetor[w]=vetor2[w+2];
            }
            vetor[k-1]=Newelement1;
            QuickSort(vetor,k-1);
            for (i=k-1; i>=1; i--)
            {
                for(j=1; j!=i; j++)
                {

                    teste=0;
                    if((vetor[i]->freq)==(vetor[j]->freq))
                    {
                        teste=strcmp((vetor[j]->rotulo),(vetor[i]->rotulo) );
                        if(teste>0)
                        {
                            aux1=cria_elemento();
                            aux1=vetor[i];
                            vetor[i]=vetor[j];
                            vetor[j]=aux1;
                        }
                    }
                }
            }

           // for(t=1; t<(k-1); t++)
           // {
           //     printf("%s ", vetor[t]->rotulo);
           // }
            //printf("\n");
            //free(vetor2);
            contador=contador+1;

        }
    }
    return 0;
}

