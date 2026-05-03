#include <stdio.h>

#define MAX 20
#define INF 9999


/* =========================================================
   PRIM'S ALGORITHM

   Purpose:
   --------
   To find the Minimum Cost Spanning Tree (MST) of a graph.

   Concept:
   --------
   Prim's algorithm builds the MST starting from any vertex
   and always adds the smallest edge that connects a visited
   vertex to an unvisited vertex.

   Steps:
   ------
   1. Start from any vertex (usually vertex 1).
   2. Mark it as visited.
   3. Find the smallest edge connecting visited to unvisited vertex.
   4. Add that edge to MST.
   5. Mark the new vertex as visited.
   6. Repeat until (V - 1) edges are selected.

   Time Complexity:
   ----------------
   O(V^2) using adjacency matrix
   ========================================================= */


/* =========================================================
   Function: prim
   Purpose : Implement Prim’s Algorithm
   ========================================================= */
void prim(int cost[MAX][MAX], int n)
{
    int visited[MAX];
    int i, j;
    int min, mincost = 0;
    int u = 1, v = 1;
    int edge_count = 0;

    /* Initially no vertex is visited */
    for(i = 1; i <= n; i++)
        visited[i] = 0;

    /* Start from vertex 1 */
    visited[1] = 1;

    printf("\nEdges in Minimum Spanning Tree:\n");

    while(edge_count < n-1)
    {
        min = INF;

        /* Find minimum edge connecting visited to unvisited */
        for(i = 1; i <= n; i++)
        {
            if(visited[i] == 1)
            {
                for(j = 1; j <= n; j++)
                {
                    if(visited[j] == 0 && cost[i][j] < min)
                    {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        /* Add edge to MST */
        printf("%d edge (%d,%d) = %d\n", edge_count+1, u, v, min);

        mincost += min;
        edge_count++;

        visited[v] = 1;   // Mark new vertex visited
    }

    printf("\nMinimum Cost = %d\n", mincost);
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int cost[MAX][MAX];
    int n, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter cost adjacency matrix:\n");

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            scanf("%d", &cost[i][j]);

            /* Replace 0 with INF except diagonal */
            if(cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    /* Call Prim's Algorithm function */
    prim(cost, n);

    return 0;
}
