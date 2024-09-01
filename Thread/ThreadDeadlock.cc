#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

std::mutex _mtx1;
std::mutex _mtx2;

void Thead1()
{
    std::lock_guard<std::mutex> lock1(_mtx1);
    sleep(2);
    std::lock_guard<std::mutex> lock2(_mtx2);
    std::cout<<"Thread 1 executed!"<<std::endl;
}

void Thead2()
{
    std::lock_guard<std::mutex> lock2(_mtx2);
    sleep(3);
    std::lock_guard<std::mutex> lock1(_mtx1);
    std::cout<<"Thread 2 executed!"<<std::endl;
}

int main()
{
    std::thread t1(Thead1);
    std::thread t2(Thead2);

    t1.join();
    t2.join();

    return 0;
}
