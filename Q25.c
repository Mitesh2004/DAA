#include <stdio.h>

/* =========================================================
   0/1 KNAPSACK PROBLEM USING DYNAMIC PROGRAMMING

   PROBLEM:
   --------
   - Given n items with weights and profits
   - Knapsack capacity = W
   - Each item can be selected (1) or not selected (0)
   - Maximize total profit without exceeding capacity

   APPROACH:
   ---------
   Dynamic Programming

   ALGORITHM:
   ----------
   Step 1: Start
   Step 2: Input number of items (n)
   Step 3: Input weights[] and profits[]
   Step 4: Input capacity W

   Step 5: Create DP table dp[n+1][W+1]

   Step 6: Initialize:
           - dp[i][0] = 0  (no capacity → no profit)
           - dp[0][w] = 0  (no items → no profit)

   Step 7: Fill table:
           For each item i = 1 to n
           For each capacity w = 1 to W

           If weight[i-1] <= w:
               dp[i][w] = max(
                   profit[i-1] + dp[i-1][w - weight[i-1]],
                   dp[i-1][w]
               )
           Else:
               dp[i][w] = dp[i-1][w]

   Step 8: Result = dp[n][W]

   Step 9: Stop

   Time Complexity: O(n × W)
   Space Complexity: O(n × W)
   ========================================================= */


/* Function to find maximum of two numbers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int n, W;

    /* Step 2: Input number of items */
    printf("Enter number of items: ");
    scanf("%d", &n);

    int weight[n], profit[n];

    /* Step 3: Input weights */
    printf("Enter weights of items:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    /* Step 3: Input profits */
    printf("Enter profits of items:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &profit[i]);

    /* Step 4: Input capacity */
    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);

    /* Step 5: Create DP table */
    int dp[n+1][W+1];

    /* Step 6: Initialize table */
    for(int i = 0; i <= n; i++)
    {
        for(int w = 0; w <= W; w++)
        {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
        }
    }

    /* Step 7: Fill DP table */
    for(int i = 1; i <= n; i++)
    {
        for(int w = 1; w <= W; w++)
        {
            /* If current item can be included */
            if(weight[i-1] <= w)
            {
                dp[i][w] = max(
                    profit[i-1] + dp[i-1][w - weight[i-1]], // include item
                    dp[i-1][w]                              // exclude item
                );
            }
            else
            {
                /* Cannot include item */
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    /* Step 8: Print result */
    printf("\nMaximum Profit = %d\n", dp[n][W]);

    return 0;
}
