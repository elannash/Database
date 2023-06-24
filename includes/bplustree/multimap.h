#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <iostream>
#include <iomanip>
#include <stack>
#include <cassert>

#include "bplustree.h"
#include "mpair.h"

using namespace std;

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;

    class Iterator
    {
    public:
        friend class MMap;

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
        MPair<K, V> operator*()
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
            return !(lhs._it == rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

    Iterator begin();
    Iterator end();

    int size() const;
    bool empty() const;

    const vector<V> &at(const K &key) const;
    vector<V> &at(const K &key);

    const vector<V> &operator[](const K &key) const;
    vector<V> &operator[](const K &key);

    void insert(const K &k, const V &v);
    void erase(const K &key);
    void clear();

    bool contains(const K &key) const;
    vector<V> &get(const K &key);

    Iterator find(const K &key);
    int count(const K &key);

    Iterator lower_bound(const K &key);
    Iterator upper_bound(const K &key);

    bool is_valid() { return mmap.is_valid(); }

    ostream &print_lookup(ostream &outs = cout); // print the mmap as a table

    friend ostream &operator<<(ostream &outs, const MMap<K, V> &print_me)
    {
        outs << print_me.mmap << endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

template <typename K, typename V>
MMap<K, V>::MMap() {}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin()
{
    return Iterator(mmap.begin());
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end()
{
    return Iterator(mmap.end());
}

template <typename K, typename V>
int MMap<K, V>::size() const
{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K, V>::empty() const
{
    return mmap.empty();
}

template <typename K, typename V>
const vector<V> &MMap<K, V>::at(const K &key) const
{
    return mmap.get(key).value_list;
}

template <typename K, typename V>
vector<V> &MMap<K, V>::at(const K &key)
{
    return mmap.get(key).value_list;
}

template <typename K, typename V>
const vector<V> &MMap<K, V>::operator[](const K &key) const
{
    return at(key);
}

template <typename K, typename V>
vector<V> &MMap<K, V>::operator[](const K &key)
{
    return at(key);
}

template <typename K, typename V>
void MMap<K, V>::insert(const K &k, const V &v)
{
    mmap.insert(MPair<K, V>(k, v));
}

template <typename K, typename V>
void MMap<K, V>::erase(const K &key)
{
    mmap.remove(key);
}

template <typename K, typename V>
void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

template <typename K, typename V>
bool MMap<K, V>::contains(const K &key) const
{
    return mmap.contains(key);
}

template <typename K, typename V>
vector<V> &MMap<K, V>::get(const K &key)
{
    return at(key);
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K &key)
{
    return Iterator(mmap.find(key));
}

template <typename K, typename V>
int MMap<K, V>::count(const K &key)
{
    return at(key).size();
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K &key)
{
    return Iterator(mmap.lower_bound(key));
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K &key)
{
    return Iterator(mmap.upper_bound(key));
}

template <typename K, typename V>
ostream &MMap<K, V>::print_lookup(ostream &outs)
{
    for (MPair<K, V> mpair : *this)
        outs << setw(10) << right << mpair.key << " :    " << mpair.value_list << endl;

    return outs;
}

#endif /* MULTIMAP_H */
