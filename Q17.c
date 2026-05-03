#include <stdio.h>

#define MAX 20


/* =========================================================
   GRAPH COLORING USING BACKTRACKING

   Goal:
   -----
   Assign colors to vertices such that:
   - No two adjacent vertices have the same color

   Approach:
   ---------
   1. Try assigning colors one by one to each vertex.
   2. Check if the color is safe.
   3. If safe → assign and move to next vertex.
   4. If not → try next color (backtracking).
   ========================================================= */


/* ---------------------------------------------------------
   Function: isSafe

   Checks whether assigning color 'c' to vertex 'v' is valid.

   Condition:
   - No adjacent vertex should have same color
--------------------------------------------------------- */
int isSafe(int graph[MAX][MAX], int color[], int v, int c, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(graph[v][i] == 1 && color[i] == c)
            return 0;   // Not safe
    }
    return 1;   // Safe
}


/* ---------------------------------------------------------
   Function: solve

   Recursive function to assign colors to vertices.

   Steps:
   1. If all vertices are colored → return success
   2. Try all colors for current vertex
   3. Check safety
   4. Assign and recurse
   5. If fails → backtrack
--------------------------------------------------------- */
int solve(int graph[MAX][MAX], int m, int color[], int v, int n)
{
    if(v == n)
        return 1;   // All vertices colored

    for(int c = 1; c <= m; c++)
    {
        if(isSafe(graph, color, v, c, n))
        {
            color[v] = c;

            if(solve(graph, m, color, v + 1, n))
                return 1;

            color[v] = 0;  // Backtrack
        }
    }

    return 0;   // No solution
}


/* ---------------------------------------------------------
   Function: graphColoring

   Initializes color array and starts recursion
--------------------------------------------------------- */
void graphColoring(int graph[MAX][MAX], int n, int m)
{
    int color[MAX] = {0};

    if(!solve(graph, m, color, 0, n))
    {
        printf("\nNo solution exists\n");
        return;
    }

    printf("\nColor Assignment:\n");

    for(int i = 0; i < n; i++)
        printf("Vertex %d → Color %d\n", i, color[i]);
}


/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main()
{
    int graph[MAX][MAX];
    int n, m;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter number of colors: ");
    scanf("%d", &m);

    graphColoring(graph, n, m);

    return 0;
}
