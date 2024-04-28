#include <iostream>
#include <omp.h>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubbleSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(int *arr, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + j + 1];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
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

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void parallelMergeSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        #pragma omp parallel sections
        #pragma omp section
        parallelMergeSort(arr, left, middle);
        #pragma omp section
        parallelMergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main()
{
    const int n = 1000; // Size of the array
    int arr[n];

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;

    // Sequential bubble sort
    auto bsstart = high_resolution_clock::now();
    bubbleSort(arr, n);
    auto bsend = high_resolution_clock::now();

    auto bsduration = duration_cast<microseconds>(bsend - bsstart);
    cout << "Sequential Bubble Sort Time: " << bsduration.count() << " seconds" << endl;

    // Parallel bubble sort
    auto bpstart = high_resolution_clock::now();
    parallelBubbleSort(arr, n);
    auto bpend = high_resolution_clock::now();

    auto bpduration = duration_cast<microseconds>(bpend - bpstart);
    cout << "Parallel Bubble Sort Time: " << bpduration.count() << " seconds" << endl;
    cout << endl;

    // Sequential merge sort
    auto msstart = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto msend = high_resolution_clock::now();

    auto msduration = duration_cast<microseconds>(msend - msstart);
    cout << "Sequential Merge Sort Time: " << msduration.count() << " seconds" << endl;

    // Parallel merge sort
    auto mpstart = high_resolution_clock::now();
    parallelMergeSort(arr, 0, n - 1);
    auto mpend = high_resolution_clock::now();

    auto mpduration = duration_cast<microseconds>(mpend - mpstart);
    cout << "Parallel Merge Sort Time: " << mpduration.count() << " seconds" << endl;

    return 0;
}
