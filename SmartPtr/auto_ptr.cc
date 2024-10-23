#include <iostream>

template <typename T>
class AutoPtr
{
private:
    T *ptr;

public:
    explicit AutoPtr(T *p = nullptr) : ptr(p) {}

    AutoPtr(AutoPtr &other) : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    AutoPtr &operator=(AutoPtr &other)
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~AutoPtr()
    {
        delete ptr;
    }

    T &operator*() { return *ptr; }
    T *operator->() { return ptr; }
};

int main()
{
    AutoPtr<int> ptr1(new int(10));
    std::cout << *ptr1 << std::endl;

    AutoPtr<int> ptr2(ptr1);
    // std::cout<<*ptr1<<std::endl;
    std::cout << *ptr2 << std::endl;

    return 0;
}