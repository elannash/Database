#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list); // print vector list

template <typename T>
vector<T> &operator+=(vector<T> &vec1, const vector<T> &vec2);

template <typename T>
vector<T> &operator+=(vector<T> &list, const T &addme); // list.push_back addme

/**
 * @brief Prints the contents of a vector.
 *
 * @tparam T
 * @param outs
 * @param list
 * @return ostream&
 */
template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list)
{
    for (T item : list)
        outs << item << " ";

    return outs;
}

/**
 * @brief Append vec2 to vec1
 *
 * @tparam T
 * @param list
 * @param addme
 * @return vector<T>&
 */
template <typename T>
vector<T> &operator+=(vector<T> &vec1, const vector<T> &vec2)
{
    for (T item : vec2)
        vec1.push_back(item);

    return vec1;
}

/**
 * @brief Append an item to the vector.
 *
 * @tparam T
 * @param list
 * @param addme
 * @return vector<T>&
 */
template <typename T>
vector<T> &operator+=(vector<T> &list, const T &addme)
{
    list.push_back(addme);

    return list;
}

#endif /* VECTOR_UTILITIES_H */
