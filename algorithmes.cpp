#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define MY_RANDOM_MAX 32768
#define Num_5 5
#define Num_10 10
#define Num_100 100
#define Num_1k 1000
#define Num_10k 10000
#define Num_100k 100000
#define Num_1M 1000000
#define Num_10M 10000000
#define Num_100M 100000000

int bubble (int myarray[], int length)
{
    int i, j, n;
    long time;
    clock_t start_time, finish_time;
    start_time = clock();
    for(i = 0; i < length - 1; i++)
    {
        for(j = 0; j < length - i - 1; j++)
        {
            if(myarray[j] > myarray[j+1])
            {
                n = myarray[j];
                myarray[j] = myarray[j+1];
                myarray[j+1] = n;
            }
        }
    }
    finish_time = clock();
    time = finish_time - start_time;
    return(time);
}

int comp(const void *i, const void *j)
{
  return *(int *)i - *(int *)j;
}

int quick (int myarray[], int length)
{
    int i;
    long time;
    clock_t start_time, finish_time;
    start_time = clock();
    qsort(myarray, length, sizeof(int), comp);
    finish_time = clock();
    time = finish_time - start_time;
    return(time);
}

void merge(int *a, long start, long split, long stop)
{
    long pos1 = start;
    long pos2 = split + 1;
    long pos3 = 0;
    int *temp;
    temp = (int *)malloc(sizeof(int) * (stop - start + 1));
    while (pos1 <= split && pos2 <= stop)
    {
        if (a[pos1] < a[pos2])
        {
            temp[pos3++] = a[pos1++];
        }
        else
        {
            temp[pos3++] = a[pos2++];
        }
    }
    while (pos2 <= stop)
    {
        temp[pos3++] = a[pos2++];
    }
    while (pos1 <= split)
    {
        temp[pos3++] = a[pos1++];
    }
    for (pos3 = 0; pos3 < stop-start+1; pos3++)
    {
        a[start + pos3] = temp[pos3];
    }
    free(temp);
}

void mergeSort(int *a, long start, long stop)
{
    long split;
    if (start < stop)
    {
        split = (start + stop) / 2;
        mergeSort(a, start, split);
        mergeSort(a, split + 1,stop);
        merge(a, start, split, stop);
    }
}

int merging (int myarray[], int length)
{
    int i;
    long time;
    clock_t start_time, finish_time;
    start_time = clock();
    mergeSort(myarray, 0, length - 1);
    finish_time = clock();
    time = finish_time - start_time;
    return(time);
}

int counting(int myarray[], int counting[], int length)
{
    int i, j, n;
    for (i = 0; i < RANDOM; i++)
    {
        counting[i] = 0;
    }
    long time;
    clock_t start_time, finish_time;
    start_time = clock();
    for(i = 0; i < length; i++)
    {
        counting[myarray[i]]++;
    }
    n = 0;
    for(i = 0; i < length; i++)
    {
        for(j = 0; j < counting[i]; j++)
        {
            myarray[n] = i;
            n++;
        }
    }
    finish_time = clock();
    time = finish_time - start_time;
    return(time);
}

