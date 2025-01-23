#pragma once
#include <functional>
#include <cstddef>
#include "Ptr.h"

template<class T>
class ShrdPtr;

template <class T>
class WeakPtr : public Ptr<T> {
private:
    size_t* counterS;
    size_t* counterW;
    void release();

public:
    template<class U>
    WeakPtr(WeakPtr<U>&&);

    template<class U>
    WeakPtr(const WeakPtr<U>&);
    
    template<class U>
    WeakPtr(ShrdPtr<U>&&);

    template<class U>
    WeakPtr(const ShrdPtr<U>&);

    template<class U>
    WeakPtr<T>& operator=(WeakPtr<U>&&);

    template<class U>
    WeakPtr<T>& operator=(const WeakPtr<U>&);

    template<class U>
    WeakPtr<T>& operator=(ShrdPtr<U>&&);

    template<class U>
    WeakPtr<T>& operator=(const ShrdPtr<U>&);

    size_t countW();

    size_t countS();

    T* get() const override;

    T* operator->() const override;

    size_t* getWCounter() const
    {
        return this->counterW;
    }

    size_t* getSCounter() const
    {
        return this->counterS;
    }

    ~WeakPtr();

    void reset();
};

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(WeakPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const WeakPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(ShrdPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const ShrdPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        this->counterW = std::move(other.counterW);
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = std::move(other.counterS);
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(ShrdPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const ShrdPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        if (this->counterW != nullptr)
        {
            *(this->counterW) += 1;
        }
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template <class T>
T* WeakPtr<T>::get() const
{
    if (*(this->counterS) != 0)
    {
        return ptr;
    }
    else
    {
        throw "All shared pointer are expired!";
    }
}

template <class T>
T* WeakPtr<T>::operator->() const
{
    if (*(this->counterS) != 0)
    {
        return ptr;
    }
    else
    {
        throw "All shared pointer are expired!";
    }
}

template<class T>
WeakPtr<T>::~WeakPtr()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}

template <class T>
size_t WeakPtr<T>::countW()
{
    if (this->counterW != nullptr)
    {
        return *(this->counterW);
    }
    return size_t(0);
}

template <class T>
size_t WeakPtr<T>::countS()
{
    if (this->counterS != nullptr)
    {
        return *(this->counterS);
    }
    return size_t(0);
}

template <class T>
void WeakPtr<T>::release()
{
    if (this->counterS != nullptr)
    {
        *(this->counterS) -= 1;
        if (*(this->counterS) == 0 && *(this->counterW) == 0)
        {
            delete this->ptr;
            delete this->counterS;
            delete this->counterW;
        }
    }

}

template<class T>
void WeakPtr<T>::reset()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}