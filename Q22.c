#include <stdio.h>
#include <string.h>

#define MAX 100

/* =========================================================
   ALGORITHM: LONGEST COMMON SUBSEQUENCE (LCS)

   Step 1: Start
   Step 2: Input two strings X and Y
   Step 3: Find lengths m and n of both strings

   Step 4: Create a DP table L[m+1][n+1]

   Step 5: Fill the table:
           - If i == 0 or j == 0 → L[i][j] = 0
           - If X[i-1] == Y[j-1]
                L[i][j] = L[i-1][j-1] + 1
           - Else
                L[i][j] = max(L[i-1][j], L[i][j-1])

   Step 6: L[m][n] contains length of LCS

   Step 7: Backtrack from L[m][n] to find LCS string:
           - If characters match → include in LCS
           - Else move in direction of larger value

   Step 8: Print LCS and its length
   Step 9: Stop

   Time Complexity: O(m × n)
   Space Complexity: O(m × n)
   ========================================================= */


/* Function to find and print LCS */
void LCS(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    int L[MAX][MAX];   // DP table

    int i, j;

    /* -------- Step 1: Build DP Table -------- */
    for(i = 0; i <= m; i++)
    {
        for(j = 0; j <= n; j++)
        {
            // Base case: first row & column = 0
            if(i == 0 || j == 0)
                L[i][j] = 0;

            // If characters match → take diagonal + 1
            else if(X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;

            // If not match → take maximum of top or left
            else
                L[i][j] = (L[i-1][j] > L[i][j-1]) ? L[i-1][j] : L[i][j-1];
        }
    }

    /* -------- Step 2: Reconstruct LCS -------- */
    int index = L[m][n];   // Length of LCS

    char lcs[index + 1];
    lcs[index] = '\0';     // Null terminate string

    i = m;
    j = n;

    // Trace back from bottom-right corner
    while(i > 0 && j > 0)
    {
        // If characters match → include in LCS
        if(X[i-1] == Y[j-1])
        {
            lcs[index-1] = X[i-1];
            i--;
            j--;
            index--;
        }
        // Move up if value above is greater
        else if(L[i-1][j] > L[i][j-1])
            i--;
        // Else move left
        else
            j--;
    }

    /* -------- Step 3: Output -------- */
    printf("\nLongest Common Subsequence = %s\n", lcs);
    printf("Length = %d\n", L[m][n]);
}


/* ---------------- MAIN FUNCTION ---------------- */
int main()
{
    char X[MAX], Y[MAX];

    printf("Enter first string: ");
    scanf("%s", X);

    printf("Enter second string: ");
    scanf("%s", Y);

    LCS(X, Y);

    return 0;
}
