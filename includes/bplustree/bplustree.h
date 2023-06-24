#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <cassert>

#include "btree_array_funcs.h"

using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator
    {
    public:
        friend class BPlusTree;

        Iterator(BPlusTree<T> *_it = nullptr, int _key_ptr = 0) : it(_it), key_ptr(_key_ptr) {}

        T operator*()
        {
            assert(it && "Pointer should not be nullptr");

            return it->data[key_ptr];
        }

        Iterator operator++(int un_used)
        {
            assert(it && "Pointer should not be nullptr");

            // hold the current iterator
            Iterator hold = *this;

            // increment the index if it will be valid
            if (key_ptr < it->data_count - 1)
                ++key_ptr;
            else
            {
                // increment the pointer and reset key_ptr (the index)
                it = it->next;
                key_ptr = 0;
            }

            // return the iterator we held
            return hold;
        }

        Iterator operator++()
        {
            assert(it);

            // increment the index if it will be valid
            if (key_ptr < it->data_count - 1)
                ++key_ptr;
            else
            {
                // increment the pointer and reset key_ptr (the index)
                it = it->next;
                key_ptr = 0;
            }

            // return this iterator
            return *this;
        }

        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }

        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return !(lhs.it == rhs.it);
        }

        void print_Iterator()
        {
            if (it)
            {
                cout << "iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else
            {
                cout << "iterator: nullptr, key_ptr: " << key_ptr << endl;
            }
        }

        bool is_null() { return !it; }

        void info()
        {
            cout << endl
                 << "Iterator info:" << endl;
            cout << "key_ptr: " << key_ptr << endl;
            cout << "it: " << *it << endl;
        }

    private:
        BPlusTree<T> *it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    // big three:
    BPlusTree(const BPlusTree<T> &other);
    ~BPlusTree();
    BPlusTree<T> &operator=(const BPlusTree<T> &RHS);

    void copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_leaf); // copy other into this object
    void copy_tree(const BPlusTree<T> &other, stack<BPlusTree<T> *> &s);

    void insert(const T &entry); // insert entry into the tree
    void remove(const T &entry); // remove entry from the tree
    void clear_tree();           // clear this object (delete all nodes etc.)

    bool contains(const T &entry) const; // true if entry can be found
    T &get(const T &entry);              // return a reference to entry
    const T &get(const T &entry) const;  // return a const reference to entry
    T &get_existing(const T &entry);     // return a reference to entry
    Iterator find(const T &entry);       // return an iterator to this key.
                                         //      nullptr if not there.
    Iterator lower_bound(const T &key);  // return first that goes NOT BEFORE
                                         //  key entry or next if does not
                                         //  exist: >= entry
    Iterator upper_bound(const T &key);  // return first that goes AFTER key
                                         // exist or not, the next entry  >entry

    int size() const; // count the number of elements

    bool empty() const { return data_count == 0; } // true if the tree is empty

    void print_tree(int level = 0, ostream &outs = cout) const;

    friend ostream &operator<<(ostream &outs, const BPlusTree<T> &print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid() const;
    string in_order() const;
    string pre_order() const;
    string post_order() const;

    Iterator begin();
    Iterator end();

    ostream &list_keys(Iterator from = NULL, Iterator to = NULL)
    {
        if (from == NULL)
            from = begin();
        if (to == NULL)
            to = end();
        for (Iterator it = from; it != to; it++)
            cout << *it << " ";
        return cout;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                               // true if duplicate keys are allowed
    int data_count;                             // number of data elements
    T data[MAXIMUM + 1];                        // holds the keys
    int child_count;                            // number of children
    BPlusTree *subset[MAXIMUM + 2] = {nullptr}; // subtrees
    BPlusTree *next;

    bool is_leaf() const
    {
        return child_count == 0;
    } // true if this is a leaf node

    T *find_ptr(const T &entry); // return a pointer to this key.
                                 //  nullptr if not there.

    // insert element functions
    void loose_insert(const T &entry); // allows MAXIMUM+1 data elements in
                                       //    the root
    void fix_excess(int i);            // fix excess in child i

    // remove element functions:
    void loose_remove(const T &entry); // allows MINIMUM-1 data elements
                                       //   in the root

    void fix_shortage(int i); // fix shortage in child i
    // BPlusTree<T> *fix_shortage(int i);
    //  fix shortage in child i
    //  and return the smallest key in this subtree
    BPlusTree<T> *get_smallest_node();
    void get_smallest(T &entry);   // entry := leftmost leaf
    void get_biggest(T &entry);    // entry := rightmost leaf
    void remove_biggest(T &entry); // remove the biggest child of tree->entry
    void transfer_left(int i);     // transfer one element LEFT from child i
    void transfer_right(int i);    // transfer one element RIGHT from child i

    void merge_with_next_subset(int i); // merges subet[i] with subset[i+1]
};

/**
 * @brief Construct a new BPlusTree<T>::BPlusTree object
 *
 * @tparam T
 * @param dups
 */
template <typename T>
BPlusTree<T>::BPlusTree(bool dups) : dups_ok(dups), data_count(0), child_count(0), next(nullptr) {}

/**
 * @brief Construct a new BPlusTree<T>::BPlusTree object
 *
 * @tparam T
 * @param a
 * @param size
 * @param dups
 */
template <typename T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups) : dups_ok(dups), data_count(0), child_count(0), next(nullptr)
{
    assert(size >= 0 && "Array size should be greater than or equal to zero");

    T *walker;
    T *end = a + size;

    for (walker = a; walker != end; walker++)
        insert(*walker);
}

