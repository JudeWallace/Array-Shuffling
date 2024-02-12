#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/**
 * cmp_int - Compare function for integers if they are equal
 *
 * @a: An integer
 * @b: An integer
 *
 * Return: -1 if a < b, 0 if a == b, 1 for any other case
 */
int cmp_int(void *a, void *b)
{
    int x = *((int *)a);
    int y = *((int *)b);

    if (x < y)
    {
        return -1;
    }
    else if (x == y)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * cmp_int - Compare if two chars are the same
 *
 * @a: A char
 * @b: A char
 *
 * Return: 0,1,-1 depending on how a and b compare to each other
 */
int cmp_str(void *a, void *b)
{
    char *x = *((char **)a);
    char *y = *((char **)b);

    return strcmp(x, y);
}

/**
 * riffle_once - Performs a single riffle of the array
 *
 * @L: The array to be shuffled
 * @len: The length of the array
 * @size: The size needed for each element in the array
 * @work: An array used as workspace for the riffle
 *
 * Return: None
 */
void riffle_once(void *L, int len, int size, void *work)
{
    char *p = L, *q = (char *)work;
    int len1 = len / 2;
    int i, j, k;

    // Loop through all elements in the array and shuffle the cards
    for (i = 0, j = 0, k = 0; i < len; i++)
    {
        // Randomly select an array for the element to be taken from
        if (j < len1 && (k >= len1 || rand() % 2 == 0))
        {
            // Copy the selected element to the work array
            memcpy(q + i * size, p + j * size, size);
            j++;
        }
        else
        {
            // Copy the element into the work array
            memcpy(q + i * size, p + (len1 + k) * size, size);
            k++;
        }
    }

    // Copy the elements in the work array back to the original array
    memcpy(L, q, len * size);
}

/**
 * riffle - Riffles the array by a number specified when calling the function
 *
 * @L: The array to be shuffled
 * @len: The length of the array
 * @size: The size needed for each element in the array
 * @N: The number of times to riffle the array
 *
 * Return: None
 */
void riffle(void *L, int len, int size, int N)
{
    void *work = malloc(len * size);

    // Check memory has been allocated
    if (work == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Loop through and riffle L N times
    int i;
    for (i = 0; i < N; i++)
    {
        riffle_once(L, len, size, work);
    }

    free(work);
}

/**
 * check_shuffle - check if the shuffled array is the same as the original list
 * and all elements have been accounted for
 *
 * @L: The array to be shuffled
 * @len: The length of the array
 * @size: The size needed for each element in the array
 * @cmp: A function which compares to values each one given be its own pointer
 *
 * Return: 0 if the shuffle has lost elements, 1 if the shuffle matches
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *))
{
    int i, j, found;
    void *original = malloc(len * size);

    // Check for is memory has been allocated correctly
    if (original == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the contents of L into the original array
    memcpy(original, L, len * size);

    // Shuffle the array L x times
    riffle(L, len, size, 5);

    // Check that each element in L is in original array
    for (i = 0; i < len; i++)
    {
        found = 0;
        for (j = 0; j < len; j++)
        {
            if (cmp(original + j * size, L + i * size) == 0)
            {
                found = 1;
                break;
            }
        }
        // If all elements aren't there return 0
        if (!found)
        {
            free(original);
            return 0;
        }
    }
    // Check that each element in original array is in L
    for (i = 0; i < len; i++)
    {
        found = 0;
        for (j = 0; j < len; j++)
        {
            if (cmp(L + j * size, original + i * size) == 0)
            {
                found = 1;
                break;
            }
        }
        // If all elements aren't there return 0
        if (!found)
        {
            free(original);
            return 0;
        }
    }

    // Free the memory location of original
    free(original);

    return 1;
}

/**
 * quality - Check the quality of the shuffled array
 *
 * @numbers: The shuffled array
 * @len: The length of the array
 *
 * Return: A float value for how good the shuffle is on the scale 0-1 where 1
 * means the shuffle is poor and the closer to 0 the better shuffle
 */
float quality(int *numbers, int len)
{
    int count = 0;
    int i;
    // Loop through every element in the list
    for (i = 0; i < len - 1; i++)
    {
        // Compare if the number at i is less than the following element
        if (numbers[i] < numbers[i + 1])
        {
            count++;
        }
    }
    return (float)count / (len - 1);
}

/**
 * average_quality - Calculate the quality of a array after being shuffled
 * trials times
 *
 * @N: The amount of numbers to be in the array
 * @shuffles: The amount of shuffles to perform on the array
 * @trials: The amount of times to perform a X amount of shuffles on an array
 *
 * Return: A float value for the overall average after the array has been
 * shuffled trial times
 */
float average_quality(int N, int shuffles, int trials)
{
    int numbers[N], original[N], i, j;
    float sum_quality = 0.0;

    // Initialize an array with the intergers 0,1. N-1
    for (i = 0; i < N; i++)
    {
        numbers[i] = i;
        original[i] = i;
    }
    // Shuffle the array and evaluate the quality of the shuffle
    for (i = 0; i < trials; i++)
    {
        riffle(numbers, N, sizeof(int), shuffles);
        sum_quality += quality(numbers, N);
        // Reset the original array to not be shuffled
        memcpy(numbers, original, sizeof(original));
    }

    return sum_quality / trials;
}
