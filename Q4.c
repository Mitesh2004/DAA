#include <stdio.h>

#define MAX 10


/* =========================================================
   STRASSEN'S MATRIX MULTIPLICATION

   Normal Matrix Multiplication:
   -----------------------------
   For two matrices A and B of size n×n:

   C[i][j] = Σ (A[i][k] * B[k][j])

   Time Complexity = O(n^3)


   Strassen's Idea:
   ----------------
   Divide matrices into 4 submatrices.

   A = |A11  A12|
       |A21  A22|

   B = |B11  B12|
       |B21  B22|

   Instead of performing 8 multiplications (standard method),
   Strassen uses only 7 multiplications.

   M1 = (A11 + A22)(B11 + B22)
   M2 = (A21 + A22) B11
   M3 = A11 (B12 − B22)
   M4 = A22 (B21 − B11)
   M5 = (A11 + A12) B22
   M6 = (A21 − A11)(B11 + B12)
   M7 = (A12 − A22)(B21 + B22)

   Then result submatrices are:

   C11 = M1 + M4 − M5 + M7
   C12 = M3 + M5
   C21 = M2 + M4
   C22 = M1 − M2 + M3 + M6

   Final matrix:

   C = |C11  C12|
       |C21  C22|

   Time Complexity improves to:
   O(n^2.81)
   ========================================================= */


/* =========================================================
   Function: addMatrix
   Purpose : Add two matrices
   C = A + B
   ========================================================= */
void addMatrix(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            C[i][j] = A[i][j] + B[i][j]; // Add corresponding elements
        }
    }
}


/* =========================================================
   Function: subMatrix
   Purpose : Subtract two matrices
   C = A - B
   ========================================================= */
void subMatrix(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            C[i][j] = A[i][j] - B[i][j]; // Subtract elements
        }
    }
}


/* =========================================================
   Function: strassen
   Purpose : Perform Strassen Matrix Multiplication

   Steps inside function:
   1. Divide matrices into four equal submatrices.
   2. Compute seven matrix multiplications (M1–M7).
   3. Combine them to form result matrix.
   ========================================================= */
void strassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    int i,j;

    /* Base case for recursion:
       If matrix size is 1×1 just multiply elements */
    if(n==1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;

    /* Declare sub matrices */
    int A11[MAX][MAX],A12[MAX][MAX],A21[MAX][MAX],A22[MAX][MAX];
    int B11[MAX][MAX],B12[MAX][MAX],B21[MAX][MAX],B22[MAX][MAX];

    int M1[MAX][MAX],M2[MAX][MAX],M3[MAX][MAX],M4[MAX][MAX];
    int M5[MAX][MAX],M6[MAX][MAX],M7[MAX][MAX];

    int T1[MAX][MAX],T2[MAX][MAX];

    /* Step 1: Divide matrices into 4 parts */
    for(i=0;i<k;i++)
    {
        for(j=0;j<k;j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    /* Step 2: Calculate M1 to M7 using Strassen formulas */

    addMatrix(A11,A22,T1,k);
    addMatrix(B11,B22,T2,k);
    strassen(T1,T2,M1,k);

    addMatrix(A21,A22,T1,k);
    strassen(T1,B11,M2,k);

    subMatrix(B12,B22,T2,k);
    strassen(A11,T2,M3,k);

    subMatrix(B21,B11,T2,k);
    strassen(A22,T2,M4,k);

    addMatrix(A11,A12,T1,k);
    strassen(T1,B22,M5,k);

    subMatrix(A21,A11,T1,k);
    addMatrix(B11,B12,T2,k);
    strassen(T1,T2,M6,k);

    subMatrix(A12,A22,T1,k);
    addMatrix(B21,B22,T2,k);
    strassen(T1,T2,M7,k);


    /* Step 3: Calculate result sub matrices */

    int C11[MAX][MAX],C12[MAX][MAX],C21[MAX][MAX],C22[MAX][MAX];

    addMatrix(M1,M4,T1,k);
    subMatrix(T1,M5,T2,k);
    addMatrix(T2,M7,C11,k);

    addMatrix(M3,M5,C12,k);

    addMatrix(M2,M4,C21,k);

    subMatrix(M1,M2,T1,k);
    addMatrix(T1,M3,T2,k);
    addMatrix(T2,M6,C22,k);


    /* Step 4: Combine sub matrices into final matrix */
    for(i=0;i<k;i++)
    {
        for(j=0;j<k;j++)
        {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int A[MAX][MAX],B[MAX][MAX],C[MAX][MAX];
    int n,i,j;

    printf("Enter order of matrix (power of 2): ");
    scanf("%d",&n);

    printf("\nEnter Matrix A:\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&A[i][j]);
        }
    }

    printf("\nEnter Matrix B:\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&B[i][j]);
        }
    }

    /* Perform Strassen Multiplication */
    strassen(A,B,C,n);

    printf("\nResult Matrix:\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