/**
 * @brief Construct a new BPlusTree<T>::BPlusTree object from another BPlusTree<T>::BPlusTree object
 *
 * @tparam T
 * @param other
 */
template <typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other) : dups_ok(other.dups_ok), data_count(0), child_count(0), next(nullptr)
{
    BPlusTree<T> *last_leaf = nullptr;
    copy_tree(other, last_leaf);
}

/**
 * @brief Destroy the BPlusTree<T>::BPlusTree object
 *
 * @tparam T
 */
template <typename T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}

/**
 * @brief Assign one BPlusTree<T>::BPlusTree object to another
 *
 * @tparam T
 * @param RHS
 * @return BPlusTree<T>&
 */
template <typename T>
BPlusTree<T> &BPlusTree<T>::operator=(const BPlusTree<T> &RHS)
{
    if (this == &RHS)
        return *this;
    else
    {
        clear_tree();
        BPlusTree<T> *last_leaf = nullptr;
        copy_tree(RHS, last_leaf);
    }

    return *this;
}

/**
 * @brief Copies the values of one tree into another.
 *
 * @tparam T
 * @param other
 */
template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_leaf)
{
    assert(empty() && "Tree should be empty before copying");

    // copy the data from other.data[] into this->data[]
    // set this->child_count to other.child_count
    // loop through other->subset[] array and allocate a new node in this for each child in the other array
    // do a recursive call to copy tree using this->subset[i]->copy_tree(*(other.subset[i]))

    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;
    dups_ok = other.dups_ok;

    for (int i = 0; i < child_count; i++)
    {
        subset[i] = new BPlusTree<T>(other.dups_ok);
        subset[i]->copy_tree(*(other.subset[i]), last_leaf);

        // if subset[i] is a leaf, and last_leaf is nullptr, set last_leaf to subset[i]
        // otherwise, (still if subset[i] is a leaf), set last_leaf->next to subset[i] and then set last_leaf to last_leaf->next (subset[i])
        if (subset[i]->is_leaf() && !last_leaf)
            last_leaf = subset[i];
        else if (subset[i]->is_leaf())
        {
            last_leaf->next = subset[i];
            last_leaf = last_leaf->next;
        }
    }
}

/**
 * @brief Copies the values of one tree into another.
 *
 * @tparam T
 * @param other
 */
template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, stack<BPlusTree<T> *> &s)
{
    //?
}

