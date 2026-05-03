#include <stdio.h>

#define MAX 20
#define INF 9999


/* =========================================================
   DIJKSTRA'S ALGORITHM

   Purpose:
   --------
   To find the shortest path from a source vertex
   to all other vertices in a weighted graph.

   Conditions:
   -----------
   - Graph must have non-negative weights.
   - Works for directed and undirected graphs.

   Working Principle:
   ------------------
   1. Start from the source vertex.
   2. Assign distance = 0 to source, INF to others.
   3. Select the vertex with the smallest distance.
   4. Update distances of its adjacent vertices.
   5. Mark the vertex as visited.
   6. Repeat until all vertices are visited.

   Time Complexity:
   ----------------
   O(V^2) using adjacency matrix
   ========================================================= */


/* =========================================================
   Function: dijkstra
   Purpose : Find shortest path from source vertex
   ========================================================= */
void dijkstra(int cost[MAX][MAX], int n, int source)
{
    int dist[MAX];      // Stores shortest distance from source
    int visited[MAX];   // Keeps track of visited vertices
    int i, j, u;
    int min;

    /* Initialize distances */
    for(i = 1; i <= n; i++)
    {
        dist[i] = cost[source][i];
        visited[i] = 0;
    }

    dist[source] = 0;   // Distance to source is always 0
    visited[source] = 1;

    /* Repeat for remaining vertices */
    for(i = 1; i < n; i++)
    {
        min = INF;

        /* Find unvisited vertex with smallest distance */
        for(j = 1; j <= n; j++)
        {
            if(!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        visited[u] = 1;   // Mark vertex as visited

        /* Update distances of adjacent vertices */
        for(j = 1; j <= n; j++)
        {
            if(!visited[j] && (dist[u] + cost[u][j] < dist[j]))
            {
                dist[j] = dist[u] + cost[u][j];
            }
        }
    }

    /* Display shortest distances */
    printf("\nShortest distances from vertex %d:\n", source);

    for(i = 1; i <= n; i++)
    {
        printf("Distance to vertex %d = %d\n", i, dist[i]);
    }
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int cost[MAX][MAX];
    int n, i, j, source;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter cost adjacency matrix:\n");

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            scanf("%d", &cost[i][j]);

            /* Replace 0 with INF except diagonal */
            if(cost[i][j] == 0 && i != j)
                cost[i][j] = INF;
        }
    }

    printf("\nEnter source vertex: ");
    scanf("%d", &source);

    /* Call Dijkstra function */
    dijkstra(cost, n, source);

    return 0;
}
