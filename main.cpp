// PROJECT 3
// by Al Anwar, Avery Birle, and John Aitken

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void merge(vector<int>& vec, int left, int mid, int right) {
    vector<int> mix;
    int i = left;
    int j = mid + 1;

    // mixing the two sides together.
    while (i <= mid && j <= right) {
        if (vec[i] <= vec[j]) {
            mix.push_back(vec[i]);
            i++;
        } else {
            mix.push_back(vec[j]);
            j++;
        }
    }

    // once one side is complete, add the rest of the other side to mix.
    while (i <= mid) {
        mix.push_back(vec[i]);
        i++;
    }
    while (j <= right) {
        mix.push_back(vec[j]);
        j++;
    }

    for (int k = left; k <= right; k++) {
        vec[k] = mix[k - left];
    }
}

void mergeSort(vector<int>& vec, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp)
{
    int output[n];
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n)
{

    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main() {
    vector<int> vec;

    for (int i = 0; i < 100000; i++){
        vec.push_back(rand());
    }

    for (int num : vec) {
        cout << num << " ";
    }

    mergeSort(vec, 0, vec.size() - 1);
    cout << "After merge sort: ";

    for (int num : vec) {
        cout << num << " ";
    }
}
