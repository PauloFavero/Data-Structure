
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10000

typedef struct
{
    int numAdj;
    int* adj;
}Node;

int numNodes;              /* total number of nodes */
Node allNodes[MAX_NODES];  /* adjacency lists */
int val[MAX_NODES];        /* used to see if a node has been visited */
int topo[MAX_NODES];       /* stores the topologically sorted list */
int topoIndex;             /* index into results list */
int id = 0;                /* global nodes visited counter */

void topo_dfs( int k )
{
    int next;


    val[k] = ++id;


    for ( next = 0; next < allNodes[k].numAdj; next++ )
    {
	if ( !val[allNodes[k].adj[next]] )
	{
	    topo_dfs( allNodes[k].adj[next] );
	}
    }

    topo[topoIndex--] = k;
}

int main()
{
    int  i,x;
    int* tptr;

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
        fscanf(fr,"%d\n",&numNodes); // LE OS DADOS INCIAIS DO ARQUIVO
    }

    /* initialize */
    for ( i = 1; i < numNodes+1; i++ )
    {
	allNodes[i].numAdj = 0;
	allNodes[i].adj = NULL;
	val[i] = 0;
    }

const char s[2] = ",";
    char *token;

    for(i=1; i<numNodes+1; i++)
    {
        fgets(line,100,fr);

        token = strtok(line, s);

        while( token != NULL )
        {

            x=atoi(token);
            if(x!=0)
            {
                tptr = realloc( allNodes[i].adj,
                allNodes[i].numAdj * sizeof( int ) );

                allNodes[i].adj = tptr;
                allNodes[i].adj[allNodes[i].numAdj++] = x;
            }
                token = strtok(NULL, s);
        }



    }


    topoIndex = numNodes + 1;

    for ( i = 1; i < numNodes+1; i++ )
    {
	if ( !val[i] )
	{
	    topo_dfs( i );
	}
    }

    for ( i = 2; i < numNodes+2; i++ )
    {
	printf( "%d ", topo[i] );
    }
    printf( "\n" );

    return 0;
}







