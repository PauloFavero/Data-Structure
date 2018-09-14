#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct cliente
{
    char *rotulo;
    double valor;
    double hora;
} cliente;


cliente *cria_cliente(void)
{
    cliente *clt;

    clt=(cliente*)malloc(sizeof(cliente));
    clt->rotulo=(char*)malloc(30*sizeof(char));

    return clt;
}

void Particao(int Esq, int Dir, int *i, int *j, cliente**A)
{
    cliente *x, *aux;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j)/2];
    do
    {
        while (x->valor > A[*i]->valor) (*i)++;
        while (x->valor < A[*j]->valor) (*j)--;
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
void Ordena(int Esq, int Dir, cliente **A)
{
    int i,j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}
void QuickSort(cliente **A, int n)
{
    Ordena(0, n-1, A);
}
int main()

{
    int i,j,n,teste;
    char arquivo[30],aux;
    double valor,tempo;
    FILE *fr;
    cliente **vetor;
    cliente *aux1;

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
    vetor=(cliente**)calloc(n,sizeof(cliente*));

    for(i=0; i<n; i++)
    {
        vetor[i]=cria_cliente();
        fscanf(fr,"%s",vetor[i]->rotulo);
        fscanf(fr, "%c", &aux);
        fscanf(fr,"%lf",&valor);
        fscanf(fr, "%c", &aux);
        fscanf(fr,"%lf\n",&tempo);
        vetor[i]->valor=valor;
        vetor[i]->hora=tempo;
    }


    QuickSort(vetor,n);

    for (i=n-1; i>=0; i--)
    {
        for(j=0; j!=i; j++)
        {

            teste=0;
            if((vetor[i]->valor)==(vetor[j]->valor))
            {
                teste=strncmp((vetor[i]->rotulo),(vetor[j]->rotulo),10 );
                if(teste>0)
                {
                    aux1=vetor[i];
                    vetor[i]=vetor[j];
                    vetor[j]=aux1;
                }
            }
        }
    }

   /* for(i=(n-1); i>=0; i--)
    {
        if(i>0)
            printf("%s,",vetor[i]->rotulo);
        else
            printf("%s",vetor[i]->rotulo);
            
        //    printf("% lf %lf\n",vetor[i]->valor,vetor[i]->hora);
    }
    printf("\n");
*/
    double soma=0,valortotal=0;
    int count=0;

    for(i=(n-1); i>=0; i--)
    {
        count+=1;
        //printf("%d\n",count);

		if(((vetor[i]->hora)+soma)>=8)
		{
			valortotal+=(8-(soma))*vetor[i]->valor;
            soma+=vetor[i]->hora;
            i=-1;
			
		}
        else if(((vetor[i]->hora<8)&&soma<8)&&((vetor[i]->hora)+soma)<8)
		        {
            
            valortotal+=vetor[i]->hora*vetor[i]->valor;
            soma+=vetor[i]->hora;
            
        }
        else if((vetor[i]->hora>8)&&soma<8)
		        {
            valortotal+=(8-(soma))*vetor[i]->valor;
            soma+=vetor[i]->hora;
            i=-1;
        }
        if(soma>=8)
            i=-1;
            
         //printf("%lf %lf\n",valortotal,soma);
    }

    //printf("\n");
   
int x=(n-1);
    while(count>0)
    {
    	
      //  printf("teste\n");
      //   printf("%d\n",x);
         
        if(count>1)
        {
            printf("%s,",vetor[x]->rotulo);
            count+=(-1);
            x=x-1;
        }
        else
            {
            	printf("%s\n",vetor[x]->rotulo);
            count+=(-1);
            x=x-1;
			}
    }
    printf("%.2lf",valortotal);

    return 0;
}
