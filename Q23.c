#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX] = {0};

int queue[MAX];
int front = -1, rear = -1;

/*
Live Node → Node that is generated but not yet expanded
E-node (Expansion node) → Node currently being expanded
Dead Node → Node that is either:
	Already expanded OR
	Not useful (no further expansion possible)
*/
/* =========================================================
   ALGORITHM

   Step 1: Input graph using adjacency matrix
   Step 2: Select starting node
   Step 3: Insert starting node into queue (Live node)
   Step 4: Mark it as visited

   Step 5: Repeat until queue is empty
       a) Remove node from queue → this is E-node
       b) Explore all adjacent nodes
       c) Add unvisited neighbors to queue → Live nodes
       d) Mark current node as Dead node

   Step 6: Continue until all nodes processed
========================================================= */


/* ---------------------------------------------------------
   Function: enqueue
   Purpose : Insert node into queue (Live node)
--------------------------------------------------------- */
void enqueue(int v)
{
    queue[++rear] = v;
}


/* ---------------------------------------------------------
   Function: dequeue
   Purpose : Remove node from queue (becomes E-node)
--------------------------------------------------------- */
int dequeue()
{
    return queue[++front];
}


/* ---------------------------------------------------------
   Function: displayLiveNodes
   Purpose : Display nodes currently in queue
             (These are Live Nodes)
--------------------------------------------------------- */
void displayLiveNodes()
{
    printf("Live Nodes: ");

    for(int i = front + 1; i <= rear; i++)
        printf("%d ", queue[i]);

    printf("\n");
}


/* =========================================================
   MAIN FUNCTION
========================================================= */
int main()
{
    int n, start;

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

    printf("Enter starting node: ");
    scanf("%d", &start);


    /* Step 1: Insert starting node into queue */
    enqueue(start);

    /* Step 2: Mark as visited */
    visited[start] = 1;

    printf("\nTraversal with Node Types:\n");


    /* Step 3: Process until queue becomes empty */
    while(front != rear)
    {
        /* Remove node from queue → E-node */
        int current = dequeue();

        printf("\nE-node (Expanding): %d\n", current);


        /* Step 4: Explore all adjacent nodes */
        for(int i = 0; i < n; i++)
        {
            if(graph[current][i] == 1 && !visited[i])
            {
                /* Add to queue → becomes Live node */
                enqueue(i);

                visited[i] = 1;
            }
        }

        /* Display Live Nodes (nodes still in queue) */
        displayLiveNodes();

        /* Step 5: Current node is now Dead node */
        printf("Dead Node: %d\n", current);
    }

    return 0;
}
