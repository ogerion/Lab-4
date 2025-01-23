#pragma once
#include "Ptr.h"

template<class T>
class WeakPtr;

template <class T>
class ShrdPtr : public Ptr<T> {
private:
    size_t* counterS;
    size_t* counterW;
    void release();

public:
    ShrdPtr();

    ShrdPtr(T*);

    template<class U>
    ShrdPtr(ShrdPtr<U>&&);

    template<class U>
    ShrdPtr(const ShrdPtr<U>&);

    template<class U>
    ShrdPtr(WeakPtr<U>&&);

    template<class U>
    ShrdPtr(const WeakPtr<U>&);

    template<class U>
    ShrdPtr<T>& operator=(ShrdPtr<U>&&);

    template<class U>
    ShrdPtr<T>& operator=(const ShrdPtr<U>&);

    template<class U>
    ShrdPtr<T>& operator=(WeakPtr<U>&&);

    template<class U>
    ShrdPtr<T>& operator=(const WeakPtr<U>&);

    size_t countW();

    size_t countS();

    size_t* getWCounter() const
    {
        return this->counterW;
    }

    size_t* getSCounter() const
    {
        return this->counterS;
    }

    T* get() const override;

    T* operator->() const override;

    ~ShrdPtr();

    void reset();
};

template<class T>
ShrdPtr<T>::ShrdPtr()
{
    this->ptr = nullptr;
    this->counterS = new size_t(1);
    this->counterW = new size_t(0);
}

template<class T>
ShrdPtr<T>::ShrdPtr(T* ptr)
{
    this->ptr = ptr;
    this->counterS = new size_t(1);
    this->counterW = new size_t(0);
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(ShrdPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(const ShrdPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = (T*)(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(WeakPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(const WeakPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = (static_cast<T*>(other.get()));
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(ShrdPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(const ShrdPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}


template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(WeakPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(const WeakPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        if (this->counterS != nullptr)
        {
            *(this->counterS) += 1;
        }
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
ShrdPtr<T>::~ShrdPtr()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}

template <class T>
size_t ShrdPtr<T>::countW()
{
    if (this->counterW != nullptr)
    {
        return *(this->counterW);
    }
    return size_t(0);
}

template <class T>
size_t ShrdPtr<T>::countS()
{
    if (this->counterS != nullptr)
    {
        return *(this->counterS);
    }
    return size_t(0);
}

template <class T>
T* ShrdPtr<T>::get() const
{
    if (*(this->counterS) != 0)
    {
        return this->ptr;
    }
    else
    {
        throw "All shared pointer are expired!";
    }
}

template <class T>
T* ShrdPtr<T>::operator->() const
{
    if (*(this->counterS) != 0)
    {
        return this->ptr;
    }
    else
    {
        throw "All shared pointer are expired!";
    }
}

template <class T>
void ShrdPtr<T>::release()
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
void ShrdPtr<T>::reset()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}
