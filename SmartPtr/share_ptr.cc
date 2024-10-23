#include <iostream>

template <typename T>
class SharePtr
{
private:
    T *ptr;
    unsigned int *ref_count;

public:
    explicit SharePtr(T *p = nullptr) : ptr(p), ref_count(new unsigned int(1)) {}

    SharePtr(const SharePtr &other) : ptr(other.ptr), ref_count(other.ref_count)
    {
        (*ref_count)++;
    }

    SharePtr &operator=(const SharePtr &other)
    {
        if (this != &other)
        {
            if (--(*ref_count) == 0)
            {
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
    }

    ~SharePtr()
    {
        if (--(*ref_count) == 0)
        {
            delete ptr;
            delete ref_count;
        }
    }

    int RefCount()
    {
        return *ref_count;
    }

    T &operator*() { return *ptr; }
    T *operator->() { return ptr; }
};

template <typename T>
class WeakPtr
{
private:
    T *ptr;
    unsigned int *ref_count;

public:
    WeakPtr(const SharePtr<T> &sptr) : ptr(sptr.ptr), ref_count(sptr.ref_count) {}

    // 检查对象是否还存在
    bool expired() const
    {
        return (*ref_count == 0);
    }

    // 尝试获取 shared_ptr
    SharedPtr<T> lock() const
    {
        if (!expired())
        {
            return SharedPtr<T>(*this); // 返回一个新的 SharedPtr
        }
        else
        {
            return SharedPtr<T>(nullptr); // 返回空的 SharedPtr
        }
    }
};

int main()
{
    SharePtr<int> ptr1(new int(10));
    std::cout << *ptr1 << " " << ptr1.RefCount() << std::endl;

    SharePtr<int> ptr2(ptr1);
    std::cout << *ptr2 << " " << ptr2.RefCount() << std::endl;
    std::cout << *ptr1 << " " << ptr1.RefCount() << std::endl;

    return 0;
}