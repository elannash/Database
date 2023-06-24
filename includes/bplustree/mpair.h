#ifndef MPAIR_H
#define MPAIR_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <sstream>
#include <cassert>

using namespace std;

template <typename K, typename V>
struct MPair
{
    K key;
    vector<V> value_list;

    MPair(const K &k = K());
    MPair(const K &k, const V &v);
    MPair(const K &k, const vector<V> &vlist);

    friend ostream &operator<<(ostream &outs, const MPair<K, V> &print_me)
    {
        outs << to_string(print_me);
        return outs;
    }
    friend bool operator==(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator!=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key != rhs.key;
    }
    friend bool operator<(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator<=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator>(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator>=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend MPair<K, V> operator+(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        assert(lhs.key == rhs.key && "Keys should be equal when adding.");

        MPair<K, V> result(lhs);

        for (typename vector<V>::const_iterator it = rhs.value_list.begin(); it != rhs.value_list.end(); it++)
            result.value_list += *it;

        return result;
    }
};

template <typename K, typename V>
MPair<K, V>::MPair(const K &k) : key(k) {}

template <typename K, typename V>
MPair<K, V>::MPair(const K &k, const V &v) : key(k)
{
    value_list += v;
}

template <typename K, typename V>
MPair<K, V>::MPair(const K &k, const vector<V> &vlist) : key(k), value_list(vlist) {}

template <typename K, typename V>
string to_string(const MPair<K, V> &mpair)
{
    stringstream s;

    s << mpair.key << ": [";

    for (V item : mpair.value_list)
        s << item << " ";

    s << "]";

    return s.str();
}

#endif /* MPAIR_H */
