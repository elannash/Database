#ifndef BTREE_ARRAY_FUNCTIONS_H
#define BTREE_ARRAY_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

#include "../stl_utils/vector_utilities.h"

using namespace std;

template <class T>
T maximal(const T &a, const T &b); // return the larger of the two items

template <class T>
void swap_items(T &a, T &b); // swap the two items

template <class T>
int index_of_maximal(T data[], int n); // return index of the largest item in data

template <class T>
void ordered_insert(T data[], int &n, T entry);

template <class T>
int first_ge(const T data[], int n, const T &entry);

template <class T>
void attach_item(T data[], int &n, const T &entry);

template <class T>
void insert_item(T data[], int i, int &n, T entry);

template <class T>
void detach_item(T data[], int &n, T &entry);

template <class T>
void delete_item(T data[], int i, int &n, T &entry);

template <class T>
void merge(T data1[], int &n1, T data2[], int &n2);

template <class T>
void append_array(T data1[], int &n1, T data2[], int &n2);

template <class T>
void prepend_array(T data1[], int &n1, T data2[], int &n2);

template <class T>
void insert_array(T data1[], int &n1, T data2[], int &n2, int index = 0);

template <class T>
void split(T data1[], int &n1, T data2[], int &n2);

template <class T>
void copy_array(T dest[], const T src[],
                int &dest_size, int src_size);

template <class T>
void print_array(const T data[], int n, int pos = -1);

template <class T>
bool is_gt(const T data[], int n, const T &item);

template <class T>
bool is_le(const T data[], int n, const T &item);

/*******************************************************************************/

/**
 * @brief Returns the largest of the two items. If both items are equal, then the second item is returned.
 *
 * @tparam T
 * @param a
 * @param b
 * @return T
 */
template <class T>
T maximal(const T &a, const T &b)
{
    if (a > b)
        return a;
    else // b is greater, or they are both equal and we can return b
        return b;
}

/**
 * @brief Swaps two items. After swapping, a will contain the contents of b, and b will contain the contents of a.
 *
 * @tparam T
 * @param a
 * @param b
 */
template <class T>
void swap_items(T &a, T &b)
{
    T hold;

    hold = a;
    a = b;
    b = hold;
}

/**
 * @brief Returns the index of the largest item. If two items are the same size, the index of the first instance of that item is returned.
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @return int
 */
template <class T>
int index_of_maximal(T data[], int n)
{
    // set index_of_largest to the first index
    // iterate through the array
    // if the item at i is largest than the item at index_of_largest, then set largest_index to i

    int index_of_largest = 0;

    for (int i = 1; i < n; i++)
    {
        if (data[i] > data[index_of_largest])
            index_of_largest = i;
    }

    return index_of_largest;
}

/**
 * @brief Insert item in an ordered manner. Data array should have space to insert entry before call to function.
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param entry
 */
template <class T>
void ordered_insert(T data[], int &n, T entry)
{
    // declare shift_right_here index and set to the index returned by first_ge()
    // call insert_item using the array, shift_right_here index, size, and entry

    int shift_right_here;

    shift_right_here = first_ge(data, n, entry);
    insert_item(data, shift_right_here, n, entry);
}

/**
 * @brief Returns the index of the first item that is greater than or equal to entry. If no item in the list is greater than or equal to entry, the size of the list is returned.
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param entry
 * @return int
 */
template <class T>
int first_ge(const T data[], int n, const T &entry)
{
    // initialize first_greater_equal_index to n, so that if no item in the array is greater than or equal to entry, size is returned
    int first_greater_equal_index = n;

    for (int i = 0; i < n; i++)
    {
        if (!(data[i].key < entry.key)) // if the item at i is greater than or equal to entry, set first_greater_equal_index to i and break the loop
        {
            first_greater_equal_index = i;
            break;
        }
    }

    return first_greater_equal_index;
}

/**
 * @brief Appends item to the end of an array and increments the size passed in.
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param entry
 */
template <class T>
void attach_item(T data[], int &n, const T &entry)
{
    // add entry to data[n]
    // increment size after

    data[n] = entry;
    n++;
}

/**
 * @brief Inserts an item at index i and increments size.
 *
 * @tparam T
 * @param data
 * @param i Index
 * @param n Size of the array being passed in.
 * @param entry
 */
template <class T>
void insert_item(T data[], int i, int &n, T entry)
{
    assert(i >= 0 && "index should be positive");

    // in a loop, shift everything right starting from the index passed in
    // after the loop, store entry at data[i]
    // increment size last

    for (int j = n; j > i; j--)
        data[j] = data[j - 1];

    data[i] = entry;
    n++;
}

/**
 * @brief Deletes the item at the end of the list and stores it in entry.
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param entry
 */
template <class T>
void detach_item(T data[], int &n, T &entry)
{
    assert(n > 0 && "size should be greater than zero");

    // decrement the size first
    // set entry to data[n], which is the element that is now one past the end of the array

    n--;
    entry = data[n];
}

