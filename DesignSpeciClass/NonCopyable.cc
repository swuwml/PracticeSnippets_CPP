#include <iostream>

class NonCopyable
{
private:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable& operator=(const NonCopyable &) = delete;

public:
    NonCopyable() { std::cout << "NonCopyable()" << std::endl; }
    ~NonCopyable() { std::cout << "~NonCopyable()" << std::endl; }
};

int main()
{
    NonCopyable obj;
    //NonCopyable obj1(obj);
    //NonCopyable obj2 = obj;
    return 0;
}