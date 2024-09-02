#include <iostream>
#include <memory>

class HeapOnly
{
private:
    HeapOnly()
    {
        std::cout << "HeapOnly constructor called" << std::endl;
    }

    HeapOnly(const HeapOnly &) = delete;
    HeapOnly &operator=(const HeapOnly &) = delete;

public:
    static std::unique_ptr<HeapOnly> create()
    {
        return std::unique_ptr<HeapOnly>(new HeapOnly());
    }

    ~HeapOnly()
    {
        std::cout << "HeapOnly destructor called" << std::endl;
    }
};

int main()
{
    // 使用智能指针来管理堆上的对象
    auto obj = HeapOnly::create();

    // 当智能指针超出作用域时，HeapOnly 对象会自动销毁

    return 0;
}