#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int board[MAX];   // board[i] = column position of queen in row i
int n;


/* ---------------------------------------------------------
   Function: isSafe

   Checks whether placing a queen at (row, col) is safe.

   Conditions:
   1. No queen in same column
   2. No queen in same diagonal
--------------------------------------------------------- */
int isSafe(int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        /* Check same column */
        if(board[i] == col)
            return 0;

        /* Check diagonals */
        if(abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}


/* ---------------------------------------------------------
   Function: printSolution

   Prints the board configuration
--------------------------------------------------------- */
void printSolution()
{
    printf("\nSolution:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}


/* ---------------------------------------------------------
   Function: solve

   Recursive function to place queens row by row

   Steps:
   1. Try placing queen in each column
   2. Check if safe
   3. Place queen and recurse
   4. If fails → backtrack
--------------------------------------------------------- */
void solve(int row)
{
    if(row == n)
    {
        printSolution();
        return;
    }

    for(int col = 0; col < n; col++)
    {
        if(isSafe(row, col))
        {
            board[row] = col;

            solve(row + 1);

            /* Backtracking happens automatically */
        }
    }
}


/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main()
{
    printf("Enter number of queens: ");
    scanf("%d", &n);

    solve(0);

    return 0;
}
