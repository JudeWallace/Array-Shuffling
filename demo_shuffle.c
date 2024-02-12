#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "riffle.h"

/**
 * main - Test the riffle function shuffles an array of any type and assert
 * all the values within the arrays are still in the shuffled array
 */
int main()
{
    int i;
    int arr[20];
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
    srand(time(NULL));

    // Initialize the integer array with values 1 to 20
    for (i = 0; i < 20; i++)
    {
        arr[i] = i + 1;
    }

    // Check if the shuffled integer array is correct
    if (check_shuffle(arr, 20, sizeof(int), cmp_int) == 1)
    {
        printf("Shuffled integer array is correct!\n");
        // Print the shuffled array
        for (i = 0; i < 20; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Shuffled integer array is incorrect!\n");
    }

    // Check if the shuffled Greek letter name array is correct
    if (check_shuffle(greek, 12, sizeof(char *), cmp_str) == 1)
    {
        printf("Shuffled Greek letter name array is correct!\n");
        for (i = 0; i < 12; i++)
        {
            printf("%s ", greek[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Shuffled Greek letter name array is incorrect!\n");
    }

    return 0;
}