/**
 * @brief Inserts an item into the tree.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::insert(const T &entry)
{
    // let loose_insert do most of the inserting work
    // if the root is in excess after calling loose_insert, create a new node and shallow copy the root's contents into it
    // clear out the current root and make it's only child (subset[0]) the new root we just created
    // call fix_excess(0) on the current root

    loose_insert(entry);

    // *** NOTE ***
    // ideally, this should leave the root node with however many elements MINIMUM is
    // but this currently only works for MINIMUM = 1 and i'm too lazy to change it (and its not that important for now)
    if (data_count == MAXIMUM + 1)
    {
        // create a new node
        BPlusTree<T> *new_node = new BPlusTree<T>(dups_ok);

        // shallow copy here
        copy_array(new_node->data, data, new_node->data_count, data_count);
        copy_array(new_node->subset, subset, new_node->child_count, child_count);

        // clear out the root node (set member variables to appropriate amounts)
        data_count = 0;
        child_count = 1;

        // set the roots subset[0] to point at the new node we just created
        subset[0] = new_node;

        // call fix excess on the new node we created, and now we have a new root!
        fix_excess(0);
    }
}

/**
 * @brief Removes an entry from the tree if found.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::remove(const T &entry)
{
    // let loose remove do most of the removing work
    loose_remove(entry);

    // if the root is in shortage after loose_remove, loop through the children and merge their data & children with the root, deleting them as we go
    if (data_count == MINIMUM - 1 && child_count == MINIMUM)
    {
        for (int i = data_count; i >= 0; i--)
        {
            BPlusTree<T> *delete_this_child;
            delete_item(subset, i, child_count, delete_this_child); // first remove the child from the subset array and store it in pointer

            // merge the data from child with the current roots data
            // prepend the child's children to the beginning of subset array (this is fine since we are accessing children from last to first)
            // these also set childs data_count and child_count to zero
            insert_array(data, data_count, delete_this_child->data, delete_this_child->data_count, i);
            prepend_array(subset, child_count, delete_this_child->subset, delete_this_child->child_count);

            // lastly release the child from memory
            delete delete_this_child;
        }
    }
}

/**
 * @brief Clears all subnodes of the root.
 *
 * @tparam T
 */
template <typename T>
void BPlusTree<T>::clear_tree()
{
    // if the current node is not a leaf, call clear_tree() on all of the subnodes and then delete each one
    // set child_count and data_count to 0

    for (int i = 0; i < child_count; i++)
    {
        subset[i]->clear_tree();
        delete subset[i];
    }

    data_count = 0;
    child_count = 0;
}

/**
 * @brief Returns true if entry is in the btree, false if entry is not found in the btree.
 *
 * @tparam T
 * @param entry
 * @return true
 * @return false
 */
template <typename T>
bool BPlusTree<T>::contains(const T &entry) const
{
    // declare a local index, and set it to the index of the first item in data_count that is greater than or equal to entry
    // if not item in data[] is greater than or equal to index, then index is set to data_count inside of first_ge() to indicate that all values in the array are smaller than entry
    // the first condition of the first if statement checks if (index < data_count). if this condition is not true, then the node will either be a leaf and we return false, or we do a recursive call on subset[index]
    // the second condition of the first if statement checks if !(entry < data[index]). if entry is not less than data[index], since we already know entry is already greater than or equal to data[index], we can conclude that entry is equal to data[index]

    int index;

    index = first_ge(data, data_count, entry);

    if ((index < data_count) && !(entry < data[index])) // if both conditions hold, then data[index] == entry
        return true;
    else if (is_leaf()) // if the node is a leaf, we can conclude the item is not in the list
        return false;
    else // recursively search on the child node
        return subset[index]->contains(entry);
}

/**
 * @brief Returns the reference to an entry in the tree. If the entry was not in the tree, it will be inserted and the reference to the new entry will be returned.
 *
 * @tparam T
 * @param entry
 * @return T&
 */
