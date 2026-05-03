#include <stdio.h>   // Standard input-output functions
#include <time.h>    // Used for measuring execution time

#define MAX 1000     // Maximum array size


/* =========================================================
   SELECTION SORT
   ---------------------------------------------------------
   Working Principle:
   1. Divide array into two parts:
      - Sorted part (left side)
      - Unsorted part (right side)

   2. In each iteration:
      - Find the smallest element from the unsorted part
      - Swap it with the first element of unsorted part

   3. After every pass one element is placed at correct position.

   Example:
   9 4 7 1

   Pass1 → smallest = 1 → swap with first
   1 4 7 9

   Pass2 → smallest = 4
   1 4 7 9

   Pass3 → smallest = 7

   Final → 1 4 7 9
   ========================================================= */
void selectionSort(int arr[], int n)
{
    int i, j, min_index, temp;

    // Outer loop controls number of passes
    for(i = 0; i < n-1; i++)
    {
        min_index = i; // assume current element is minimum

        // Find smallest element in remaining array
        for(j = i+1; j < n; j++)
        {
            if(arr[j] < arr[min_index])
                min_index = j;  // update index of smallest element
        }

        // Swap smallest element with current element
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}


/* =========================================================
   INSERTION SORT
   ---------------------------------------------------------
   Working Principle:
   Works like arranging playing cards.

   1. Assume first element is already sorted.
   2. Take next element and insert it into correct
      position in sorted part.
   3. Shift elements if required.

   Example:
   8 3 5 2

   Step1 → 8
   Step2 → insert 3 before 8 → 3 8
   Step3 → insert 5 → 3 5 8
   Step4 → insert 2 → 2 3 5 8
   ========================================================= */
void insertionSort(int arr[], int n)
{
    int i, j, key;

    // Start from second element
    for(i = 1; i < n; i++)
    {
        key = arr[i]; // element to be placed correctly
        j = i - 1;

        // Shift larger elements to right
        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }

        // Insert element in correct position
        arr[j+1] = key;
    }
}


/* =========================================================
   HEAP SORT
   ---------------------------------------------------------
   Working Principle:

   1. Convert array into a Max Heap
      (parent node greater than children)

   2. Root of heap contains largest element.

   3. Swap root with last element.

   4. Reduce heap size and heapify again.

   5. Repeat until array is sorted.

   Example Heap:

          50
        /    \
      30      40
     /  \
    10  20

   Root always contains maximum element.
   ========================================================= */


/* Function to maintain heap property */
void heapify(int arr[], int n, int i)
{
    int largest = i;      // assume root is largest
    int left = 2*i + 1;   // left child index
    int right = 2*i + 2;  // right child index
    int temp;

    // If left child is larger than root
    if(left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger
    if(right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root then swap
    if(largest != i)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the subtree
        heapify(arr, n, largest);
    }
}

/* Heap Sort function */
void heapSort(int arr[], int n)
{
    int i, temp;

    // Step 1: Build heap
    for(i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Step 2: Extract elements from heap
    for(i = n-1; i > 0; i--)
    {
        // Move current root to end
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Restore heap property
        heapify(arr, i, 0);
    }
}


/* =========================================================
   RADIX SORT
   ---------------------------------------------------------
   Working Principle:

   Radix sort sorts numbers digit by digit.

   Steps:
   1. Find maximum number.
   2. Sort numbers based on unit digit.
   3. Sort numbers based on tens digit.
   4. Continue until highest digit.

   Example:
   170 45 75 90

   Pass1 (unit digit)
   170 90 45 75

   Pass2 (tens digit)
   170 45 75 90

   Pass3 (hundreds digit)
   45 75 90 170
   ========================================================= */


/* Find maximum element */
int getMax(int arr[], int n)
{
    int max = arr[0];

    for(int i = 1; i < n; i++)
        if(arr[i] > max)
            max = arr[i];

    return max;
}


/* Counting sort used inside radix sort */
void countSort(int arr[], int n, int exp)
{
    int output[MAX];
    int count[10] = {0};
    int i;

    // Count digit occurrences
    for(i = 0; i < n; i++)
        count[(arr[i]/exp)%10]++;

    // Convert to actual positions
    for(i = 1; i < 10; i++)
        count[i] += count[i-1];

    // Build output array
    for(i = n-1; i >= 0; i--)
    {
        output[count[(arr[i]/exp)%10] - 1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }

    // Copy sorted numbers back
    for(i = 0; i < n; i++)
        arr[i] = output[i];
}


/* Radix sort main function */
void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);

    // Sort for every digit
    for(int exp = 1; max/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}


/* Copy array so every algorithm gets same data */
void copyArray(int a[], int b[], int n)
{
    for(int i = 0; i < n; i++)
        b[i] = a[i];
}







/* Function to display array elements */
void printArray(int arr[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);   // Print each element of the array
    }

    printf("\n"); // Move cursor to next line after printing array
}



/* =========================================================
   MAIN FUNCTION
   ========================================================= */
int main()
{
    int arr[MAX], temp[MAX];
    int n, i;

    clock_t start, end;
    double time_taken;

    printf("Enter number of elements: ");
    scanf("%d",&n);

    printf("Enter numbers:\n");

    for(i = 0; i < n; i++)
        scanf("%d",&arr[i]);

    /* Selection Sort */
    copyArray(arr,temp,n);
    start = clock();
    selectionSort(temp,n);
    end = clock();

    time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
   // printf("\nSelection Sort Time = %f",time_taken);
printf("\nSelection Sort Output:\n");
printArray(temp,n);
printf("Selection Sort Time = %f",time_taken);
    
    /* Insertion Sort */
    copyArray(arr,temp,n);
    start = clock();
    insertionSort(temp,n);
    end = clock();

    time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
   // printf("\nInsertion Sort Time = %f",time_taken);
printf("\nInsertion Sort Output:\n");
printArray(temp,n);
printf("Insertion Sort Time = %f",time_taken); 

    /* Heap Sort */
    copyArray(arr,temp,n);
    start = clock();
    heapSort(temp,n);
    end = clock();

    time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
   // printf("\nHeap Sort Time = %f",time_taken);
printf("\nHeap Sort Output:\n");
printArray(temp,n);
printf("Heap Sort Time = %f",time_taken);
    /* Radix Sort */
    copyArray(arr,temp,n);
    start = clock();
    radixSort(temp,n);
    end = clock();

    time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
   // printf("\nRadix Sort Time = %f\n",time_taken);
printf("\nRadix Sort Output:\n");
printArray(temp,n);
printf("Radix Sort Time = %f\n",time_taken);
    return 0;
}
