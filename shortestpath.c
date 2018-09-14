#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Vértices de digrafos são representados por objetos do tipo Vertex. */

#define Vertex int
#define Dag Digraph
#define INFINITO 10000000
#define maxV 100

/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */
typedef struct node *link;
struct node {
   Vertex w;
   link next;
   double cost;
};
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura digraph representa um digrafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos. */


struct digraph {
   int V;
   int A;
   link *adj;
};
/* Um objeto do tipo Digraph contém o endereço de um digraph. */

typedef struct digraph *Digraph;

/* A função NEWnode recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next. */

link NEWnode( Vertex w, link next, double cost) {
   link a = malloc( sizeof (struct node));
   a->w = w;
   a->next = next;
   a->cost=cost;
   return a;
}

link NEWnode1( Vertex w, double cost) {
   link a = malloc( sizeof (struct node));
   a->w = w;
   a->next = NULL;
   a->cost=cost;
   return a;
}
Digraph DIGRAPHinit( int V) {
   Vertex v;
   Digraph G = malloc( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (v = 0; v < V; v++)
      G->adj[v] = NULL;
   return G;
}
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsetA insere um arco v-w no digrafo G.  A função supõe que v e w são distintos, positivos, e menores que G->V. Se o digrafo já tem arco v-w, a função não faz nada. */

void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w, double cost) {
   link a;
   link p;
   int count=0,count1=0;
    printf("insert \n");
   for (a = G->adj[v]; a != NULL; a = a->next)
   {

        if (a->w == w)

        {count1++;
            return;
        }
   }
   for (a = G->adj[v]; a != NULL; )
   {
    printf("a->w %d w %d\n",a->w+1,w+1);

        if(a->w < w && a->next==NULL && count1==0)
        {
             count++;
            printf("oi\n");
            p = NEWnode1( w,cost);
            a->next=p;
            return;
        }
         else if(a->w < w && a->next->w >w && count1==0)
        {
             count++;
            printf("oi\n");
            p = NEWnode1( w,cost);
            p->next=a->next;
            a->next=p;

        }
        else
        a = a->next;


   }
   if(count==0&&count==0){
    G->adj[v] = NEWnode( w, G->adj[v],cost);
   G->A++;

   }


}

static int conta, pre[maxV], tsi[maxV];
/* Recebe um DAG G e armazena em tsi[0..V-1] uma ordenação topológica de G:  para cada arco v-w teremos tsi[v] < tsi[w].  (O código é cópia do Programa 19.6 de Sedgewick.) */
void TSdfsR( Dag G, Vertex v)
{
   link a;
   pre[v] = 0;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (pre[a->w] == -1){
            printf("%d\n", a->w);
        TSdfsR( G, a->w);
      }

         printf("visitando conta %d e v %d\n", conta+1, v);
   tsi[v] = conta--;
}
void DAGts( Dag G)
{
   Vertex v;
   conta = G->V - 1;
   for (v = 0; v < G->V; v++)
      pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (pre[v] == -1)
         TSdfsR( G, v);
}


/* A função recebe um DAG G com custos positivos nos arcos e uma ordenação topológica ts de G. Recebe também um vértice s.
 A função calcula a distância de s a cada um dois demais vértices. As distâncias são depositadas no vetor dist indexado pelos vértices. */

/* A função supõe que INFINITO é estritamente maior que a soma dos custos de todos os arcos.*/

void DAGminPath( Dag G, Vertex ts[], Vertex s, double dist[])
{
   int j; Vertex v; link a;
   for (v = 0; v < G->V; v++)
      dist[v] = INFINITO;
   dist[s] = 0.0;
   for (j = 0; j < G->V; j++) {
      v = ts[j];
      for (a = G->adj[v]; a != NULL; a = a->next)
         if (dist[a->w] > dist[v] + a->cost)
            dist[a->w] = dist[v] + a->cost;
   }
}

int main()
{
    int n,i,k;
    double cost;
    char arquivo[30],ch,c;
    FILE *fr;
	 Digraph G;

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

G= DIGRAPHinit(n);

  for(i=0;i<n;)
    {
    	if(ch==-1)
    	break;

    		ch=getc(fr);

        	if(ch!=10)
        	{
        		ungetc(ch,fr);
			}
			else
			i++;
        do{
        fscanf(fr,"%d%c%lf%c",&k,&c,&cost,&ch);
        DIGRAPHinsertA(G,i,k-1,cost);
        printf("%d %d %lf \n",i+1,k,cost);


		if(ch==10)
		{
			i++;
		}
        }
        while(ch==';');

        	ch=getc(fr);

        	if(ch!=10)
        	{
        		ungetc(ch,fr);
			}
			else
			i++;

				if(ch==-1)
    	break;

    }
    link p ;
    int v;

    for(v=0;v<n;v++)
    {
   	 	printf("[%d]-->",v+1);

    	for(p=G->adj[v];p!=NULL;p=p->next){
    	printf("%d-->",p->w+1);
		}
		printf("\n");
	}

    DAGts(G);
    for(i=0;i<n;i++)
        printf("%d\n",tsi[i]+1);

    double *dist=malloc(n*sizeof(double));
    for(i=0;i<n;i++)
    DAGminPath(G,tsi,i,dist);

    for(i=0;i<n;i++)
        printf("%d(%lf)\n",i,dist[i]);


    return 0;
}
