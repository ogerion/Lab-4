#pragma once
#include "Ptr.h"
template<class T>
class Ptr;
template<class T>
class UnqPtr : public Ptr<T> {
public:
    UnqPtr();

    UnqPtr(T* ptr);

    template<class U>
    UnqPtr(UnqPtr<U>&);

    template<class U>
    UnqPtr(UnqPtr<U>&&);

    template<class U>
    UnqPtr<T>& operator=(UnqPtr<U>&);

    template<class U>
    UnqPtr<T>& operator=(UnqPtr<U>&&);

    template<class U>
    UnqPtr(const UnqPtr<U>&) = delete;

    template<class U>
    UnqPtr<T>& operator=(const UnqPtr<T>&) = delete;

    T* get() const override;

    T* operator->() const override;

    ~UnqPtr();

    T* release();
};

template<class T>
UnqPtr<T>::UnqPtr()
{
    this->ptr = nullptr;
}


template<class T>
UnqPtr<T>::UnqPtr(T* ptr)
{
    this->ptr = ptr;
}

template<class T>
template<class U>
UnqPtr<T>::UnqPtr(UnqPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.release());
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
UnqPtr<T>::UnqPtr(UnqPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        other.ptr = nullptr;
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
UnqPtr<T>& UnqPtr<T>::operator=(UnqPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.release());
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
UnqPtr<T>& UnqPtr<T>::operator=(UnqPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        other.ptr = nullptr;
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template <class T>
T* UnqPtr<T>::get() const
{
    if (this->ptr != nullptr)
    {
        return this->ptr;
    }
    else
    {
        throw "Pointer is expired!";
    }
}

template <class T>
T* UnqPtr<T>::operator->() const
{
    if (this->ptr != nullptr)
    {
        return this->ptr;
    }
    else
    {
        throw "Pointer is expired!";
    }
}

template<class T>
UnqPtr<T>::~UnqPtr()
{
    delete this->ptr;
}

template<class T>
T* UnqPtr<T>::release()
{
    T* res = this->ptr;
    this->ptr = nullptr;
    return res;
}