/**
 * @brief Deletes the item as index i and stores it in entry.
 *
 * @tparam T
 * @param data
 * @param i Index
 * @param n Size of the array being passed in.
 * @param entry
 */
template <class T>
void delete_item(T data[], int i, int &n, T &entry)
{
    assert(n > 0 && "size should be greater than zero");
    assert(i >= 0 && "index should be positive");
    assert(i < n && "index should be less than size");

    // decrement size first
    // store the item at data[i] in entry
    // in a loop starting from the end of the array, set data[j-1] t data[j

    n--;
    entry = data[i];

    for (int j = i; j < n; j++)
        data[j] = data[j + 1];
}

/**
 * @brief Merges data2 with data1 array. Assumes arrays are sorted beforehand, and merges in a sorted manner. Size of first array is set to the appropriate amount after appending. Size of second array is set to 0 at the end of operation.
 *
 * @tparam T
 * @param data1
 * @param n1 Size of the first array being passed in.
 * @param data2
 * @param n2 Size of the second array being passed in.
 */
template <class T>
void merge(T data1[], int &n1, T data2[], int &n2)
{
    for (int i = 0; i < n2; i++)
        ordered_insert(data1, n1, data2[i]);

    n2 = 0;
}

/**
 * @brief Appends data2 array to the end of data1 array. Size of data2 array is set to 0 after operation.
 *
 * @tparam T
 * @param data1
 * @param n1 Size of the first array being passed in.
 * @param data2
 * @param n2 Size of the second array being passed in.
 */
template <class T>
void append_array(T data1[], int &n1, T data2[], int &n2)
{
    for (int i = 0; i < n2; i++)
        attach_item(data1, n1, data2[i]);

    n2 = 0;
}

/**
 * @brief Prepends data2 array to beginning of data1 array. Size of data2 array is set to 0 after operation.
 *
 * @tparam T
 * @param data1
 * @param n1 Size of the first array being passed in.
 * @param data2
 * @param n2 Size of the second array being passed in.
 */
template <class T>
void prepend_array(T data1[], int &n1, T data2[], int &n2)
{
    for (int i = n2 - 1; i >= 0; i--)
        insert_item(data1, 0, n1, data2[i]);

    n2 = 0;
}

/**
 * @brief Inserts data2 array into data1 array at position index. Index is 0 by default. Size of data2 array is set to 0 after operation.
 *
 * @tparam T
 * @param data1
 * @param n1
 * @param data2
 * @param n2
 * @param index
 */
template <class T>
void insert_array(T data1[], int &n1, T data2[], int &n2, int index)
{
    for (int i = n2 - 1; i >= 0; i--)
        insert_item(data1, index, n1, data2[i]);

    n2 = 0;
}

/**
 * @brief Moves n/2 elements from the right half of data1 array and appends to the end of data2 array
 *
 * @tparam T
 * @param data1
 * @param n1 Size of the first array being passed in.
 * @param data2
 * @param n2 Size of the second array being passed in.
 */
template <class T>
void split(T data1[], int &n1, T data2[], int &n2)
{
    // calculate the number of items to split (n1/2), and subtract from n1 to get the index where we will split from
    // in a loop starting from the index we split from in data1, loop until end of data1 and call attach_item() onto data2 using data1[i]
    // set n1 to split_from_here (which will be the new size)

    int split_from_here = n1 - (n1 / 2);

    for (int i = split_from_here; i < n1; i++)
        attach_item(data2, n2, data1[i]);

    n1 = split_from_here; // since split_from_here is now one past the end of the first array, it also holds the new size of the first array
}

/**
 * @brief Copy the contents from src into dest. dest_size is set to src_size.
 *
 * @tparam T
 * @param dest
 * @param src
 * @param dest_size
 * @param src_size
 */
template <class T>
void copy_array(T dest[], const T src[], int &dest_size, int src_size)
{
    dest_size = src_size;

    for (int i = 0; i < src_size; i++)
        dest[i] = src[i];
}

/**
 * @brief Print the contents of the array. Passing in a position will also print the item at that position.
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param pos
 */
template <class T>
void print_array(const T data[], int n, int pos)
{
    assert(pos < n && "index (pos) should be less than size of array");

    string spaces = "   ";

    for (int i = 0; i < n; i++)
    {
        cout << "[" << data[i] << "]";
    }

    // if pos passed in, print an arrow under that element in the array
    // if(pos != -1)
}

/**
 * @brief
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param item
 * @return true
 * @return false
 */
template <class T>
bool is_gt(const T data[], int n, const T &item)
{
    // loop through array
    // if item is less than or equal to any item in the array, then return false
    // otherwise true is returned by default

    for (int i = 0; i < n; i++)
        if (item <= data[i])
            return false;

    return true;
}

/**
 * @brief
 *
 * @tparam T
 * @param data
 * @param n Size of the array being passed in.
 * @param item
 * @return true
 * @return false
 */
template <class T>
bool is_le(const T data[], int n, const T &item)
{
    return !is_gt(data, n, item);
}

#endif /* BTREE_ARRAY_FUNCTIONS_H */
