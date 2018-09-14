#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This constant can be avoided by explicitly calculating height of Huffman Tree
int t,x=0;
// A Huffman tree node
struct MinHeapNode
{
    char *rotulo;  // One of the input characters
    double freq;  // Frequency of the character
    int cont;
    struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap
{
    int tamAtual;    // Current size of min heap
    int tamMax;   // capacity of min heap
    struct MinHeapNode **vetor;  // Attay of minheap node pointers
} ;

// A utility function allocate a new min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(void)
{
    struct MinHeapNode* temp =(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->rotulo = (char*)malloc(30*sizeof(char));
    return temp;
}

// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(int tamMax)
{
    struct MinHeap* minHeap =(struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->tamAtual = 0;  // current size is 0
    minHeap->tamMax = tamMax;
    minHeap->vetor =(struct MinHeapNode**)malloc(minHeap->tamMax * sizeof(struct MinHeapNode*));
    return minHeap;
}
// A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->tamAtual && minHeap->vetor[left]->freq < minHeap->vetor[smallest]->freq)
      smallest = left;

    if (right < minHeap->tamAtual &&  minHeap->vetor[right]->freq < minHeap->vetor[smallest]->freq)
      smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->vetor[smallest],&minHeap->vetor[idx]);
        minHeapify(minHeap, smallest);
    }
}
// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->tamAtual- 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i){
        minHeapify(minHeap, i);
    }
}
int small(struct MinHeapNode *a, struct MinHeapNode *b)
{
    if(a->freq<b->freq)
        return 1;
    else if (a->freq==b->freq)
    {
        if(a->cont<b->cont)
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
//y= small(minHeapNode, minHeap->vetor[(i-1)/2]);

    //while(i>0 && small(minHeapNode, minHeap->vetor[(i-1)/2])==1 )
// A utility function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->tamAtual;
    int i = minHeap->tamAtual - 1;

    while (i && minHeapNode->freq< minHeap->vetor[(i - 1)/2]->freq)
    {
    	// printf("i: %d no: %lf vetor: %lf\n", i, minHeapNode->freq,minHeap->vetor[(i - 1)/2]->freq);
        minHeap->vetor[i] = minHeap->vetor[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->vetor[i] = minHeapNode;
}
// A utility function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->tamAtual == 1);
}
// A standard function to extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->vetor[0];
    minHeap->vetor[0] = minHeap->vetor[minHeap->tamAtual - 1];
    --minHeap->tamAtual;
    minHeapify(minHeap, 0);
    return temp;
}
// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(struct MinHeap *minHeap)
{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // 'NULL' is a special value for internal nodes, not used
        top = newNode();
        top->rotulo=NULL;
        top->freq=left->freq+right->freq;
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}
// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}
void printArr2(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}
// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
        printf("%s: ", root->rotulo);
        printArr(arr, top);
    }
}
void printCodes2(struct MinHeapNode* root, char nome[], int arr[], int top)
{
   // printf("%s %s\n",nome,root->rotulo);
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes2(root->left, nome, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes2(root->right, nome, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
        int t=strcmp(nome,root->rotulo);
        if(t==0)
        {
        printArr2(arr, top);
        return;
        }
    }
}
// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
struct MinHeapNode* HuffmanCodes(struct MinHeap *minHeap,int n)
{
   //  Construct Huffman Tree
   struct MinHeapNode* root = buildHuffmanTree(minHeap);

   // Print Huffman codes using the Huffman tree built above
   int *arr,top = 0;
   arr=malloc(n*sizeof(int));
   printCodes(root, arr, top);
   return root;
}
void decodify(struct MinHeapNode *root, char arr[], int i)
{
    if (isLeaf(root)){

        printf("%s\n", root->rotulo);
        t=i;
    }
    else if (arr[i]=='0')
        {
        root=root->left;
        i++;
       decodify(root, arr, i);
        }
        else if (arr[i]=='1')
        {
            root=root->right;
            i++;
            decodify(root, arr, i);
        }



}

int main()
{
    int i,n,m,arr[500],l,j;
    char arquivo[30],aux,sub[10000],code[10000];
    double valor;
    FILE *fr;
    struct  MinHeap *vetorHEAP;
    struct  MinHeapNode *novono,*root;//*teste;

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

  vetorHEAP=createMinHeap(n);

    for(i=0; i<n; i++)
    {
        novono=newNode();
        fscanf(fr,"%s",novono->rotulo);
        fscanf(fr, "%c", &aux);
        fscanf(fr,"%lf\n",&valor);
        novono->freq=valor;
        novono->cont=x;
        insertMinHeap(vetorHEAP,novono);
        //vetorHEAP->vetor[i]=novono;
        x=x+1;
    }
    struct MinHeapNode *aux1;

//for(i=0;i<n;i++)
     //   printf("%s %lf\n",vetorHEAP->vetor[i]->rotulo,vetorHEAP->vetor[i]->freq);
        
       // printf("************************\n");
	for(i=0;i<n;i++)
	{
		for(j=n-1;j>i;j--)
		{
			
			if(vetorHEAP->vetor[i]->freq==vetorHEAP->vetor[j]->freq)
            {//	printf("nos iguais %s %s\n",vetorHEAP->vetor[i]->rotulo,vetorHEAP->vetor[j]->rotulo);
                if(vetorHEAP->vetor[i]->cont>vetorHEAP->vetor[j]->cont){
                	//printf("%s:%d   %s:%d\n",vetorHEAP->vetor[i]->rotulo,vetorHEAP->vetor[i]->cont,vetorHEAP->vetor[j]->rotulo,vetorHEAP->vetor[j]->cont);
                    aux1=vetorHEAP->vetor[j];
                    vetorHEAP->vetor[j]=vetorHEAP->vetor[i];
                    vetorHEAP->vetor[i]=aux1;}
                   // printf("%s:%d   %s:%d\n",vetorHEAP->vetor[i]->rotulo,vetorHEAP->vetor[i]->cont,vetorHEAP->vetor[j]->rotulo,vetorHEAP->vetor[j]->cont);
            }
		}
	}

    //for(i=0;i<n;i++)
      //  printf("%s %lf\n",vetorHEAP->vetor[i]->rotulo,vetorHEAP->vetor[i]->freq);
    //teste=extractMin(vetorHEAP);
   // printf("%s*********\n\n",teste->rotulo);
    root=buildHuffmanTree(vetorHEAP);
    //root=HuffmanCodes(vetorHEAP,n);

    fscanf(fr,"%d",&m);
    fscanf(fr, "%c", &aux);
    fscanf(fr, "%s,", sub);
    char *nome;
    const char delims[] = ",";
    const char *s = sub;
    do {
        size_t field_len = strcspn(s, delims);
        nome=(char*)malloc((field_len+1)*sizeof(char));
        for(i=0;i<field_len+1;i++)
        {
            if(i!=field_len)
            nome[i] = s[i];
            else
                nome[i]='\0';
        }
        printCodes2(root,nome,arr,0);
        free(nome);
        s += field_len;
    }
    while (*s++);
    printf("\n");
    fscanf(fr,"%s",code);
    l=strlen(code);

    for(t=0;t<l; ){
     decodify(root, code, t );
    }

    free(vetorHEAP);



}
