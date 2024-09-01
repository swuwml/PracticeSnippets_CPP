#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define COUNT 10
#define RANGE 100

void QuickSort(std::vector<int>& arr,int l,int r)
{
    if(l>=r) return;
    int i=l-1,j=r+1,key=l;
    while(i<j)
    {
        do ++i;while(arr[i]<arr[key]);
        do --j;while(arr[j]>arr[key]);
        if(i<j) std::swap(arr[i],arr[j]);
    }
    QuickSort(arr,l,j);
    QuickSort(arr,j+1,r);
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> arr;
    for(int i=0;i<COUNT;i++) {
        int randomNumber = rand()%RANGE+1;
        arr.push_back(randomNumber);
    }
    QuickSort(arr,0,arr.size()-1);
    for(auto e : arr) std::cout<<e<<" ";
    std::cout<<std::endl;
    return 0;
}