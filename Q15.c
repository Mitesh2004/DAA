#include <stdio.h>

#define MAX 20

/* ---------------------------------------------------------
   Function: isSafe

   Purpose:
   Checks whether a vertex can be added to the Hamiltonian path.

   Conditions:
   1. The vertex must be adjacent to the previous vertex.
   2. The vertex must not already be in the path.
--------------------------------------------------------- */
int isSafe(int v, int graph[MAX][MAX], int path[], int pos)
{
    /* Check if vertex is connected to previous vertex */
    if(graph[path[pos-1]][v] == 0)
        return 0;

    /* Check if vertex already exists in path */
    for(int i=0; i<pos; i++)
    {
        if(path[i] == v)
            return 0;
    }

    return 1;
}


/* ---------------------------------------------------------
   Function: hamiltonianUtil

   Purpose:
   Recursive function that builds Hamiltonian cycle using
   backtracking.

   Steps:
   1. Try different vertices as next candidate.
   2. Check if safe to add.
   3. If safe → add to path.
   4. Recursively continue.
   5. If no solution → backtrack.
--------------------------------------------------------- */
int hamiltonianUtil(int graph[MAX][MAX], int path[], int pos, int n)
{
    /* If all vertices are included in the path */
    if(pos == n)
    {
        /* Check if last vertex connects to first */
        if(graph[path[pos-1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    /* Try different vertices */
    for(int v = 1; v < n; v++)
    {
        if(isSafe(v, graph, path, pos))
        {
            path[pos] = v;

            if(hamiltonianUtil(graph, path, pos+1, n) == 1)
                return 1;

            /* Backtracking */
            path[pos] = -1;
        }
    }

    return 0;
}


/* ---------------------------------------------------------
   Function: hamiltonianCycle

   Purpose:
   Initializes path and starts recursion.
--------------------------------------------------------- */
void hamiltonianCycle(int graph[MAX][MAX], int n)
{
    int path[MAX];

    /* Initialize path */
    for(int i=0;i<n;i++)
        path[i] = -1;

    /* Start from vertex 0 */
    path[0] = 0;

    if(hamiltonianUtil(graph, path, 1, n) == 0)
    {
        printf("\nNo Hamiltonian Cycle exists\n");
        return;
    }

    printf("\nHamiltonian Cycle:\n");

    for(int i=0;i<n;i++)
        printf("%d ", path[i]);

    /* Return to starting vertex */
    printf("%d\n", path[0]);
}


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

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }

    hamiltonianCycle(graph, n);

    return 0;
}

/*
 A Hamiltonian cycle is a cycle in a graph that visits every vertex exactly once and returns to the starting vertex. It is a closed loop, often used in computer science for optimization problems like the "Traveling Salesperson Problem".
 */
