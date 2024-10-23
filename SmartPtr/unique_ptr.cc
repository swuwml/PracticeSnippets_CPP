#include <iostream>

template <typename T>
class UniquePtr
{
private:
    T *ptr;

public:
    explicit UniquePtr(T *p = nullptr) : ptr(p) {}

    UniquePtr(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr &operator=(UniquePtr &&other)
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~UniquePtr() { delete ptr; }

    T &operator*() { return *ptr; }
    T *operator->() { return ptr; }
};

int main()
{
    UniquePtr<int> ptr1(new int(10));
    std::cout << *ptr1 << std::endl;

    // UniquePtr<int> ptr2(ptr1);

    return 0;
}