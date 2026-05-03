#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define N 10

/* =========================================================
   TRAVELLING SALESMAN PROBLEM (TSP)

   - Given n cities and a cost matrix
   - Visit each city exactly once
   - Return to starting city
   - Objective: Find minimum cost tour

   It is an NP-Hard problem
   ========================================================= */


/* =========================================================
   LCBB (Least Cost Branch and Bound)

   - Uses State Space Tree
   - Each node represents partial solution
   - Uses lower bound (matrix reduction)
   - Expands least cost node first
   - Prunes non-promising paths
   ========================================================= */


/* =========================================================
   NODE STRUCTURE

   path           → stores path of cities
   reducedMatrix  → cost matrix after reduction
   cost           → lower bound cost
   vertex         → current city
   level          → number of cities visited
   ========================================================= */
typedef struct Node {
    int path[N];
    int reducedMatrix[N][N];
    int cost;
    int vertex;
    int level;
} Node;


/* =========================================================
   FUNCTION: Create New Node

   Steps:
   1. Copy parent path
   2. Add new city
   3. Copy matrix
   4. Mark visited row & column as INF
   ========================================================= */
Node* newNode(int parentMatrix[N][N], int path[], int level, int i, int j, int n)
{
    Node* node = (Node*)malloc(sizeof(Node));

    // Copy path
    memcpy(node->path, path, sizeof(node->path));

    // Add current city
    if (level != 0)
        node->path[level] = j;

    // Copy matrix
    for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
            node->reducedMatrix[x][y] = parentMatrix[x][y];

    // Mark row & column as visited (set to INF)
    for (int k = 0; k < n; k++) {
        node->reducedMatrix[i][k] = INT_MAX;
        node->reducedMatrix[k][j] = INT_MAX;
    }

    // Prevent returning to start before visiting all cities
    node->reducedMatrix[j][0] = INT_MAX;

    node->level = level;
    node->vertex = j;

    return node;
}


/* =========================================================
   FUNCTION: Reduce Matrix (Lower Bound Calculation)

   Steps:
   1. Row reduction → subtract minimum element
   2. Column reduction → subtract minimum element
   3. Add reductions → cost (lower bound)
   ========================================================= */
int reduceMatrix(int matrix[N][N], int n)
{
    int row[N], col[N];
    int cost = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        row[i] = INT_MAX;

        for (int j = 0; j < n; j++)
            if (matrix[i][j] < row[i])
                row[i] = matrix[i][j];

        if (row[i] != INT_MAX && row[i] != 0) {
            for (int j = 0; j < n; j++)
                if (matrix[i][j] != INT_MAX)
                    matrix[i][j] -= row[i];

            cost += row[i];
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        col[j] = INT_MAX;

        for (int i = 0; i < n; i++)
            if (matrix[i][j] < col[j])
                col[j] = matrix[i][j];

        if (col[j] != INT_MAX && col[j] != 0) {
            for (int i = 0; i < n; i++)
                if (matrix[i][j] != INT_MAX)
                    matrix[i][j] -= col[j];

            cost += col[j];
        }
    }

    return cost;
}


/* =========================================================
   FUNCTION: Solve TSP using LCBB

   ALGORITHM:

   1. Create root node
   2. Reduce matrix → initial lower bound
   3. Insert into priority queue
   4. Repeat:
      - Select node with minimum cost
      - If all cities visited:
          → add return cost → solution found
      - Else:
          → generate child nodes (branch)
          → calculate cost:
             cost = parent cost +
                    reduced edge cost +
                    reduction cost
          → insert into queue
   5. Print minimum cost
   ========================================================= */
void solveTSP(int costMatrix[N][N], int n)
{
    int path[N];
    memset(path, -1, sizeof(path));

    Node* pq[1000];   // simple priority queue
    int size = 0;

    // Step 1: Create root node
    Node* root = newNode(costMatrix, path, 0, -1, 0, n);

    // Step 2: Initial reduction
    root->cost = reduceMatrix(root->reducedMatrix, n);

    pq[size++] = root;

    int minCost = INT_MAX;

    while (size > 0)
    {
        // Step 3: Select minimum cost node
        int minIndex = 0;
        for (int i = 1; i < size; i++)
            if (pq[i]->cost < pq[minIndex]->cost)
                minIndex = i;

        Node* min = pq[minIndex];

        // Remove from queue
        for (int i = minIndex; i < size - 1; i++)
            pq[i] = pq[i + 1];
        size--;

        int i = min->vertex;

        // Step 4: If all cities visited
        if (min->level == n - 1)
        {
            // Add return cost to starting city
            minCost = min->cost + costMatrix[i][0];
            break;
        }

        // Step 5: Expand child nodes
        for (int j = 0; j < n; j++)
        {
            if (min->reducedMatrix[i][j] != INT_MAX)
            {
                Node* child = newNode(min->reducedMatrix,
                                      min->path,
                                      min->level + 1,
                                      i, j, n);

                // Cost calculation (LCBB formula)
                child->cost = min->cost +
                              min->reducedMatrix[i][j] +
                              reduceMatrix(child->reducedMatrix, n);

                pq[size++] = child;
            }
        }
    }

    printf("\nMinimum Cost = %d\n", minCost);
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int n, costMatrix[N][N];

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &costMatrix[i][j]);

    solveTSP(costMatrix, n);

    return 0;
}
