#include <iostream>
#include <mutex>
#include <thread>

class Singleton_cpp11
{
private:
    Singleton_cpp11()
    {
        std::cout << "Singleton created" << std::endl;
    }

    Singleton_cpp11(const Singleton_cpp11 &) = delete;
    Singleton_cpp11 &operator=(const Singleton_cpp11 &) = delete;

public:
    static Singleton_cpp11 &getInstance()
    {
        static Singleton_cpp11 instance;
        return instance;
    }

    void doSomething()
    {
        std::cout << "Singleton doing something." << std::endl;
    }
};

class Singleton
{
private:
    Singleton()
    {
        std::cout << "Singleton created." << std::endl;
    }

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    static std::mutex _mtx;

public:
    static Singleton *getInstance()
    {
        static Singleton *instance = nullptr;
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(_mtx);
            if (instance == nullptr)
                instance = new Singleton();
        }
        return instance;
    }

    void doSomething()
    {
        std::cout << "Singleton doing something." << std::endl;
    }
};
std::mutex Singleton::_mtx;

int main()
{
    Singleton_cpp11 &obj1 = Singleton_cpp11::getInstance();
    obj1.doSomething();

    Singleton *obj2 = Singleton::getInstance();
    obj2->doSomething();

    Singleton *obj3 = Singleton::getInstance();
    obj3->doSomething();

    return 0;
}