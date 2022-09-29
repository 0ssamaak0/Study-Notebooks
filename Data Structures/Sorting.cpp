#include <bits/stdc++.h>
using namespace std;

// Array that multiplies array's elements by 2
int *double_arr(int arr[], int size)
{
    int *result = new int[size];
    for (int i = 0; i < size; i++)
    {
        result[i] = 2 * arr[i];
    }
    return result;
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return;
}

void bubble_sort(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            return;
        }
    }
}
void merge(int arr[], int left, int right)
{
    int temp[right - left + 1];
    int mid = (right + left) / 2;

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
    for (int i = left; i <= right; i++)
    {
        arr[i] = temp[i - left];
    }
}

void mergesort(int arr[], int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = (right + left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, right);
}

void quicksort(int arr[], int left, int right)
{
    if (right <= left)
    {
        return;
    }

    int pivot = arr[left];
    int i = left + 1;
    for (int j = left + 1; j <= right; j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[left], &arr[i - 1]);

    quicksort(arr, left, i - 2);
    quicksort(arr, i, right);
}
void selectionsort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        swap(&arr[i], &arr[min_index]);
    }
}

int binarysearch(int arr[], int l, int r, int num)
{
    if (l == r)
    {
        if (num == arr[l])
        {
            return l;
        }
        return -1;
    }
    int middle = (l + r) / 2;
    if (num == arr[middle])
    {
        return middle;
    }
    else if (num < arr[middle])
    {
        return binarysearch(arr, l, middle - 1, num);
    }
    else
    {
        return binarysearch(arr, middle + 1, r, num);
    }
    return -1;
}

int main(void)
{
    int arr1[] = {1, 4, 2, -1, 7, 8, 16, 22, 15, 0};
    bubble_sort(arr1, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr1[i] << " ";
    }
    cout << "\n";

    int arr2[] = {1, 4, 2, -1, 7, 8, 16, 22, 15, 0};
    mergesort(arr2, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        cout << arr2[i] << " ";
    }
    cout << "\n";

    int arr3[] = {1, 4, 2, -1, 7, 8, 16, 22, 15, 0};
    quicksort(arr3, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        cout << arr3[i] << " ";
    }
    cout << "\n";

    int arr4[] = {1, 4, 2, -1, 7, 8, 16, 22, 15, 0};
    selectionsort(arr4, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr4[i] << " ";
    }

    cout << "\n";
    int arr5[] = {1, 4, 2, -1, 7, 8, 16, 22, 15, 0};
    insertion_sort(arr5, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr5[i] << " ";
    }
    cout << "\n";
}