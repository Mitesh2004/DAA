#include <stdio.h>

#define MAX 20
#define INF 9999


/* =========================================================
   OPTIMAL BINARY SEARCH TREE (OBST)

   Purpose:
   --------
   OBST minimizes the expected search cost of a Binary
   Search Tree based on access probabilities.

   Idea:
   -----
   Instead of building a BST normally, we choose the root
   that minimizes total search cost.

   Dynamic Programming Approach:
   ------------------------------
   cost[i][j] = minimum search cost of keys i..j

   Steps:
   ------
   1. Calculate weight sum of probabilities.
   2. Try every key as root.
   3. Choose the root giving minimum cost.

   Time Complexity:
   ----------------
   Best Case  : O(n^2)
   Worst Case : O(n^3)

   Space Complexity:
   -----------------
   O(n^2)
   ========================================================= */


/* Function to find sum of frequencies */
int sum(int freq[], int i, int j)
{
    int s = 0;
    for(int k=i; k<=j; k++)
        s += freq[k];

    return s;
}


/* Function to compute optimal cost */
int optimalBST(int keys[], int freq[], int n)
{
    int cost[MAX][MAX];

    int i,j,r,L;

    /* cost[i][i] = frequency of single key */
    for(i=0;i<n;i++)
        cost[i][i] = freq[i];

    /* L = chain length */
    for(L=2; L<=n; L++)
    {
        for(i=0; i<=n-L; i++)
        {
            j = i + L - 1;
            cost[i][j] = INF;

            int fsum = sum(freq,i,j);

            /* Try every key as root */
            for(r=i; r<=j; r++)
            {
                int c = 0;

                if(r>i)
                    c += cost[i][r-1];

                if(r<j)
                    c += cost[r+1][j];

                c += fsum;

                if(c < cost[i][j])
                    cost[i][j] = c;
            }
        }
    }

    return cost[0][n-1];
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int keys[MAX], freq[MAX];
    int n,i;

    printf("Enter number of keys: ");
    scanf("%d",&n);

    printf("Enter keys:\n");

    for(i=0;i<n;i++)
        scanf("%d",&keys[i]);

    printf("Enter frequencies:\n");

    for(i=0;i<n;i++)
        scanf("%d",&freq[i]);

    int cost = optimalBST(keys,freq,n);

    printf("\nOptimal Binary Search Tree Cost = %d\n",cost);

    printf("\nBest Case Complexity  = O(n^2)");
    printf("\nWorst Case Complexity = O(n^3)\n");

    return 0;
}
