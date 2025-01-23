#pragma once
#include "ShrdPtr.h"
template <class T>
class Sequence
{
    protected:
        size_t size;
    public:
        virtual const T & GetFirst() = 0;
        virtual const T & GetLast() = 0;
        virtual  T & Get(size_t) = 0;

        virtual void Append(T &) = 0;
        virtual void Prepend(T &) = 0;
        virtual void InsertAt(T &, size_t index) = 0;

        virtual void Set(T, size_t) = 0;

        int GetLenght() const
        {
            return this->size;
        };
        
        T & operator[] (const size_t index)
        {
            return this->Get(index);
        }
        
        Sequence<T> * operator + (const Sequence<T> * seq2)
        {
            return this->Concat(seq2);
        }        

        Sequence<T> & operator += (const Sequence<T> * seq2)
        {
            Sequence * res = this->Concat(seq2);
            return *res;
        }

        virtual void Swap(size_t, size_t) = 0;

        virtual ShrdPtr<Sequence<T>> GetSubSequence(size_t,size_t) = 0;
        virtual ShrdPtr<Sequence<T>> Concat(Sequence<T> &) = 0;

};
