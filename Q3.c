#include <stdio.h>      // For input-output functions
#include <stdlib.h>     // For rand() and srand()
#include <time.h>       // For time measurement

#define MAX 10000       // Maximum array size


/* =========================================================
   MERGE SORT ALGORITHM

   Working Principle:

   Merge Sort follows the Divide and Conquer technique.

   Steps:
   1. Divide the array into two halves.
   2. Recursively sort both halves.
   3. Merge the two sorted halves.

   Example:
   Array: 38 27 43 3 9

   Step1: Divide
   38 27 | 43 3 9

   Step2: Divide again
   38 | 27   43 | 3 9

   Step3: Sort and Merge
   27 38   3 9 43

   Step4: Final Merge
   3 9 27 38 43

   Time Complexity:
   Best Case   : O(n log n)
   Average Case: O(n log n)
   Worst Case  : O(n log n)
   ========================================================= */


/* =========================================================
   Function: merge
   Purpose : Merge two sorted subarrays
   ========================================================= */
void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;

    int n1 = mid - left + 1; // size of left subarray
    int n2 = right - mid;    // size of right subarray

    int L[5000], R[5000];    // temporary arrays

    /* Copy data into temporary arrays */
    for(i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for(j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];


    i = 0;
    j = 0;
    k = left;

    /* Merge the temporary arrays back */
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy remaining elements if any */
    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


/* =========================================================
   Function: mergeSort
   Purpose : Recursively divide array and sort
   ========================================================= */
void mergeSort(int arr[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        /* Sort first half */
        mergeSort(arr, left, mid);

        /* Sort second half */
        mergeSort(arr, mid + 1, right);

        /* Merge the sorted halves */
        merge(arr, left, mid, right);
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
    int arr[MAX];
    int n, i;

    clock_t start, end;
    double time_taken;

    printf("Enter number of elements: ");
    scanf("%d",&n);

    /* Generate random numbers */
    srand(time(0));

    for(i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000; // numbers between 0-999
    }

    printf("\nOriginal Array:\n");
    printArray(arr, n);

    /* Start time measurement */
    start = clock();

    mergeSort(arr, 0, n-1);

    /* End time measurement */
    end = clock();

    printf("\nSorted Array (Merge Sort):\n");
    printArray(arr, n);

    /* Calculate execution time */
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken to sort %d elements = %f seconds\n", n, time_taken);

    return 0;
}