template <typename T>
T &BPlusTree<T>::get(const T &entry)
{
    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

/**
 * @brief Returns a const reference to an entry in the tree.
 *
 * @tparam T
 * @param entry
 * @return T&
 */
template <typename T>
const T &BPlusTree<T>::get(const T &entry) const
{
    // essentially the find function

    int index;
    bool found;

    index = first_ge(data, data_count, entry);
    found = ((index < data_count) && !(entry < data[index])); // if both conditions hold, then data[index] == entry

    if (found)
    {
        if (is_leaf()) // if we found the key, and the current node is a leaf, return reference to data item
            return data[index];
        else // otherwise this is not a leaf so we do recursive search
            return subset[index + 1]->get_existing(entry);
    }
    else if (is_leaf()) // otherwise the node is a leaf and not found, so we assert
    {
        assert(found && "Entry was not in the list when calling get");
        return data[0]; // THIS BLOCK SHOULD NOT RETURN ANYTHING, THIS RETURN STATEMENT IS ONLY HERE TO STOP COMPILER WARNINGS AND WILL NEVER EXECUTE BECAUSE OF ASSERT STATEMENT
    }
    else // otherwise the node is not a leaf and we do a recursive serach
        return subset[index]->get_existing(entry);
}

/**
 * @brief Returns a reference to an existing entry in the tree.
 *
 * @tparam T
 * @param entry
 * @return T&
 */
template <typename T>
T &BPlusTree<T>::get_existing(const T &entry)
{
    // essentially the find function

    int index;
    bool found;

    index = first_ge(data, data_count, entry);
    found = ((index < data_count) && !(entry < data[index])); // if both conditions hold, then data[index] == entry

    if (found)
    {
        if (is_leaf()) // if we found the key, and the current node is a leaf, return reference to data item
            return data[index];
        else // otherwise this is not a leaf so we do recursive search
            return subset[index + 1]->get_existing(entry);
    }
    else if (is_leaf()) // otherwise the node is a leaf and not found, so we assert
    {
        assert(found && "Entry was not in the list when calling get_existing().");
        return data[0]; // THIS BLOCK SHOULD NOT RETURN ANYTHING, THIS RETURN STATEMENT IS ONLY HERE TO STOP COMPILER WARNINGS AND WILL NEVER EXECUTE BECAUSE OF ASSERT STATEMENT
    }
    else // otherwise the node is not a leaf and we do a recursive serach
        return subset[index]->get_existing(entry);
}

/**
 * @brief Returns an Iterator to an entry, null Iterator if entry was not found.
 *
 * @tparam T
 * @param entry
 * @return T*
 */
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &entry)
{
    // declare index and found variables
    // set index to the first index greater or equal to entry in the data array
    // set found to represent whether or not entry was found in data array
    // if the entry was found in the data array, if the current node is a leaf, return iterator to the entry. if the current node is not a leaf do a recursive call on subset[i+1]
    // if the current node is a leaf but the entry was not found, return a NULL iterator
    // otherwise if the current node is not a leaf but the entry was not found, do a recursive call on subset[i]

    int index;
    bool found;

    index = first_ge(data, data_count, entry);
    found = (index < data_count) && !(entry < data[index]);

    if (found) // entry was found
    {
        if (is_leaf()) // current node a leaf so we just return iterator to index in data
            return Iterator(this, index);
        else // current node is not a leaf so we do a recursive search on right child
            return subset[index + 1]->find(entry);
    }
    else if (is_leaf()) // found was false and the current node is a leaf, entry was not in the tree and we return null iterator
        return Iterator(nullptr, 0);
    else // found was false but current node is not a leaf, do a recursive search on left child
        return subset[index]->find(entry);
}

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T &key)
{
    // first greater than or equal to
    // essentially the find function

    int index;
    bool found;

    index = first_ge(data, data_count, key);
    found = (index < data_count) && !(key < data[index]);

    if (found) // key was found
    {
        if (is_leaf()) // current node a leaf so we just return iterator to index in data
            return Iterator(this, index);
        else // current node is not a leaf so we do a recursive search on right child
            return subset[index + 1]->lower_bound(key);
    }
    else if (is_leaf()) // found was false and the current node is a leaf, key was not in the tree and we return null iterator
    {
        if (index < data_count) // return iterator to the first data item that was greater than key
            return Iterator(this, index);
        else // return iterator to whatever next points to
            return Iterator(next, 0);
    }
    else // found was false but current node is not a leaf, do a recursive search on left child
        return subset[index]->lower_bound(key);
}

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T &key)
{
    // first greater than
    // essentially the find function

    int index;
    bool found;

    index = first_ge(data, data_count, key);
    found = (index < data_count) && !(key < data[index]);

    if (found) // key was found
    {
        if (is_leaf()) // current node a leaf so we declare iterator to the key and increment it
            return ++Iterator(this, index);
        else // current node is not a leaf so we do a recursive search on right child
            return subset[index + 1]->upper_bound(key);
    }
    else if (is_leaf()) // found was false and the current node is a leaf, key was not in the tree and we return null iterator
    {
        if (index < data_count) // return iterator to the first data item that was greater than key
            return Iterator(this, index);
        else // return iterator to whatever next points to
            return Iterator(next, 0);
    }
    else // found was false but current node is not a leaf, do a recursive search on left child
        return subset[index]->upper_bound(key);
}

/**
 * @brief Returns the total data count of the tree.
 *
 * @tparam T
 * @return int
 */
template <typename T>
int BPlusTree<T>::size() const
{
    // in_order traversal and just add to count
    int size = data_count;

    for (int i = 0; i < child_count; i++)
        size += subset[i]->size();

    return size;
}

/**
 * @brief Prints the tree structure with all data entries and links between leaves.
 *
 * @tparam T
 * @param level The level of recursion
 * @param outs
 */
