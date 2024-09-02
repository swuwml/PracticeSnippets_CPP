#include <iostream>

class StackOnly
{
public:
    // 私有构造函数，禁止直接创建对象
    StackOnly()
    {
        std::cout << "StackOnly constructor called." << std::endl;
    }

    // 私有析构函数，禁止直接删除对象
    ~StackOnly()
    {
        std::cout << "StackOnly destructor called." << std::endl;
    }

public:
    // 禁用拷贝构造函数和拷贝赋值运算符
    StackOnly(const StackOnly &) = delete;
    StackOnly &operator=(const StackOnly &) = delete;
    void *operator new(size_t) = delete;
    void operator delete(void *) = delete;
};

int main()
{
    // 在栈上创建对象
    StackOnly obj;

    // 编译错误，禁止在堆上创建对象
    // StackOnly* pObj = new StackOnly(); // 错误
    // StackOnly* pObj = new StackOnly(); // 错误

    return 0;
}