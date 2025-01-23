#pragma once
#include "UnqPtr.h"
#include "ShrdPtr.h"
template<class T>
class Node
{
public:
    T val;
    ShrdPtr<Node<T>> next;
    ShrdPtr<Node<T>> prev;

    Node()
    {
        this->val = T();
        this->next = ShrdPtr<Node<T>>();
        this->prev = ShrdPtr<Node<T>>();
    }
    Node( T& value)
    {
        this->val = value;
        this->next = ShrdPtr<Node<T>>();
        this->prev = ShrdPtr<Node<T>>();
    }

    Node( T& value, ShrdPtr<Node<T>>& n, ShrdPtr<Node<T>>& p)
    {
        this->val = value;
        this->next = n;
        this->prev = p;
    }

};

template <class T>
class LinkedList
{
protected:
    ShrdPtr<Node<T>> base;
    size_t size;
public:
    LinkedList();

    LinkedList<T>* Append( T&) ;
    LinkedList<T>* Prepend(T&) ;
    LinkedList<T>* InsertAt(T&, size_t) ;

    const T& GetFirst() ;
    const T& GetLast() ;
     T& Get(size_t) ;

    void Set(T, size_t);

    LinkedList<T>& GetSubLinkedList(size_t, size_t) ;

    LinkedList<T>& Concat(LinkedList<T>& seq) ;

    size_t GetLenght()
    {
        return size;
    }
};

template <class T>
LinkedList<T>::LinkedList()
{
    size = 0;
    base = ShrdPtr<Node<T>>();
}

template <class T>
LinkedList<T>* LinkedList<T>::Append(T& item)
{
    ShrdPtr<Node<T>> newNode = ShrdPtr<Node<T>>(new Node<T>(item));
    if (size == 0)
    {
        base = std::move(newNode);
        base->next = std::move(base);
        base->prev = std::move(base);
    }
    else if (size == 1)
    {
        base->next = std::move(newNode);
        base->prev = std::move(base->next);
        base->next->prev = std::move(base);
        base->next->next = std::move(base);
    }
    else
    {
        base->prev->next = std::move(newNode);
        base->prev->next->next = std::move(base);
        base->prev->next->prev = std::move(base->prev);
        base->prev = std::move(base->prev->next);
    }
    size += 1;
    return this;
}

template <class T>
LinkedList<T>* LinkedList<T>::Prepend(T& item)
{
    ShrdPtr<Node<T>> newNode = ShrdPtr<Node<T>>(new Node<T>(item));
    if (size == 0)
    {
        base = std::move(newNode);
        base->next = std::move(base);
        base->prev = std::move(base);
    }
    else if (size == 1)
    {
        base->next = std::move(newNode);
        base->prev = std::move(base->next);
        base->next->prev = std::move(base);
        base->next->next = std::move(base);
        base = std::move(newNode);

    }
    else
    {
        base->prev->next = std::move(newNode);
        newNode->prev = std::move(base->prev);
        base->prev = std::move(newNode);
        newNode->next = std::move(base);
        base = std::move(newNode);

    }
    size += 1;
    return this;
}

template <class T>
LinkedList<T>* LinkedList<T>::InsertAt(T& item, size_t pos)
{
    ShrdPtr<Node<T>> newNode = ShrdPtr<Node<T>>(new Node<T>(item));
    if (size == 0)
    {
        base = std::move(newNode);
        base->next = std::move(base);
        base->prev = std::move(base);
    }
    else
    {
        ShrdPtr<Node<T>> actual(std::move(base));
        for (int i = 0; i < pos - 1; i++)
        {
            actual = std::move(actual->next);
        }
        actual = std::move(actual->next);
        newNode->next = std::move(actual);
        newNode->prev = std::move(actual->prev);
        actual->prev->next = std::move(newNode);
        actual->prev = std::move(newNode);
    }
    size += 1;
    return this;
}

template <class T>
const T& LinkedList<T>::GetFirst()
{
    if (this->size != 0)
    {
        return base->val;
    }
    else
    {
        throw "There are no items in list!";
    }
}

template <class T>
const T& LinkedList<T>::GetLast()
{
    if (this->size != 0)
    {
        return base->prev->val;
    }
    else
    {
        throw "Threre are no intems in list!";
    }
}

template <class T>
 T& LinkedList<T>::Get(size_t index)
{
    if (this->size != 0)
    {
        ShrdPtr<Node<T>> actual = std::move(base);
        for (int i = 0; i < index; i++)
        {
            actual = std::move(actual->next);
        }
        T &res = actual->val;

        return res;
    }
    else
    {
        throw "There are no items in list!";
    }
}

template<class T>
LinkedList<T>& LinkedList<T>::GetSubLinkedList(size_t startIndex, size_t endIndex)
{
    LinkedList<T>* res = new LinkedList<T>();
    for (int i = startIndex; i < endIndex; i++)
    {
        T temp = this->Get(i);
        res->Append(temp);
    }

    return *res;
}

template <class T>
LinkedList<T>& LinkedList<T>::Concat(LinkedList<T>& seq)
{
    LinkedList<T>* res = new LinkedList<T>();
    for (int i = 0; i < this->size; i++)
    {
        T temp1 = this->Get(i);
        res->Append(temp1);
    }
    for (int i = 0; i < seq.GetLenght(); i++)
    {
        T temp2 = seq.Get(i);
        res->Append(temp2);
    }
    return *res;
}

template <class T>
void LinkedList<T>::Set(T val, size_t index)
{
    if (this->size != 0)
    {
        ShrdPtr<Node<T>> actual = std::move(base);
        for (int i = 0; i < index; i++)
        {
            actual = std::move(actual->next);
        }
        actual->val = val;
    }
    else
    {
        throw "There are no items in list!";
    }
}