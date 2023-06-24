#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;               // give access to list to access _ptr
        Iterator() { _ptr = nullptr; }    // default ctor
        Iterator(node<T> *p) : _ptr(p) {} // Point Iterator to where
                                          //   p is pointing to
        T operator*()
        {
            // assert that _ptr is not nullptr and then return it's item

            assert(_ptr);
            return _ptr->_item;
        } // dereference operator
        bool is_null()
        {
            return !_ptr;
        }                                                                   // true if _ptr is NULL
        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++()
        {
            assert(_ptr);
            _ptr = _ptr->_next; // iterate first before returning

            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused)
        {
            assert(it._ptr);
            Iterator hold = it; // we want to return the iterator before incrementing
            it._ptr = it._ptr->_next;

            return hold;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T> &copyMe);
    ~Queue();
    Queue &operator=(const Queue<T> &RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

    void clear(); // for debugging purposes

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;
};

template <typename T>
Queue<T>::Queue()
{
    // set both private member pointers to nullptr
    // set the size to zero

    _front = _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &copyMe)
{
    // set _front pointer to the node returned by _copy_list
    // set _size to copyMe._size

    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template <typename T>
Queue<T>::~Queue()
{
    // clear the list
    // set _front to nullptr
    // set the size to zero

    _clear_list(_front);
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    // check for self-reference
    // if self-reference, just return *this
    // otherwise call _clear_list and then set _front to node returned by _copy_list

    if (&RHS == this)
        return *this;

    _clear_list(_front);
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;

    return *this;
}

template <typename T>
bool Queue<T>::empty()
{
    assert((_front == nullptr && _rear == nullptr && _size == 0) || (_front != nullptr && _rear != nullptr && _size != 0));

    return _size == 0;
}

template <typename T>
T Queue<T>::front()
{
    assert(_front != nullptr && "_front was nullptr when trying to access item");

    return _front->_item;
}

template <typename T>
T Queue<T>::back()
{
    assert(_rear != nullptr && "_rear was nullptr when trying to access item");

    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    _rear = _insert_after(_front, _rear, item);
    _size++;
}

template <typename T>
T Queue<T>::pop()
{
    assert(_front != nullptr && "_front was nullptr when popping");

    T popped;

    popped = _delete_node(_front, _front);

    // if front is nullptr after popping, we must set rear to nullptr
    if (_front == nullptr)
        _rear = nullptr;

    _size--;

    return popped;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    // return an iterator to the first node

    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    // return an iterator to nullptr

    return Iterator(nullptr);
}

template <typename T>
void Queue<T>::print_pointers()
{
    assert(_front && "front was nullptr");
    assert(_rear && "rear was nullptr");

    cout << "Front: " << _front->_item << endl
         << "Rear: " << _rear->_item << endl;
}

template <typename TT>
ostream &operator<<(ostream &outs, const Queue<TT> &printMe)
{
    outs << "[" << printMe.size() << "] ";
    return _print_list(printMe._front, outs);
}

template <typename T>
void Queue<T>::clear()
{
    _clear_list(_front);
    _rear = nullptr;
    _size = 0;
}

#endif /* MYQUEUE_H */
