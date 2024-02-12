#include <stdio.h>
#include "riffle.h"

/**
 * main - Display to the terminal the average quality of an array when it
 * has been riffled trial times.
 */
int main()
{
    int shuffles = 15;
    int trials = 30;

    int N;
    for (N = 1; N <= shuffles; N++)
    {
        float avg_quality = average_quality(50, N, trials);
        printf("N=%d, avg_quality=%f\n", N, avg_quality);
    }

    return 0;
}