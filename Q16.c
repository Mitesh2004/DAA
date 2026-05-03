#include <stdio.h>

#define MAX 20
#define INF 9999

/* ---------------------------------------------------------
   TSP using Nearest Neighbor (Greedy Method)

   Idea:
   -----
   1. Start from a chosen city.
   2. Visit the nearest unvisited city.
   3. Repeat until all cities are visited.
   4. Return to the starting city.

   This algorithm is greedy because it always chooses
   the nearest available city.
--------------------------------------------------------- */

void tsp(int graph[MAX][MAX], int n)
{
    int visited[MAX] = {0};
    int i,city=0,nextCity;
    int minDistance,totalCost=0;

    printf("Tour Path:\n");

    visited[city] = 1;     // Start from city 0
    printf("%d ", city);

    for(i=1;i<n;i++)
    {
        minDistance = INF;
        nextCity = -1;

        /* Find nearest unvisited city */
        for(int j=0;j<n;j++)
        {
            if(graph[city][j] && !visited[j])
            {
                if(graph[city][j] < minDistance)
                {
                    minDistance = graph[city][j];
                    nextCity = j;
                }
            }
        }

        visited[nextCity] = 1;
        printf("-> %d ", nextCity);

        totalCost += minDistance;
        city = nextCity;
    }

    /* Return to starting city */
    totalCost += graph[city][0];
    printf("-> 0");

    printf("\n\nMinimum Travel Cost = %d\n", totalCost);
}


/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main()
{
    int graph[MAX][MAX];
    int n,i,j;

    printf("Enter number of cities: ");
    scanf("%d",&n);

    printf("Enter cost matrix:\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }

    tsp(graph,n);

    return 0;
}

/*
The Travelling Salesman Problem (TSP) is a classic algorithmic problem aiming to find the shortest possible route that visits a set of cities exactly once and returns to the origin city.

*/
