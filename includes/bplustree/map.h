#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <iomanip>
#include <stack>
#include <cassert>

#include "bplustree.h"
#include "pair.h"

using namespace std;

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;

    class Iterator
    {
    public:
        friend class Map;

        Iterator(typename map_base::Iterator it = NULL) : _it(it) {}

        Iterator operator++(int unused)
        {
            assert(_it != NULL && "Iterator should not be NULL.");
            Iterator hold = *this;
            ++_it;
            return hold;
        }

        Iterator operator++()
        {
            assert(_it != NULL && "Iterator should not be NULL.");
            ++_it;
            return *this;
        }

        Pair<K, V> operator*()
        {
            assert(_it != NULL && "Iterator should not be NULL.");
            return *_it;
        }

        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._it == rhs._it;
        }

        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    Map();
    
    Iterator begin();
    Iterator end();

    int size() const;
    bool empty() const;

    V &operator[](const K &key);
    const V &operator[](const K &key) const;

    V &at(const K &key);
    const V &at(const K &key) const;

    void insert(const K &k, const V &v);
    void erase(const K &key);
    void clear();
    V get(const K &key);

    Iterator find(const K &key);
    bool contains(const Pair<K, V> &target) const;

    int count(const K &key);
    Iterator lower_bound(const K &key);
    Iterator upper_bound(const K &key);

    bool is_valid() { return map.is_valid(); }

    friend ostream &operator<<(ostream &outs, const Map<K, V> &print_me)
    {
        outs << print_me.map;
        return outs;
    }

private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

template <typename K, typename V>
Map<K, V>::Map() : key_count(0) {}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin()
{
    return Iterator(map.begin());
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end()
{
    return Iterator(map.end());
}

template <typename K, typename V>
int Map<K, V>::size() const
{
    return key_count;
}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    assert(key_count == 0 && map.empty() || key_count != 0 && !map.empty());

    return map.empty();
}

template <typename K, typename V>
V &Map<K, V>::operator[](const K &key)
{
    return at(key);
}

template <typename K, typename V>
const V &Map<K, V>::operator[](const K &key) const
{
    return at(key);
}

template <typename K, typename V>
V &Map<K, V>::at(const K &key)
{
    // if the key wasn't already in the map, at() will add it, so increment key_count
    if (!map.contains(key))
        ++key_count;

    return map.get(key).value;
}

template <typename K, typename V>
const V &Map<K, V>::at(const K &key) const
{
    return map.get(key).value;
}

template <typename K, typename V>
void Map<K, V>::insert(const K &k, const V &v)
{
    // if the key wasn't already in the map, insert() will add it, so increment key_count
    if (!map.contains(k))
        ++key_count;

    map.insert(Pair<K, V>(k, v));
}

template <typename K, typename V>
void Map<K, V>::erase(const K &key)
{
    // if the key was found in the map, decrement key_count
    if (map.contains(key))
        --key_count;

    map.remove(key);
}

template <typename K, typename V>
void Map<K, V>::clear()
{
    map.clear_tree();
    key_count = 0;
}

template <typename K, typename V>
V Map<K, V>::get(const K &key)
{
    return at(key);
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K &key)
{
    return Iterator(map.find(key));
}

template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V> &target) const
{
    return map.contains(target);
}

template <typename K, typename V>
int Map<K, V>::count(const K &key)
{
    return contains(key); // regular maps can only map one value to each index, so just return the boolean returned by contains()
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K &key)
{
    return Iterator(map.lower_bound(key));
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K &key)
{
    return Iterator(map.upper_bound(key));
}

#endif /* MAP_H */