template <typename T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    const bool debug = false;

    // if the current node is not a leaf, then call print on it's rightmost child first
    if (!is_leaf())
        subset[child_count - 1]->print_tree(level + 1, outs);

    // in a loop, print the current node's data
    // and call print on the remaining children (moving right to left in the array)
    for (int i = data_count - 1; i >= 0; i--)
    {
        if (i == data_count - 1)
        {
            // if the current node is  a leaf and the next ptr is not nullptr
            if (is_leaf() && next)
                outs << setw(5 * level + 3) << "↑" << endl;

            outs << setw(5 * level + 3) << "⎴" << endl;
        }

        // using to_string length in setw to align everything
        outs << setw(5 * level + to_string(data[i]).length()) << data[i];

        //// debug stuff
        if (debug && i == data_count / 2) // only print debug info for the middle data item
            outs << " - DC: [" << data_count << "] "
                 << " CC: [" << child_count << "]";

        outs << endl;
        ////

        if (i == 0)
            outs << setw(5 * level + 3) << "⎵" << endl;

        if (!is_leaf())
            subset[i]->print_tree(level + 1, outs);
    }
}

/**
 * @brief Checks the validity of a btree. Will return true if the tree is a btree, false otherwise.
 *
 * @tparam T
 * @return true
 * @return false
 */
template <typename T>
bool BPlusTree<T>::is_valid() const
{
    // if the node is a leaf, check that the links are valid
    if (is_leaf())
    {
        if (next && next->data[0] < data[data_count - 1])
            return false;
        else
            return true;
    }

    if (!subset[child_count - 1]->is_valid()) // check last child first (makes contents of loop easier)
        return false;

    // not a leaf so we loop through the data & children
    for (int i = 0; i < data_count; i++)
    {
        // do a recursive call on all of the children nodes
        if (!subset[i]->is_valid())
            return false;

        // if the data item at data[i] is not the same as the smallest data item of right child subtree, the tree will be invalid
        if (data[i] != subset[i + 1]->get_smallest_node()->data[0])
            return false;

        // if the item at data[i] is greater than the item at data[i+1], the tree will be invalid
        // check that i+1 is a valid index first
        // this is bad code
        if (i < data_count - 1)
            if (data[i] > data[i + 1])
                return false;

        // if the item at data[i] is greater than any of the data at subset[i+1]->data[j], the tree will be invalid
        for (int j = 0; j < subset[i + 1]->data_count; j++)
        {
            if (data[i] > subset[i + 1]->data[j])
                return false;
        }

        // if the item at data[i] is less than any of the data at subset[i]->data[j], the tree will be invalid
        for (int j = 0; j < subset[i]->data_count; j++)
        {
            if (data[i] < subset[i]->data[j])
                return false;
        }
    }

    return true;
}

/**
 * @brief Returns an in order traversal string of the tree's data entries.
 *
 * @tparam T
 * @return string
 */
template <typename T>
string BPlusTree<T>::in_order() const
{
    // (1) start with an empty string
    // (2) if the current node is not a leaf, add the return value from subset[0]->in_order()
    // (3) in a loop, add data[i] to the string
    // (4) after adding data[i] to string, do recursive call on subset[i+1]

    string str = ""; // (1)

    if (!is_leaf())
        str += subset[0]->in_order(); // (2)

    for (int i = 0; i < data_count; i++) // (3)
    {
        str += to_string(data[i]) + "|";

        if (!is_leaf()) // (4)
            str += subset[i + 1]->in_order();
    }

    return str;
}

/**
 * @brief Returns a pre order traversal string of the tree's data entries.
 *
 * @tparam T
 * @return string
 */
template <typename T>
string BPlusTree<T>::pre_order() const
{
    // (1) start with empty string
    // (2) loop through data array adding data[i] to string
    // (3) if current node is not a leaf, add subset[i]->pre_order() return value to string
    // (4) outside of the loop, add the return value of the last child to the string

    string str = ""; // (1)

    for (int i = 0; i < data_count; i++) // (2)
    {
        str += to_string(data[i]) + "|";

        if (!is_leaf()) // (3)
            str += subset[i]->pre_order();
    }

    if (!is_leaf())
        str += subset[child_count - 1]->pre_order(); // (4)

    return str;
}

/**
 * @brief Returns a post order traversal string of the tree's data entries.
 *
 * @tparam T
 * @return string
 */
