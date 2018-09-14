#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef struct edge
{
    int u,v,w;
} edge;

typedef struct edgelist
{
    edge data[MAX];
    int n;
} edgelist;
edgelist elist;

float G[MAX][MAX];
int n;
edgelist spanlist;

void kruskal();
int find(int belongs[],int vertexno);
void union1(int belongs[],int c1,int c2);
void sort();
void print();

int main()
{
    int i,j;
    float x;

    char arquivo[30],line[100];
    FILE *fr;

    scanf("%s",arquivo);

    fr=fopen(arquivo,"r");   //ABRE O ARQUIVO DE ENTRADA
    if(fr==NULL)
    {
        printf("Arquivo nulo\n");
        return 0;
    }
    else
    {
        fscanf(fr,"%d\n",&n); // LE OS DADOS INCIAIS DO ARQUIVO
    }

    for(i=0; i<n; i++)
    {
        fgets(line,100,fr);



        const char s[2] = " ";
        char *token;

        token = strtok(line, s);

        while( token != NULL )
        {
            for(j=0; j<n; j++)
            {
                x=atof(token);
                G[i][j]=x;
                token = strtok(NULL, s);
            }
        }
    }
    kruskal();
    print();
}

void kruskal()
{
    int belongs[MAX],i,j,cno1,cno2;
    elist.n=0;
    for(i=1; i<n; i++)
        for(j=0; j<i; j++)
        {
            if(G[i][j]!=0)
            {
                elist.data[elist.n].u=i;
                elist.data[elist.n].v=j;
                elist.data[elist.n].w=G[i][j];
                elist.n++;
            }
        }

    sort();

    for(i=0; i<n; i++)
        belongs[i]=i;

    spanlist.n=0;
    for(i=0; i<elist.n; i++)
    {
        cno1=find(belongs,elist.data[i].u);
        cno2=find(belongs,elist.data[i].v);
        if(cno1!=cno2)
        {
            spanlist.data[spanlist.n]=elist.data[i];
            spanlist.n=spanlist.n+1;
            union1(belongs,cno1,cno2);
        }
    }
}

int find(int belongs[],int vertexno)
{
    return(belongs[vertexno]);
}

void union1(int belongs[],int c1,int c2)
{
    int i;
    for(i=0; i<n; i++)
        if(belongs[i]==c2)
            belongs[i]=c1;
}

void sort()
{
    int i,j;
    edge temp;
    for(i=1; i<elist.n; i++)
        for(j=0; j<elist.n-1; j++)
            if(elist.data[j].w>elist.data[j+1].w)
            {
                temp=elist.data[j];
                elist.data[j]=elist.data[j+1];
                elist.data[j+1]=temp;
            }
}

void print()
{
    int i;
    float cost=0.0;
    for(i=0; i<spanlist.n; i++)
    {
        cost=cost+spanlist.data[i].w;
    }
    printf("%.5f",cost);
}
