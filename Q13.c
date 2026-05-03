#include <stdio.h>

#define MAX 20

/* Queue for BFS */
int queue[MAX];
int front = -1;
int rear = -1;


/* =========================================================
   BFS FUNCTION

   Breadth First Search explores graph level by level.

   Steps:
   1. Start from source vertex.
   2. Visit all its adjacent vertices.
   3. Then visit vertices at next level.

   Uses Queue (FIFO).
   ========================================================= */
void BFS(int graph[MAX][MAX], int n, int start)
{
    int visited[MAX] = {0};
    int i;

    /* Enqueue start vertex */
    queue[++rear] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while(front != rear)
    {
        int vertex = queue[++front];
        printf("%d ", vertex);

        for(i=1;i<=n;i++)
        {
            if(graph[vertex][i] && !visited[i])
            {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}


/* =========================================================
   DFS FUNCTION

   Depth First Search explores graph deeply before backtracking.

   Steps:
   1. Visit starting vertex.
   2. Visit one adjacent vertex.
   3. Continue deeper until no more nodes.
   4. Backtrack and explore remaining nodes.

   Uses Recursion or Stack.
   ========================================================= */
void DFS(int graph[MAX][MAX], int visited[], int vertex, int n)
{
    printf("%d ", vertex);
    visited[vertex] = 1;

    for(int i=1;i<=n;i++)
    {
        if(graph[vertex][i] && !visited[i])
            DFS(graph, visited, i, n);
    }
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int graph[MAX][MAX];
    int visited[MAX] = {0};
    int n,i,j,start;

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("\nEnter adjacency matrix:\n");

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }

    printf("\nEnter starting vertex: ");
    scanf("%d",&start);

    /* DFS */
    printf("\nDFS Traversal: ");
    DFS(graph, visited, start, n);

    /* BFS */
    BFS(graph, n, start);

    printf("\n");

    return 0;
}
