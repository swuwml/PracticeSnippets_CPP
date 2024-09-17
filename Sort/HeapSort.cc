#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define COUNT 10
#define RANGE 100

void AdjustDown(std::vector<int> &arr, int parent, int sz)
{
    int child = parent * 2 + 1;
    while (child < sz)
    {
        if (child + 1 < sz && arr[child + 1] > arr[child])
            child++;
        if (arr[parent] < arr[child])
        {
            std::swap(arr[parent], arr[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
            break;
    }
}

void HeapSort(std::vector<int> &arr, int sz)
{
    for (int i = (sz - 1 - 1) / 2; i >= 0; i--)
        AdjustDown(arr, i, sz);
    for (int i = 1; i < sz; i++)
    {
        std::swap(arr[sz - i], arr[0]);
        AdjustDown(arr, 0, sz - i);
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> arr;
    for (int i = 0; i < COUNT; i++)
    {
        int randomNumber = rand() % RANGE;
        arr.push_back(randomNumber);
    }
    HeapSort(arr, arr.size());
    for (auto e : arr)
        std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}
