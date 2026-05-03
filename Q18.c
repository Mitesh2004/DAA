#include <stdio.h>

#define MAX 20

int w[MAX];        // Array of elements (weights)
int x[MAX];        // Solution vector (0 or 1)
int n, target;


/* ---------------------------------------------------------
   Function: printSolution

   Prints the subset that satisfies the condition
--------------------------------------------------------- */
void printSolution()
{
    printf("Subset: ");

    for(int i = 0; i < n; i++)
    {
        if(x[i] == 1)
            printf("%d ", w[i]);
    }

    printf("\n");
}


/* ---------------------------------------------------------
   Function: sumOfSubsets

   s  = current sum
   k  = current index
   r  = remaining sum of elements

   Steps:
   1. Check if current sum == target → print solution
   2. Try including current element
   3. Try excluding current element
   4. Use bounding condition to reduce unnecessary calls
--------------------------------------------------------- */
void sumOfSubsets(int s, int k, int r)
{
    /* If current sum equals target */
    if(s == target)
    {
        printSolution();
        return;
    }

    /* If more elements exist */
    if(k < n)
    {
        /* Include current element */
        if(s + w[k] <= target)
        {
            x[k] = 1;
            sumOfSubsets(s + w[k], k + 1, r - w[k]);
        }

        /* Exclude current element */
        if(s + r - w[k] >= target)
        {
            x[k] = 0;
            sumOfSubsets(s, k + 1, r - w[k]);
        }
    }
}


/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main()
{
    int total = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
        total += w[i];   // Calculate total sum
    }

    printf("Enter target sum: ");
    scanf("%d", &target);

    sumOfSubsets(0, 0, total);

    return 0;
}
