#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <iomanip>
#include <stack>
#include <sstream>
#include <cassert>

using namespace std;

template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K &k = K(), const V &v = V());

    friend ostream &operator<<(ostream &outs, const Pair<K, V> &print_me)
    {
        outs << to_string(print_me);
        return outs;
    }
    friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator!=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key != rhs.key;
    }
    friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator>=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend Pair<K, V> operator+(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
Pair<K, V>::Pair(const K &k, const V &v) : key(k), value(v) {}

template <typename K, typename V>
string to_string(const Pair<K, V> &pair)
{
    stringstream s;
    s << pair.key << ": " << pair.value;

    return s.str();
}

#endif /* PAIR_H */