template <typename T>
string BPlusTree<T>::post_order() const
{
    // (1) start with an empty string
    // (2) if the current node is not a leaf, add the resulting string from a recursive call on subset[0]
    // (3) in a loop, if the current node is not a leaf. add return value from subset[i+1]->post_order()
    // (4) add the value at data[i] to the string

    string str = ""; // (1)

    if (!is_leaf())
        str += subset[0]->post_order(); // (2)

    for (int i = 0; i < data_count; i++) // (3)
    {
        if (!is_leaf()) // (4)
            str += subset[i + 1]->post_order();

        str += to_string(data[i]) + "|";
    }

    return str;
}

/**
 * @brief Returns an Iterator to the leftmost node of the tree
 *
 * @tparam T
 * @return BPlusTree<T>::Iterator
 */
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    if (!is_leaf()) // if the current node isn't a leaf, call begin() on the leftmost child
        return subset[0]->begin();
    else // otherwise the current node is a leaf and we return an iterator to the current node
        return Iterator(this);
}

/**
 * @brief Returns an Iterator to nullptr.
 *
 * @tparam T
 * @return BPlusTree<T>::Iterator
 */
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(nullptr, 0); // return a null iterator
}

/**
 * @brief Returns an pointer to the entry, nullptr if entry was not found.
 *
 * @tparam T
 * @param entry
 * @return T*
 */
template <typename T>
T *BPlusTree<T>::find_ptr(const T &entry)
{
    // declare a local index, and set it to the index of the first item in data_count that is greater than or equal to entry
    // if not item in data[] is greater than or equal to index, then index is set to data_count inside of first_ge() to indicate that all values in the array are smaller than entry
    // the first condition of the first if statement checks if (index < data_count). if this condition is not true, then the node will either be a leaf and we return nullptr, or we do a recursive call on subset[index]
    // the second condition of the first if statement checks if !(entry < data[index]). if entry is not less than data[index], since we already know entry is already greater than or equal to data[index], we can conclude that entry is equal to data[index]

    int index;
    bool found;

    index = first_ge(data, data_count, entry);
    found = (index < data_count) && !(entry < data[index]);

    if (found) // if both conditions hold, then data[index] == entry
        return &data[index];
    else if (is_leaf()) // if the node is a leaf, we can conclude the item is not in the list
        return nullptr;
    else // recursively search on the child node
        return subset[index]->find_ptr(entry);
}

/**
 * @brief Inserts an entry from the tree. Tree will be valid after inserting with the exeption that the root may contain one more than MAXIMUM entries.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::loose_insert(const T &entry)
{
    int index;
    bool found;

    index = first_ge(data, data_count, entry);
    found = (index < data_count) && !(entry < data[index]);

    if (found && !dups_ok) // if first two conditions hold, then data[index] == entry
        return;
    else if (found) // && dups_ok
    {
        if (is_leaf())
            data[index] = data[index] + entry;
        else
            subset[index + 1]->loose_insert(entry);
    }
    else // !found, do a recursive call on the subset
    {
        if (is_leaf())
            insert_item(data, index, data_count, entry);
        else
        {
            subset[index]->loose_insert(entry);

            if (subset[index]->data_count > MAXIMUM) // if the child node is in excess, call fix_excess on it
                fix_excess(index);
        }
    }
}

/**
 * @brief Fixes a child that is in excess at position i in the subset. Root node may be in excess after calling.
 *
 * @tparam T
 * @param i Index
 */
template <typename T>
void BPlusTree<T>::fix_excess(int i)
{
    // create node and insert pointer to a new btree at subset[i+1] (one past the node we are trying to fix excess as)
    // split the data[] array at subset[i], and move half of it over to the data[] array at subset[i+1] (this will leave the one entry we want to move to the parent at the end of subset[i]'s data array)
    // split the children nodes at subset[i], and move half of them over to subset[i+1]
    // create an item to store the entry we want to move to the parent
    // since the entry that was at the middle of subset[i]'s data[] array is now at the end of the array after splitting, call detach and store the detached item
    // do an ordered insert into the parent's data[] array using the detached item

    insert_item(subset, i + 1, child_count, new BPlusTree<T>(dups_ok));
    split(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
    split(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);

    T move_to_parent;
    detach_item(subset[i]->data, subset[i]->data_count, move_to_parent);
    insert_item(data, i, data_count, move_to_parent);

    // if subset[i+1] is a leaf, insert the middle value (which was moved to parent) to the beginning of subset[i+1]->data
    // connect the links for leaf nodes
    if (subset[i + 1]->is_leaf())
    {
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, move_to_parent);

        subset[i + 1]->next = subset[i]->next;
        subset[i]->next = subset[i + 1];
    }
}

