#include <iostream>
#include <omp.h>

// Function to merge two sorted arrays
void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0, j = 0, k = 0;

    // Merge the two arrays into arr[]
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }

    // Copy the remaining elements of left[], if any
    while (i < leftSize)
    {
        arr[k++] = left[i++];
    }

    // Copy the remaining elements of right[], if any
    while (j < rightSize)
    {
        arr[k++] = right[j++];
    }
}

// Function to perform merge sort
void mergeSort(int arr[], int size)
{
    // Base case: if the array size is 1 or less, it is already sorted
    if (size <= 1)
    {
        return;
    }

    int mid = size / 2;

    // Create left and right subarrays
    int *left = new int[mid];
    int *right = new int[size - mid];

    // Copy elements to the left subarray
    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }

    // Copy elements to the right subarray
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    // Sort the left subarray recursively
    mergeSort(left, mid);

    // Sort the right subarray recursively
    mergeSort(right, size - mid);

    // Merge the sorted subarrays
    merge(arr, left, mid, right, size - mid);

    // Free memory
    delete[] left;
    delete[] right;
}

int main()
{
    int size;
    std::cout << "Enter the number of elements: ";
    std::cin >> size;

    int *arr = new int[size];
    std::cout << "Enter the elements: ";
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }

// Perform merge sort in parallel using OpenMP
#pragma omp parallel
    {
#pragma omp single nowait
        mergeSort(arr, size);
    }

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Free memory
    delete[] arr;

    return 0;
}
