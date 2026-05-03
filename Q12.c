#include <stdio.h>
#include <string.h>

#define MAX 100


/* =========================================================
   LONGEST COMMON SUBSEQUENCE (LCS)

   Problem:
   --------
   Given two sequences, find the length of the longest
   subsequence that appears in both sequences.

   Example:
   String1 = "ABCBDAB"
   String2 = "BDCAB"

   LCS = "BCAB"
   Length = 4

   Approach:
   ---------
   Dynamic Programming

   Idea:
   -----
   Let L[i][j] represent the length of LCS of
   first i characters of string1 and first j characters of string2.

   If characters match:
   L[i][j] = L[i-1][j-1] + 1

   If characters do not match:
   L[i][j] = max(L[i-1][j], L[i][j-1])

   Time Complexity:
   ----------------
   O(m × n)

   Space Complexity:
   -----------------
   O(m × n)
   ========================================================= */


/* Function to find maximum of two numbers */
int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}


/* Function to calculate LCS length */
int LCSLength(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    int L[MAX][MAX];

    int i,j;

    /* Initialize first row and column with 0 */
    for(i=0;i<=m;i++)
        L[i][0] = 0;

    for(j=0;j<=n;j++)
        L[0][j] = 0;

    /* Fill DP table */
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }

    return L[m][n];
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    char X[MAX], Y[MAX];

    printf("Enter first string: ");
    scanf("%s",X);

    printf("Enter second string: ");
    scanf("%s",Y);

    int length = LCSLength(X,Y);

    printf("\nLength of Longest Common Subsequence = %d\n",length);

    return 0;
}
