#include <stdio.h>

#define MAX 20
#define INF 999999


/* =========================================================
   MATRIX CHAIN MULTIPLICATION (MCM)

   Problem:
   --------
   Given a sequence of matrices, determine the most efficient
   way to multiply them.

   Example:
   A1 (10×30)
   A2 (30×5)
   A3 (5×60)

   We can multiply in different ways:
   (A1A2)A3 or A1(A2A3)

   Goal:
   -----
   Find the order that minimizes scalar multiplications.

   Approach:
   ---------
   Dynamic Programming

   Steps:
   ------
   1. Store dimensions in array p[].
   2. m[i][j] stores minimum cost of multiplying matrices i..j.
   3. Try every possible split k between i and j.
   4. Choose minimum cost.

   Time Complexity:
   ----------------
   O(n^3)

   Space Complexity:
   -----------------
   O(n^2)
   ========================================================= */


/* Function to compute minimum multiplication cost */
int matrixChain(int p[], int n)
{
    int m[MAX][MAX];
    int i,j,k,L,q;

    /* Cost is zero when multiplying one matrix */
    for(i=1;i<n;i++)
        m[i][i] = 0;

    /* L = chain length */
    for(L=2; L<n; L++)
    {
        for(i=1; i<n-L+1; i++)
        {
            j = i + L - 1;
            m[i][j] = INF;

            for(k=i; k<=j-1; k++)
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n-1];
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int p[MAX];
    int n,i;

    printf("Enter number of matrices: ");
    scanf("%d",&n);

    printf("Enter dimensions array (size %d):\n", n+1);

    for(i=0;i<=n;i++)
        scanf("%d",&p[i]);

    int result = matrixChain(p, n+1);

    printf("\nMinimum number of multiplications = %d\n", result);

    return 0;
}
