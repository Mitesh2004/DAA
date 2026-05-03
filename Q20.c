#include <stdio.h>
#include <stdlib.h>

#define N 4   // Fixed size for 4-Queens

int board[N];   // board[i] = column of queen in row i


/* ---------------------------------------------------------
   Function: isSafe

   Checks whether placing queen at (row, col) is safe

   Conditions:
   1. No queen in same column
   2. No queen in same diagonal
--------------------------------------------------------- */
int isSafe(int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        if(board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}


/* ---------------------------------------------------------
   Function: printSolution

   Prints one valid 4-queen configuration
--------------------------------------------------------- */
void printSolution()
{
    printf("\nSolution:\n");

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
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
   1. Try each column
   2. Check if safe
   3. Place queen
   4. Move to next row
   5. Backtrack if needed
--------------------------------------------------------- */
void solve(int row)
{
    if(row == N)
    {
        printSolution();
        return;
    }

    for(int col = 0; col < N; col++)
    {
        if(isSafe(row, col))
        {
            board[row] = col;
            solve(row + 1);
        }
    }
}


/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main()
{
    solve(0);
    return 0;
}
