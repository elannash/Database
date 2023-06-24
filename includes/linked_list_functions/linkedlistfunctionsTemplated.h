#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H
#define LINKEDLISTFUNCTIONSTEMPLATED_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../node/node.h"
using namespace std;

// Linked List General Functions:
template <typename T>
ostream &_print_list(node<T> *head, ostream &outs = cout);

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head,
                      T key);

template <typename T>
node<T> *_insert_head(node<T> *&head,
                      T insert_this);

// insert after ptr: insert head if marker null
template <typename T>
node<T> *_insert_after(node<T> *&head,
                       node<T> *after_this,
                       T insert_this);

// insert before ptr: insert head if marker null
template <typename T>
node<T> *_insert_before(node<T> *&head,
                        node<T> *before_this,
                        T insert_this);

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this);

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this);

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head);

// duplicate the list, return pointer to last node in dest...
//      use this function in your queue big three
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head);

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos);

/****************************************************************************************************/

template <typename T>
ostream &_print_list(node<T> *head, ostream &outs)
{
    outs << "H->";
    for (node<T> *walker = head; walker != nullptr; walker = walker->_next)
    {
        outs << " <-[" << walker->_item << "]-> ";
    }
    outs << "|||";

    return outs;
}

template <typename T>
void _print_list_backwards(node<T> *head)
{
    if (head == nullptr) // stopping case
    {
        cout << "|||";
    }
    else
    {
        _print_list_backwards(head->_next); // this is called until head==nullptr
        cout << head->_item;
    }

    // this function signature offers no way of knowing what the true head of the list is
    // so i'm not printing Head in the output
}

template <typename T>
node<T> *_search_list(node<T> *head, T key)
{
    bool debug = true;

    // walk a walker from the head of the list to the end
    // check whether the walker's item is the key during each step
    // asserts if the key was not found

    node<T> *walker = head;

    while (walker != nullptr)
    {
        if (walker->_item == key)
        {
            return walker;
        }
        walker = walker->_next;
    }

    if (debug)
    {
        cout << "KEY: " << key << endl;
    }

    return nullptr;
}

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this)
{
    // declare a new node
    // store the item in new node
    // point the new node to the head node
    // point the head pointer to the new node
    // if head->_next is not nullptr, set the head->_next node's _prev to hold
    // return the new head

    node<T> *hold = new node<T>;

    hold->_item = insert_this;
    hold->_next = head;
    head = hold;
    if (head->_next != nullptr)
    {
        head->_next->_prev = hold;
    }

    return head;
}

template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this)
{
    // check if after_this is nullptr (list empty), if it is, return _insert_head
    // otherwise, declare a new node
    // store the item in new node
    // set the new node _next pointer to after_this->_next
    // set hold's _prev pointer to after_this
    // set after_this->_next to the new node
    // if the node after newly inserted node is not nullptr, set it's _prev pointer to hold
    // return the new node

    if (after_this == nullptr)
    {
        after_this = _insert_head(head, insert_this);
        return head;
    }

    node<T> *hold = new node<T>;
    hold->_item = insert_this;
    hold->_next = after_this->_next;
    hold->_prev = after_this;
    after_this->_next = hold;

    if (hold->_next != nullptr)
        hold->_next->_prev = hold;

    return hold;
}

template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this)
{
    // if before_this is the head pointer, return insert_head
    // otherwise return insert_after on _previous_node(before_this)

    // because this iteration of _previous_node uses the _prev pointer, it is possible that before_this is not
    // in the list given by head
    // this code assumes that before_this IS on the same list and does not have any special returns if it is not

    if (before_this == head)
    {
        return _insert_head(head, insert_this);
    }

    return _insert_after(head, before_this->_prev, insert_this);
}

template <typename T>
node<T> *_previous_node(node<T> *prev_to_this)
{
    return prev_to_this->_prev;
}

template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    // if the node is the head node, set head to head->_next
    // if delete_this->_prev is not nullptr, set _prev's _next to the node after delete_this
    // if delete_this->_next is not nullptr, set _next's _prev to the node before delete_this
    // store delete_this's _item in a temp variable
    // call delete on delete_this
    // return the item stored in the temp variable

    assert(delete_this != nullptr && "delete_this cannot be nullptr");

    if (delete_this == head)
    {
        head = head->_next;
    }
    else
    {
        if (delete_this->_prev != nullptr)
        {
            delete_this->_prev->_next = delete_this->_next;
        }
        if (delete_this->_next != nullptr)
        {
            delete_this->_next->_prev = delete_this->_prev;
        }
    }
    T hold = delete_this->_item;
    delete delete_this;
    delete_this = nullptr;

    return hold;
}

template <typename T>
node<T> *_copy_list(node<T> *head)
{
    // create a new head pointer for the new list
    // create a walker for both the source and destination
    // while the source walker is not nullptr, call insert_after on destination walker and walk both walkers
    // return the destination head

    node<T> *dest_head = nullptr;
    node<T> *src_walker = head;
    node<T> *dest_walker = dest_head;

    while (src_walker != nullptr)
    {
        dest_walker = _insert_after(dest_head, dest_walker, src_walker->_item);
        src_walker = src_walker->_next;
    }

    return dest_head;
}

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    // this _copy_list returns the last node of the list

    // null terminate dest list
    // create a walker for both the source and destination
    // while the source walker is not nullptr, call insert_after on destination walker and walk both walkers
    // return the destination head

    dest = nullptr;
    node<T> *src_walker = src;
    node<T> *dest_walker = dest;

    while (src_walker != nullptr)
    {
        dest_walker = _insert_after(dest, dest_walker, src_walker->_item);
        src_walker = src_walker->_next;
    }

    return dest_walker;
}

template <typename T>
void _clear_list(node<T> *&head)
{
    while (head != nullptr)
    {
        _delete_node(head, head);
    }
}

template <typename T>
T &_at(node<T> *head, int pos)
{
    // starting from the head node
    // walk a walker pos times
    // return the walker

    node<T> *walker = head;

    for (int i = 0; i < pos; i++)
    {
        walker = walker->_next;
    }

    return walker->_item;
}

#endif /* LINKEDLISTFUNCTIONSTEMPLATED_H */
