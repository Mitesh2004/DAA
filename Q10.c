#include <stdio.h>
#include <stdlib.h>

#define MAX 100


/* =========================================================
   HUFFMAN CODING USING GREEDY METHOD

   Purpose:
   --------
   Huffman Coding is used for data compression.

   Idea:
   -----
   Characters with higher frequency get shorter codes,
   and characters with lower frequency get longer codes.

   Steps:
   ------
   1. Create a node for each character with its frequency.
   2. Insert all nodes into a min-priority queue.
   3. Remove two nodes with smallest frequencies.
   4. Create a new node with their sum.
   5. Repeat until only one node remains (root).

   Left edge  -> 0
   Right edge -> 1

   Complexity:
   -----------
   Best Case  : O(n log n)
   Worst Case : O(n log n)

   ========================================================= */


/* Node structure for Huffman Tree */
struct Node
{
    char data;
    int freq;
    struct Node *left, *right;
};


/* Create a new node */
struct Node* createNode(char data, int freq)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;

    return newNode;
}


/* Swap two nodes */
void swap(struct Node** a, struct Node** b)
{
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}


/* Sort nodes based on frequency */
void sort(struct Node* arr[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]->freq > arr[j+1]->freq)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}


/* Print Huffman Codes */
void printCodes(struct Node* root, int code[], int top)
{
    if(root->left)
    {
        code[top] = 0;
        printCodes(root->left, code, top+1);
    }

    if(root->right)
    {
        code[top] = 1;
        printCodes(root->right, code, top+1);
    }

    /* If leaf node */
    if(!root->left && !root->right)
    {
        printf("%c: ", root->data);

        for(int i=0;i<top;i++)
            printf("%d", code[i]);

        printf("\n");
    }
}


/* Build Huffman Tree */
void huffman(char data[], int freq[], int n)
{
    struct Node* nodes[MAX];

    for(int i=0;i<n;i++)
        nodes[i] = createNode(data[i], freq[i]);

    int size = n;

    while(size > 1)
    {
        sort(nodes, size);

        struct Node* left = nodes[0];
        struct Node* right = nodes[1];

        struct Node* newNode = createNode('$', left->freq + right->freq);

        newNode->left = left;
        newNode->right = right;

        nodes[0] = newNode;

        for(int i=1;i<size-1;i++)
            nodes[i] = nodes[i+1];

        size--;
    }

    int code[MAX];
    int top = 0;

    printf("\nHuffman Codes:\n");

    printCodes(nodes[0], code, top);
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    char data[MAX];
    int freq[MAX];
    int n;

    printf("Enter number of characters: ");
    scanf("%d",&n);

    printf("Enter characters:\n");

    for(int i=0;i<n;i++)
        scanf(" %c",&data[i]);

    printf("Enter frequencies:\n");

    for(int i=0;i<n;i++)
        scanf("%d",&freq[i]);

    huffman(data, freq, n);

    printf("\nBest Case Complexity  = O(n log n)");
    printf("\nWorst Case Complexity = O(n log n)\n");

    return 0;
}
