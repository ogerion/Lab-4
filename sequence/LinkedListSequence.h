#pragma once
#include "sequence/LinkedList.h"
#include "sequence/Sequence.h"
template <class T>
class LinkedListSequence : public Sequence<T>
{
	protected:
		LinkedList<T> list;
	public:
        LinkedListSequence<T>();
        LinkedListSequence<T>(LinkedList<T> list);

        const T& GetFirst() override;
        const T& GetLast() override;
        T& Get(size_t) override;

        void Append(T&) override;
        void Prepend(T&) override;
        void InsertAt(T&, size_t index) override;

        void Set(T, size_t) override;

        void Swap(size_t, size_t) override;

        ShrdPtr<Sequence<T>> GetSubSequence(size_t, size_t) override;
        ShrdPtr<Sequence<T>> Concat(Sequence<T>&) override;
};

template<class T>
LinkedListSequence<T>::LinkedListSequence()
{
    list = LinkedList<T>();
    this->size = 0;
}

template<class T>
LinkedListSequence<T>::LinkedListSequence(LinkedList<T> list)
{
    this->list = list;
    this->size = list.GetLenght();
}


template <class T>
const T& LinkedListSequence<T>::GetFirst()
{
    return list.GetFirst();
}

template <class T>
const T& LinkedListSequence<T>::GetLast()
{
    return list.GetLast();
}

template <class T>
T& LinkedListSequence<T>::Get(size_t index)
{
    return list.Get(index);
}

template <class T>
void LinkedListSequence<T>::Append(T& item)
{
    list.Append(item);
    this->size += 1;
}

template <class T>
void LinkedListSequence<T>::Prepend(T& item)
{
    list.Prepend(item);
    this->size += 1;
}

template <class T>
void LinkedListSequence<T>::InsertAt(T& item, size_t index)
{
    list.InsertAt(item,index);
    this->size += 1;
}

template <class T>
ShrdPtr<Sequence<T>> LinkedListSequence<T>::GetSubSequence(size_t startIndex, size_t endIndex)
{
    LinkedListSequence<T> * res = new LinkedListSequence<T>(list.GetSubLinkedList(startIndex, endIndex));
    return ShrdPtr<Sequence<T>>(res);
}


template <class T>
ShrdPtr<Sequence<T>> LinkedListSequence<T>::Concat(Sequence<T>& other)
{
    LinkedListSequence<T>* res = new LinkedListSequence<T>();
    for (int i = 0; i < this->size; i++)
    {
        T temp = this->Get(i);
        res->Append(temp);
    }
    for (int i = 0; i < other.GetLenght(); i++)
    {
        T temp = other.Get(i);
        res->Append(temp);
    }
    return ShrdPtr<Sequence<T>>(res);
}

template <class T>
void LinkedListSequence<T>::Swap(size_t indexOne, size_t indexTwo)
{
    T temp1 = this->list.Get(indexOne);
    T temp2 = this->list.Get(indexTwo);

    this->list.Set(temp2, indexOne);
    this->list.Set(temp1, indexTwo);
}

template <class T>
void LinkedListSequence<T>::Set(T item, size_t index)
{
    this->list.Set(item, index);
}