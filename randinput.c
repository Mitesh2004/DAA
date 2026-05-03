#include <stdio.h>   // For file handling functions
#include <stdlib.h>  // For rand() and srand()
#include <time.h>    // For time() used in random seed

int main()
{
    FILE *fp;   // File pointer
    int n, i;

    printf("Enter number of elements to generate: ");
    scanf("%d", &n);

    // Open file in write mode
    fp = fopen("input.txt", "w");

    if(fp == NULL)
    {
        printf("Error creating file!\n");
        return 1;
    }

    srand(time(0));   // Initialize random seed using current time

    // Write number of elements first
    fprintf(fp, "%d\n", n);

    // Generate and write random numbers
    for(i = 0; i < n; i++)
    {
        int num = rand() % 1000;  // Random numbers from 0 to 999
        fprintf(fp, "%d ", num);  // Write number into file
    }

    fclose(fp);   // Close the file

    printf("\ninput.txt file generated successfully with %d numbers.\n", n);

    return 0;
}
