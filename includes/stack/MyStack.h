#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename ITEM_TYPE>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;                       //give access to list to access _ptr
        Iterator() { _ptr = nullptr; }            //default ctor
        Iterator(node<ITEM_TYPE> *p) : _ptr(p) {} //Point Iterator to where
                                                  //  p is pointing to
        ITEM_TYPE operator*()
        {
            //assert that _ptr is not nullptr and then return it's item

            assert(_ptr);
            return _ptr->_item;
        } //dereference operator
        bool is_null()
        {
            return !_ptr;
        }                                                                   //true if _ptr is NULL
        friend bool operator!=(const Iterator &left, const Iterator &right) //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right) //true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++()
        {
            assert(_ptr);
            _ptr = _ptr->_next; //iterate first before returning

            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused)
        {
            assert(it._ptr);
            Iterator hold = it; //we want to return the iterator before incrementing
            it._ptr = it._ptr->_next;

            return hold;
        }

    private:
        node<ITEM_TYPE> *_ptr; //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE> &copyMe);
    ~Stack();
    Stack<ITEM_TYPE> &operator=(const Stack<ITEM_TYPE> &RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template <typename T>
    friend ostream &operator<<(ostream &outs, const Stack<T> &printMe);
    Iterator begin() const; //Iterator to the head node
    Iterator end() const;   //Iterator to NULL
    int size() const { return _size; }

    void clear(); //for debugging purposes

private:
    node<ITEM_TYPE> *_top;
    int _size;
};

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack()
{
    _top = nullptr;
    _size = 0;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE> &copyMe)
{
    //set _top to the new node returned by _copy_list
    //set _size to copyMe._size

    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack()
{
    //call clear_list on top
    //set _size to 0

    _clear_list(_top);
    _size = 0;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE> &Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE> &RHS)
{
    //check for self-reference, if self-reference return *this
    //otherwise, clear_list and set _top to node returned by _copy_list
    //set _size to RHS._size

    if (&RHS == this)
    {
        return *this;
    }

    _clear_list(_top);
    _top = _copy_list(RHS._top);
    _size = RHS._size;

    return *this;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    assert(_top != nullptr && "_top was nullptr when trying to access item");

    return _top->_item;
}

template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty()
{
    return _size == 0;
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    _size++;
    _insert_head(_top, item);
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    assert(_top != nullptr && "_top was nullptr when popping");

    _size--;
    return _delete_node(_top, _top);
}

template <typename T>
ostream &operator<<(ostream &outs, const Stack<T> &printMe)
{
    outs << "[" << printMe.size() << "] ";
    return _print_list(printMe._top, outs);
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const
{
    //return an iterator to the top node

    return Iterator(_top);
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const
{
    //return an iterator to nullptr

    return Iterator(nullptr);
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::clear()
{
    _clear_list(_top);
    _size = 0;
}

#endif /* MYSTACK_H */
