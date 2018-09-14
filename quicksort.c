#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct substancia
{
    char *rotulo;
    double frequencia;
} substancia;


substancia *cria_substancia(void)
{
    substancia *sub;

    sub=(substancia*)malloc(sizeof(substancia));
    sub->rotulo=(char*)malloc(30*sizeof(char));

    return sub;
}

void Particao(int Esq, int Dir, int *i, int *j, substancia **A)
{
    substancia *x, *aux;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j)/2];
    do
    {
        while (x->frequencia > A[*i]->frequencia) (*i)++;
        while (x->frequencia < A[*j]->frequencia) (*j)--;
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
void Ordena(int Esq, int Dir, substancia **A)
{
	int i,j;
  Particao(Esq, Dir, &i, &j, A);
  if (Esq < j) Ordena(Esq, j, A);
  if (i < Dir) Ordena(i, Dir, A);
}
void QuickSort(substancia **A, int n)
{
  Ordena(0, n-1, A);
  //Ordena(1, n-1, A);
}
int main()

{
    int i,j,n,teste;
    char arquivo[30],aux;
    double valor;
    FILE *fr;
    substancia **vetor;
    substancia *aux1;

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
    vetor=(substancia**)calloc(n,sizeof(substancia*));

    for(i=0; i<n; i++)
    {
        vetor[i]=cria_substancia();
        fscanf(fr,"%s",vetor[i]->rotulo);
        fscanf(fr, "%c", &aux);
        fscanf(fr,"%lf\n",&valor);
        vetor[i]->frequencia=valor;
    }
    

    QuickSort(vetor,n);
    /* for(i=(n-1); i>=0; i--)
    {
        if(i>0)
        printf("%s,",vetor[i]->rotulo);
        else
            printf("%s",vetor[i]->rotulo);
    }*/

for (i=n-1;i>=0;i--)
{
    for(j=0;j!=i;j++)
        {

		teste=0;
        if((vetor[i]->frequencia)==(vetor[j]->frequencia))
    {
        //printf("%lf\n",vetor[i]->frequencia);
        //printf("%lf\n",vetor[j]->frequencia);

        //printf("%d %d\n",i,j);
        teste=strncmp((vetor[i]->rotulo),(vetor[j]->rotulo),10 );
        //printf("%d\n",teste);
      if(teste>0)
        {
          //printf("%s\n",vetor[i]->rotulo);
           //printf("%s\n",vetor[j]->rotulo);
            aux1=vetor[i];
            vetor[i]=vetor[j];
            vetor[j]=aux1;
        }
    }
    }
}

     for(i=(n-1); i>=0; i--)
    {
        if(i>0)
        printf("%s,",vetor[i]->rotulo);
        else
            printf("%s",vetor[i]->rotulo);
    }

    return 0;
}
