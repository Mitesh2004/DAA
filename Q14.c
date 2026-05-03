#include <stdio.h>

#define MAX 20

/* ---------------------------------------------------------
   Global Stack
   Used to store vertices in reverse finishing order.
   After DFS finishes exploring a vertex, it is pushed
   into the stack.
--------------------------------------------------------- */
int stack[MAX];
int top = -1;


/* ---------------------------------------------------------
   Function: push
   Purpose : Insert a vertex into the stack

   Each vertex is pushed after all its neighbors
   are visited in DFS.
--------------------------------------------------------- */
void push(int v)
{
    stack[++top] = v;
}


/* ---------------------------------------------------------
   Function: DFS (Depth First Search)

   This function performs DFS traversal.

   Working:
   1. Mark the current vertex as visited.
   2. Visit all adjacent vertices recursively.
   3. After visiting all neighbors, push the vertex
      into the stack.

   Why push after recursion?
   Because a vertex should appear AFTER all
   vertices that depend on it.
--------------------------------------------------------- */
void DFS(int graph[MAX][MAX], int visited[], int v, int n)
{
    visited[v] = 1;   // Mark vertex as visited

    for(int i = 1; i <= n; i++)
    {
        /* If there is an edge and the node is not visited */
        if(graph[v][i] == 1 && visited[i] == 0)
        {
            DFS(graph, visited, i, n);
        }
    }

    /* After exploring all neighbors push vertex */
    push(v);
}


/* ---------------------------------------------------------
   Function: topologicalSort

   This function ensures DFS is called for every vertex.

   Steps:
   1. Initialize visited array.
   2. Run DFS from every unvisited vertex.
   3. After DFS completes, stack contains vertices
      in reverse topological order.
   4. Pop stack to get the correct order.
--------------------------------------------------------- */
void topologicalSort(int graph[MAX][MAX], int n)
{
    int visited[MAX] = {0};

    for(int i = 1; i <= n; i++)
    {
        if(visited[i] == 0)
        {
            DFS(graph, visited, i, n);
        }
    }

    printf("\nTopological Order:\n");

    /* Print stack elements */
    while(top != -1)
    {
        printf("%d ", stack[top--]);
    }

    printf("\n");
}

// V = number of vertices
// E = number of edges
/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main()
{
    int graph[MAX][MAX];
    int n,i,j;

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("\nEnter adjacency matrix:\n");

    /* Input adjacency matrix of directed graph */
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }

    /* Perform Topological Sorting */
    topologicalSort(graph, n);

    return 0;
}