/**
 * @brief Removes an entry from the tree if found. Tree will be valid after removing with the exeption that the root may contain one less than MINIMUM entries.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::loose_remove(const T &entry)
{
    int index;
    bool found;

    index = first_ge(data, data_count, entry);
    found = (index < data_count) && !(entry < data[index]);

    if (is_leaf() && !found) // node is a leaf and entry was not found
        return;
    else if (is_leaf() && found) // node is a leaf and entry was found
    {
        T temp; // passed into delete_item and will hold the value of entry after, not used in any meaniningful way
        delete_item(data, index, data_count, temp);
    }
    else if (!is_leaf() && !found) // node is not a leaf and the entry was not found in data[]
    {
        subset[index]->loose_remove(entry);

        if (subset[index]->data_count < MINIMUM)
            fix_shortage(index); // fix_shortage() will check if subset[index] is actually in shortage
    }
    else // node is not a leaf and the entry was found
    {
        subset[index + 1]->loose_remove(entry);

        if (subset[index + 1]->data_count < MINIMUM) // if child is in shortage after removing, call fix_shortage on it
            fix_shortage(index + 1);

        // rationale for if statement
        // 4 scenarios after fixing shortage in child
        // (1) the child was a leaf and transferred a data element to it's sibling, and already replaced data[index]
        // (2) the child was not a leaf and transferred a data element to it's sibling, and already replaced data[index]
        // (3) the child was a leaf and merged with its sibling, child was a leaf and deleted the entry at data[index]
        // (4) the child was not a leaf and merged with it's sibling, breadcrumb was sent down to child
        // checking index+1 < child_count ensures that the child and data indices are valid
        // checking that data[index] == entry ensures that we are not replacing a data element that was already replaced by the transfer functions OR already deleted by the merge_with_next_subset functions when fix_shortage was previously called
        // in case that breadcrumb was sent to child, we call subset[index]->get_smallest() and replace the data item at the end of child's data array

        if (index + 1 < child_count && data[index] == entry)                                // need to ensure that subset[index+1] is still a valid child after fix_shortage before calling get_smallest on it
            subset[index + 1]->get_smallest(data[index]);                                   // data[index] is passed into get_smallest() and the smallest entry of the subtree is stored in it
        else if (subset[index]->data[subset[index]->data_count - 1] == entry)               // otherwise breadcrumb was transferred to the end of child data during merge
            subset[index]->get_biggest(subset[index]->data[subset[index]->data_count - 1]); // so we replace it there
    }
}

/**
 * @brief Fixes shortage in child at subset[i]. Root node may be in shortage after calling.
 *
 * @tparam T
 * @param i Index
 */
template <typename T>
void BPlusTree<T>::fix_shortage(int i)
{
    assert(data_count > 0 && "data_count should be greater than zero when calling fix_shortage");

    if (i > 0 && subset[i - 1]->data_count > MINIMUM) // if subset[i-1] is a valid index, borrow an entry from it
        transfer_right(i - 1);
    else if (i < data_count && subset[i + 1]->data_count > MINIMUM) // if subset[i+1] is a valid index, borrow an entry from it
        transfer_left(i + 1);
    else if (i > 0 && subset[i - 1]->data_count == MINIMUM) // and subset[i-1]->data_count == MINIMUM
        merge_with_next_subset(i - 1);
    else if (i < data_count && subset[i + 1]->data_count == MINIMUM) // i < data_count and subset[i+1]->data_count == MINIMUM
        merge_with_next_subset(i);
}

/**
 * @brief Returns a pointer to the leftmost node of the current tree.
 *
 * @tparam T
 * @return BPlusTree<T>*
 */
template <typename T>
BPlusTree<T> *BPlusTree<T>::get_smallest_node()
{
    assert(data_count > 0 && "data_count should be greater than zero when calling get_smallest_node");

    if (is_leaf()) // then this is the leftmost leaf
        return this;
    else // this node is not a leaf and we do a recursive call
        return subset[0]->get_smallest_node();
}

/**
 * @brief Stores the smallest data item of the current node's tree in entry.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::get_smallest(T &entry)
{
    entry = get_smallest_node()->data[0];
}

/**
 * @brief Stores the smallest item data item from the rightmost tree in entry.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::get_biggest(T &entry)
{
    if (is_leaf()) // store the data item in entry
        entry = data[0];
    else // this node is not a leaf and we do a recursive call
        subset[child_count - 1]->get_biggest(entry);
}

/**
 * @brief Removes the largest data item of the current node's tree and stores it in entry.
 *
 * @tparam T
 * @param entry
 */
