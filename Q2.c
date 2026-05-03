#include <stdio.h>      // For printf()
#include <stdlib.h>     // For rand() and srand()
#include <time.h>       // For clock() and time()

#define MAX 10000       // Maximum size of array


/* =========================================================
   Function: swap
   Purpose : Swap two elements
   ========================================================= */
void swap(int *a, int *b)
{
    int temp;

    temp = *a;   // Store value of a
    *a = *b;     // Copy value of b to a
    *b = temp;   // Copy temp value to b
}


/* =========================================================
   Function: partition
   Purpose : Rearrange elements around pivot

   Working:
   1. Select last element as pivot.
   2. Place pivot at correct sorted position.
   3. Elements smaller than pivot go left.
   4. Elements greater go right.
   ========================================================= */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];   // Choose last element as pivot
    int i = low - 1;         // Index of smaller element
    int j;

    for(j = low; j < high; j++)
    {
        // If current element is smaller than pivot
        if(arr[j] < pivot)
        {
            i++;   // Move index of smaller element

            swap(&arr[i], &arr[j]);  // Swap elements
        }
    }

    // Place pivot in correct position
    swap(&arr[i + 1], &arr[high]);

    return (i + 1);   // Return pivot index
}


/* =========================================================
   Function: quickSort
   Purpose : Sort array using Quick Sort (recursive)

   Working:
   1. Choose pivot element.
   2. Partition array around pivot.
   3. Recursively apply quick sort to left and right parts.
   ========================================================= */
void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pi;

        // Partitioning index
        pi = partition(arr, low, high);

        // Sort left part
        quickSort(arr, low, pi - 1);

        // Sort right part
        quickSort(arr, pi + 1, high);
    }
}


/* =========================================================
   Function: printArray
   Purpose : Display array elements
   ========================================================= */
void printArray(int arr[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int arr[MAX];
    int n, i;

    clock_t start, end;
    double time_taken;

    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    /* Generate random numbers */
    srand(time(0));   // Seed random generator

    for(i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;   // Generate random numbers 0-999
    }

    printf("\nGenerated Elements:\n");
    printArray(arr, n);

    /* Start time measurement */
    start = clock();

    quickSort(arr, 0, n-1);

    /* End time measurement */
    end = clock();

    printf("\nSorted Elements (Quick Sort):\n");
    printArray(arr, n);

    /* Calculate time taken */
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken to sort %d elements = %f seconds\n", n, time_taken);

    return 0;
}
