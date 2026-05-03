#include <stdio.h>    // For file handling and input-output
#include <stdlib.h>   // For exit()
#include <time.h>     // For time measurement

#define MAX 10000     // Maximum array size


/* =========================================================
   Function: swap
   Purpose : Swap two numbers
   ========================================================= */
void swap(int *a, int *b)
{
    int temp;

    temp = *a;   // Store value of first number
    *a = *b;     // Copy second number into first
    *b = temp;   // Put temp value into second
}


/* =========================================================
   Function: partition
   Purpose : Place pivot element at correct position
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
            i++;  // Move index

            swap(&arr[i], &arr[j]); // Swap elements
        }
    }

    // Place pivot at correct position
    swap(&arr[i+1], &arr[high]);

    return i + 1; // Return pivot position
}


/* =========================================================
   Function: quickSort
   Purpose : Recursive Quick Sort
   ========================================================= */
void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pi;

        // Partition array
        pi = partition(arr, low, high);

        // Sort left side
        quickSort(arr, low, pi - 1);

        // Sort right side
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
        printf("%d ", arr[i]);

    printf("\n");
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    FILE *fp;          // File pointer
    int arr[MAX];
    int n, i;

    clock_t start, end;
    double time_taken;

    /* Open file in read mode */
    fp = fopen("input.txt", "r");

    if(fp == NULL)
    {
        printf("Error: File not found!\n");
        exit(1);
    }

    /* Read number of elements */
    fscanf(fp, "%d", &n);

    /* Read elements from file */
    for(i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp); // Close file

    printf("Elements read from file:\n");
    printArray(arr, n);

    /* Start time measurement */
    start = clock();

    quickSort(arr, 0, n-1);

    /* End time measurement */
    end = clock();

    printf("\nSorted Elements (Quick Sort):\n");
    printArray(arr, n);

    /* Calculate execution time */
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken to sort %d elements = %f seconds\n", n, time_taken);

    return 0;
}
