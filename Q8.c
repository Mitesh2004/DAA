#include <stdio.h>

#define MAX 20

/* =========================================================
   FRACTIONAL KNAPSACK USING GREEDY METHOD

   Problem:
   --------
   We are given:
   - n items
   - Each item has weight and profit
   - A knapsack with capacity W

   Goal:
   -----
   Maximize profit without exceeding capacity.

   Greedy Idea:
   ------------
   Select items with highest profit/weight ratio first.

   Steps:
   ------
   1. Compute profit/weight ratio for each item.
   2. Sort items in descending order of ratio.
   3. Pick items until knapsack is full.
   4. If remaining capacity is small, take fraction of item.

   Time Complexity:
   ----------------
   O(n log n) for sorting
   ========================================================= */


/* =========================================================
   Structure to store item information
   ========================================================= */
struct item
{
    int weight;
    int profit;
    float ratio;
};


/* =========================================================
   Function: sortItems
   Purpose : Sort items based on profit/weight ratio
   ========================================================= */
void sortItems(struct item arr[], int n)
{
    int i,j;
    struct item temp;

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j].ratio < arr[j+1].ratio)
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


/* =========================================================
   Function: knapsack
   Purpose : Apply greedy method to maximize profit
   ========================================================= */
void knapsack(struct item arr[], int n, int capacity)
{
    int i;
    float totalProfit = 0.0;

    for(i=0;i<n;i++)
    {
        /* If full item can be taken */
        if(arr[i].weight <= capacity)
        {
            capacity -= arr[i].weight;
            totalProfit += arr[i].profit;

            printf("Item %d taken completely\n", i+1);
        }

        /* Take fraction of item */
        else
        {
            float fraction = (float)capacity / arr[i].weight;

            totalProfit += arr[i].profit * fraction;

            printf("Item %d taken fractionally (%.2f part)\n", i+1, fraction);

            break;
        }
    }

    printf("\nMaximum Profit = %.2f\n", totalProfit);
}

//10 + 20 + 20 (2/3 of item3)
//60 + 100 + 80 = 240

/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    struct item arr[MAX];
    int n,i,capacity;

    printf("Enter number of items: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter profit and weight of item %d: ",i+1);
        scanf("%d %d",&arr[i].profit,&arr[i].weight);

        /* Calculate profit/weight ratio */
        arr[i].ratio = (float)arr[i].profit / arr[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%d",&capacity);

    /* Sort items based on ratio */
    sortItems(arr,n);

    /* Apply greedy knapsack */
    knapsack(arr,n,capacity);

    return 0;
}
