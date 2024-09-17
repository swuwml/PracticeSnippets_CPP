#include <iostream>
#include <vector>
#include <cstdlib>

#define COUNT 10
#define RANGE 100

std::vector<int> tmp(COUNT);

void merge(std::vector<int> &arr, int l, int mid, int r)
{
    int index = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (arr[i] <= arr[j])
            tmp[index++] = arr[i++];
        else
            tmp[index++] = arr[j++];
    }
    while (i <= mid)
        tmp[index++] = arr[i++];
    while (j <= r)
        tmp[index++] = arr[j++];
    std::copy(tmp.begin(), tmp.begin() + index, arr.begin() + l);
}

void MergeSort(std::vector<int> &arr, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    MergeSort(arr, l, mid), MergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

int main()
{
    std::srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<int> arr;
    for (int i = 0; i < COUNT; i++)
    {
        int randomNumber = rand() % RANGE;
        arr.push_back(randomNumber);
    }
    MergeSort(arr, 0, arr.size() - 1);
    for (auto e : arr)
        std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}