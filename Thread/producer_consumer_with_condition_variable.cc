#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <condition_variable>

#define BUFFER_SIZE 10
#define PRODUCER_SIZE 3
#define CONSUMER_SIZE 1

std::queue<int> buffer;
std::mutex _mtx;
std::condition_variable cv_producer;
std::condition_variable cv_consumer;

void producer(int id)
{
    while (true)
    {
        int data = rand() % 20 + 1;
        sleep(1);
        std::unique_lock<std::mutex> lock(_mtx);
        cv_producer.wait(lock, []
                         { return buffer.size() < BUFFER_SIZE; });
        buffer.push(data);
        std::cout << "producer" << id << " push->" << data << std::endl;
        cv_consumer.notify_all();
    }
}

void consumer(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(_mtx);
        cv_consumer.wait(lock, []
                         { return !buffer.empty(); });
        int data = buffer.front();
        buffer.pop();
        std::cout << "consumer" << id << " pop: " << data << std::endl;
        cv_producer.notify_all();
        sleep(1);
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<std::thread> pro_arr, con_arr;
    for (int i = 0; i < PRODUCER_SIZE; i++)
        pro_arr.push_back(std::thread(producer, i));
    for (int i = 0; i < CONSUMER_SIZE; i++)
        con_arr.push_back(std::thread(consumer, i));

    for (auto &e : pro_arr)
        e.join();
    for (auto &e : con_arr)
        e.join();

    return 0;
}