int main()
{
    float bubble_time_5, bubble_time_10, bubble_time_100, bubble_time_1k, bubble_time_10k, bubble_time_100k, bubble_time_1M, bubble_time_10M, bubble_time_100M;
    float merging_time_5, merging_time_10, merging_time_100, merging_time_1k, merging_time_10k, merging_time_100k, merging_time_1M, merging_time_10M, merging_time_100M;
    float quick_time_5, quick_time_10, quick_time_100, quick_time_1k, quick_time_10k, quick_time_100k, quick_time_1M, quick_time_10M, quick_time_100M;
    float counting_time_5, counting_time_10, counting_time_100, counting_time_1k, counting_time_10k, counting_time_100k, counting_time_1M, counting_time_10M, counting_time_100M;
    int i;
    int *array_main = (int *)malloc(Num_100M * sizeof(int));
    for(i = 0; i < Num_100M; i++)
    {
        array_main[i] = 1 + rand() % MY_RANDOM_MAX;
    };
    int *array_counting = (int *)malloc(MY_RANDOM_MAX * sizeof(int));
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    printf("n \t bubble \t merging \t quick \t\t counting \n");

    //5
    int *array_5 = (int *)malloc(Num_5 * sizeof(int));
    for(i = 0; i < Num_5; i++)
    {
        array_5[i] = array_main[i];
    }
    bubble_time_5 = bubble (array_5, Num_5);
    for(i = 0; i < Num_5; i++)
    {
        array_5[i] = array_main[i];
    }
    quick_time_5 = quick (array_5, Num_5);
    for(i = 0; i < Num_5; i++)
    {
        array_5[i] = array_main[i];
    }
    merging_time_5 = merging (array_5, Num_5);
    for(i = 0; i < Num_5; i++)
    {
        array_5[i] = array_main[i];
    }
    counting_time_5 = counting (array_5, array_counting, Num_5);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_5);
    printf("5 \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_5/CLOCKS_PER_SEC, merging_time_5/CLOCKS_PER_SEC, quick_time_5/CLOCKS_PER_SEC, counting_time_5/CLOCKS_PER_SEC);

    //10
    int *array_10 = (int *)malloc(Num_10 * sizeof(int));
    for(i = 0; i < Num_10; i++)
    {
        array_10[i] = array_main[i];
    }
    bubble_time_10 = bubble (array_10, Num_10);
    for(i = 0; i < Num_10; i++)
    {
        array_10[i] = array_main[i];
    }
    quick_time_10 = quick (array_10, Num_10);
    for(i = 0; i < Num_10; i++)
    {
        array_10[i] = array_main[i];
    }
    merging_time_10 = merging (array_10, Num_10);
    for(i = 0; i < Num_10; i++)
    {
        array_10[i] = array_main[i];
    }
    counting_time_10 = counting (array_10, array_counting, Num_10);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_10);
    printf("10 \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_10/CLOCKS_PER_SEC, merging_time_10/CLOCKS_PER_SEC, quick_time_10/CLOCKS_PER_SEC, counting_time_10/CLOCKS_PER_SEC);

    //100
    int *array_100 = (int *)malloc(Num_100 * sizeof(int));
    for(i = 0; i < Num_100; i++)
    {
        array_100[i] = array_main[i];
    }
    bubble_time_100 = bubble (array_100, Num_100);
    for(i = 0; i < Num_100; i++)
    {
        array_100[i] = array_main[i];
    }
    quick_time_100 = quick (array_100, Num_100);
    for(i = 0; i < Num_100; i++)
    {
        array_100[i] = array_main[i];
    }
    merging_time_100 = merging (array_100, Num_100);
    for(i = 0; i < Num_100; i++)
    {
        array_100[i] = array_main[i];
    }
    counting_time_100 = counting (array_100, array_counting, Num_100);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_100);
    printf("100 \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_100/CLOCKS_PER_SEC, merging_time_100/CLOCKS_PER_SEC, quick_time_100/CLOCKS_PER_SEC, counting_time_100/CLOCKS_PER_SEC);

    //1k
    int *array_1k = (int *)malloc(Num_1k * sizeof(int));
    for(i = 0; i < Num_1k; i++)
    {
        array_1k[i] = array_main[i];
    }
    bubble_time_1k = bubble (array_1k, Num_1k);
    for(i = 0; i < Num_1k; i++)
    {
        array_1k[i] = array_main[i];
    }
    quick_time_1k = quick (array_1k, Num_1k);
    for(i = 0; i < Num_1k; i++)
    {
        array_1k[i] = array_main[i];
    }
    merging_time_1k = merging (array_1k, Num_1k);
    for(i = 0; i < Num_1k; i++)
    {
        array_1k[i] = array_main[i];
    }
    counting_time_1k = counting (array_1k, array_counting, Num_1k);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_1k);
    printf("1k \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_1k/CLOCKS_PER_SEC, merging_time_1k/CLOCKS_PER_SEC, quick_time_1k/CLOCKS_PER_SEC, counting_time_1k/CLOCKS_PER_SEC);

    //10k
    int *array_10k = (int *)malloc(Num_10k * sizeof(int));
    for(i = 0; i < Num_10k; i++)
    {
        array_10k[i] = array_main[i];
    }
    bubble_time_10k = bubble (array_10k, Num_10k);
    for(i = 0; i < Num_10k; i++)
    {
        array_10k[i] = array_main[i];
    }
    quick_time_10k = quick (array_10k, Num_10k);
    for(i = 0; i < Num_10k; i++)
    {
        array_10k[i] = array_main[i];
    }
    merging_time_10k = merging (array_10k, Num_10k);
    for(i = 0; i < Num_10k; i++)
    {
        array_10k[i] = array_main[i];
    }
    counting_time_10k = counting (array_10k, array_counting, Num_10k);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_10k);
    printf("10k \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_10k/CLOCKS_PER_SEC, merging_time_10k/CLOCKS_PER_SEC, quick_time_10k/CLOCKS_PER_SEC, counting_time_10k/CLOCKS_PER_SEC);

    //100k
    int *array_100k = (int *)malloc(Num_100k * sizeof(int));
    for(i = 0; i < Num_100k; i++)
    {
        array_100k[i] = array_main[i];
    }
    bubble_time_100k = bubble (array_100k, Num_100k);
    for(i = 0; i < Num_100k; i++)
    {
        array_100k[i] = array_main[i];
    }
    quick_time_100k = quick (array_100k, Num_100k);
    for(i = 0; i < Num_100k; i++)
    {
        array_100k[i] = array_main[i];
    }
    merging_time_100k = merging (array_100k, Num_100k);
    for(i = 0; i < Num_100k; i++)
    {
        array_100k[i] = array_main[i];
    }
    counting_time_100k = counting (array_100k, array_counting, Num_100k);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_100k);
    printf("100k \t %2.5f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_100k/CLOCKS_PER_SEC, merging_time_100k/CLOCKS_PER_SEC, quick_time_100k/CLOCKS_PER_SEC, counting_time_100k/CLOCKS_PER_SEC);

    //1M
    int *array_1M = (int *)malloc(Num_1M * sizeof(int));
    for(i = 0; i < Num_1M; i++)
    {
        array_1M[i] = array_main[i];
    }
    bubble_time_1M = bubble (array_1M, Num_1M);
    for(i = 0; i < Num_1M; i++)
    {
        array_1M[i] = array_main[i];
    }
    quick_time_1M = quick (array_1M, Num_1M);
    for(i = 0; i < Num_1M; i++)
    {
        array_1M[i] = array_main[i];
    }
    merging_time_1M = merging (array_1M, Num_1M);
    for(i = 0; i < Num_1M; i++)
    {
        array_1M[i] = array_main[i];
    }
    counting_time_1M = counting (array_1M, array_counting, Num_1M);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_1M);
    printf("1M \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_1M/CLOCKS_PER_SEC, merging_time_1M/CLOCKS_PER_SEC, quick_time_1M/CLOCKS_PER_SEC, counting_time_1M/CLOCKS_PER_SEC);

    //10M
    int *array_10M = (int *)malloc(Num_10M * sizeof(int));
    for(i = 0; i < Num_10M; i++)
    {
        array_10M[i] = array_main[i];
    }
    bubble_time_10M = bubble (array_10M, Num_10M);
    for(i = 0; i < Num_10M; i++)
    {
        array_10M[i] = array_main[i];
    }
    quick_time_10M = quick (array_10M, Num_10M);
    for(i = 0; i < Num_10M; i++)
    {
        array_10M[i] = array_main[i];
    }
    merging_time_10M = merging (array_10M, Num_10M);
    for(i = 0; i < Num_10M; i++)
    {
        array_10M[i] = array_main[i];
    }
    counting_time_10M = counting (array_10M, array_counting, Num_10M);
    for(i = 0; i < MY_RANDOM_MAX; i++)
    {
        array_counting[i] = 0;
    }
    free(array_10M);
    printf("10M \t %2.6f \t %2.6f \t %2.6f \t %2.6f \n", bubble_time_10M/CLOCKS_PER_SEC, merging_time_10M/CLOCKS_PER_SEC, quick_time_10M/CLOCKS_PER_SEC, counting_time_10M/CLOCKS_PER_SEC);

    //100M
    int *array_100M = (int *)malloc(Num_100M * sizeof(int));
    for(i = 0; i < Num_100M; i++)
    {
        array_100M[i] = array_main[i];
    }
    bubble_time_100M = bubble (array_100M, Num_100M);
    for(i = 0; i < Num_100M; i++)
    {
        array_100M[i] = array_main[i];
    }
    quick_time_100M = quick (array_100M, Num_100M);
    for(i = 0; i < Num_100M; i++)
    {
        array_100M[i] = array_main[i];
    }
    merging_time_100M = merging (array_100M, Num_100M);for(i = 0; i < Num_100M; i++)
    {
        array_100M[i] = array_main[i];
    }
    counting_time_100M = counting (array_100M, array_counting, Num_100M);
    free(array_100M);
    printf("100M \t %2.6f \t %2.5f \t %2.5f \t %2.6f \n", bubble_time_100M/CLOCKS_PER_SEC, merging_time_100M/CLOCKS_PER_SEC, quick_time_100M/CLOCKS_PER_SEC, counting_time_100M/CLOCKS_PER_SEC);

    free(array_main);
    free(array_counting);
    return 0;
}