template <typename T>
void BPlusTree<T>::remove_biggest(T &entry)
{
    assert(data_count > 0 && "data_count should be greater than zero when calling remove_biggest");

    // remove_biggest() is called with data[index] as the argument

    if (is_leaf())
        detach_item(data, data_count, entry);
    else // this node is not a leaf and we do a recursive call
    {
        subset[child_count - 1]->remove_biggest(entry);

        if (subset[child_count - 1]->data_count < MINIMUM)
            fix_shortage(child_count - 1);
    }
}

/**
 * @brief Data entry transfer from subset[i+1] to subset[i]. Called when subset[i+1] is a valid index. If subset[i+1] is not a leaf, the appropriate child is also transferred.
 *
 * @tparam T
 * @param i
 */
template <typename T>
void BPlusTree<T>::transfer_right(int i)
{
    if (subset[i]->is_leaf())
    {
        T move_to_sibling;

        detach_item(subset[i]->data, subset[i]->data_count, move_to_sibling);
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, move_to_sibling);
        subset[i + 1]->get_smallest(data[i]); // replace data[i] with subset[i+1]->data[0]
    }
    else
    {
        T move_to_child;
        T move_to_parent;
        BPlusTree<T> *move_to_sibling;

        // move the item at data[i] to subset[i+1]->data
        delete_item(data, i, data_count, move_to_child);
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, move_to_child); // insert to the front of subset[i]->data_count

        // move item at end of subset[i]->data to data[i]
        detach_item(subset[i]->data, subset[i]->data_count, move_to_parent);
        insert_item(data, i, data_count, move_to_parent);

        // we already know all the subset nodes are not leaves, so transfer the appropriate children to sibling
        detach_item(subset[i]->subset, subset[i]->child_count, move_to_sibling);
        insert_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, move_to_sibling);
    }
}

/**
 * @brief Data entry transfer from subset[i-1] to subset[i]. Called when subset[i-1] is a valid index. If subset[i-1] is not a leaf, the appropriate child is also transferred.
 *
 * @tparam T
 * @param i Index
 */
template <typename T>
void BPlusTree<T>::transfer_left(int i)
{
    if (subset[i]->is_leaf())
    {
        T move_to_sibling;

        delete_item(subset[i]->data, 0, subset[i]->data_count, move_to_sibling);
        attach_item(subset[i - 1]->data, subset[i - 1]->data_count, move_to_sibling);
        subset[i]->get_smallest(data[i - 1]); // replace data[i-1] with subset[i]->data[0]
    }
    else
    {
        T move_to_child;
        T move_to_parent;
        BPlusTree<T> *move_to_sibling;

        // move the item at data[i-1] to end of subset[i-1]->data
        delete_item(data, i - 1, data_count, move_to_child);
        attach_item(subset[i - 1]->data, subset[i - 1]->data_count, move_to_child);

        // move item at subset[i]->data[0] to data[i-1]
        delete_item(subset[i]->data, 0, subset[i]->data_count, move_to_parent);
        insert_item(data, i - 1, data_count, move_to_parent);

        // we already know all the subset nodes are not leaves, so transfer the appropriate children to sibling
        delete_item(subset[i]->subset, 0, subset[i]->child_count, move_to_sibling);
        attach_item(subset[i - 1]->subset, subset[i - 1]->child_count, move_to_sibling);
    }
}

/**
 * @brief Merges child subset[i] with child subset[i+1]. The item a data[i] will be deleted during operation.
 *
 * @param i
 */
template <typename T>
void BPlusTree<T>::merge_with_next_subset(int i)
{
    if (subset[i]->is_leaf()) // if leaf, simply delete data[i] and then append [i+1]->data to [i]->data
    {
        T delete_me; // item that is getting thrown away

        delete_item(data, i, data_count, delete_me);
        append_array(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
    }
    else
    {
        T move_to_child;

        // transfer a data item to child since we will be removing a child
        delete_item(data, i, data_count, move_to_child);
        attach_item(subset[i]->data, subset[i]->data_count, move_to_child);

        // append subset[i+1] to subset[i]
        append_array(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
        append_array(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);
    }

    BPlusTree<T> *delete_this_child; // pointer to the child that will be deleted

    delete_item(subset, i + 1, child_count, delete_this_child);
    subset[i]->next = delete_this_child->next; // same as subset[i]->next = subset[i+1]->next;
    delete delete_this_child;                  // release the memory for the child we removed
}

#endif /* B_PLUS_TREE_H */