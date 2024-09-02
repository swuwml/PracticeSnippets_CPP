#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#define COUNT 10

int j = 1;
std::mutex _mtx;
std::condition_variable _cv;

void print1()
{
    for (int i = 0; i < COUNT; i++)
    {
        std::unique_lock<std::mutex> _lock(_mtx);
        _cv.wait(_lock, [&]
                 { return j % 3 == 1; });
        std::cout << "thread1 -> " << j << std::endl;
        ++j;
        _cv.notify_all();
    }
}

void print2()
{
    for (int i = 0; i < COUNT; i++)
    {
        std::unique_lock<std::mutex> _lock(_mtx);
        _cv.wait(_lock, [&]
                 { return j % 3 == 2; });
        std::cout << "thread2 -> " << j << std::endl;
        ++j;
        _cv.notify_all();
    }
}

void print3()
{
    for (int i = 0; i < COUNT; i++)
    {
        std::unique_lock<std::mutex> _lock(_mtx);
        _cv.wait(_lock, [&]
                 { return j % 3 == 0; });
        std::cout << "thread3 -> " << j << std::endl;
        ++j;
        _cv.notify_all();
    }
}

int main()
{
    std::thread t1(print1);
    std::thread t2(print2);
    std::thread t3(print3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}