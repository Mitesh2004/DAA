#include <stdio.h>

#define MAX 20
#define INF 9999

/* =========================================================
   KRUSKAL'S ALGORITHM

   Purpose:
   --------
   To find the Minimum Cost Spanning Tree (MST) of a graph.

   Minimum Spanning Tree:
   ----------------------
   A spanning tree connects all vertices of a graph
   with minimum possible total edge weight and no cycles.

   Steps of Kruskal's Algorithm:
   -----------------------------
   1. Sort all edges in increasing order of weight.
   2. Select the smallest edge.
   3. Check if it forms a cycle.
   4. If it does NOT form a cycle, include it in MST.
   5. Repeat until (V - 1) edges are selected.

   Time Complexity:
   ----------------
   O(E log E)
   where E = number of edges
   ========================================================= */


/* =========================================================
   Function: find
   Purpose : Find the parent of a node (used in union-find)
   ========================================================= */
int find(int parent[], int i)
{
    while(parent[i])
        i = parent[i];

    return i;
}


/* =========================================================
   Function: unionSet
   Purpose : Join two sets (used to avoid cycles)
   ========================================================= */
void unionSet(int parent[], int i, int j)
{
    parent[j] = i;
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int cost[MAX][MAX];     // Cost adjacency matrix
    int parent[MAX];        // Parent array for union-find
    int i, j, n;
    int u, v;
    int min, mincost = 0;
    int edge_count = 0;

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("\nEnter the cost adjacency matrix:\n");

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%d",&cost[i][j]);

            /* Replace 0 with INF except diagonal */
            if(cost[i][j]==0)
                cost[i][j]=INF;
        }
    }

    /* Initialize parent array */
    for(i=1;i<=n;i++)
        parent[i]=0;

    printf("\nEdges in Minimum Spanning Tree:\n");

    /* Kruskal algorithm continues until n-1 edges are selected */
    while(edge_count < n-1)
    {
        min = INF;

        /* Find the smallest edge */
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(cost[i][j] < min)
                {
                    min = cost[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        /* Find parent vertices to check cycle */
        int a = find(parent,u);
        int b = find(parent,v);

        /* If including this edge does not create cycle */
        if(a != b)
        {
            printf("%d edge (%d,%d) = %d\n",edge_count+1,u,v,min);

            mincost += min;  // Add cost to MST
            edge_count++;

            unionSet(parent,a,b);
        }

        /* Mark edge as used */
        cost[u][v] = cost[v][u] = INF;
    }

    printf("\nMinimum Cost = %d\n",mincost);

    return 0;
}
