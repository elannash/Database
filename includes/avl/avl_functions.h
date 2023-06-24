#ifndef AVL_FUNCTIONS_H
#define AVL_FUNCTIONS_H

#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

template <typename T>
struct tree_node
{
    tree_node(T item = T(), tree_node *left = nullptr, tree_node *right = nullptr) : _item(item), _left(left), _right(right)
    {
        update_height();
    }

    T _item;
    tree_node<T> *_left;
    tree_node<T> *_right;
    int _height;

    int balance_factor()
    {
        if (_left == nullptr && _right == nullptr) // else if both children are nullptr, the height is zero
            return 0;
        else if (_left != nullptr && _right != nullptr) // if neither children are nullptr, subtract heights to get the balance factor
            return _left->_height - _right->_height;
        else if (_left == nullptr) // else if the left is the only null child, subtract the right height from negative 1
            return -1 - _right->_height;
        else // else right is the only child, subtract -1 from left height (add 1 to left height)
            return _left->_height + 1;
    }

    int height() // calculates the height of the tree
    {
        if (_left == nullptr && _right == nullptr) // if both children are nullptr, the height is zero
            return 0;
        else if (_left != nullptr && _right != nullptr) // else if neither pointers are nullptr, height gets set to one plus the max of the two heights
            return max(_left->_height, _right->_height) + 1;
        else if (_left == nullptr) // else if left is the only null child, height gets set to right's height plus one
            return _right->_height + 1;
        else // else right is the only null child and height gets set to left's height plus one
            return _left->_height + 1;
    }

    int update_height() // not sure why this returns
    {
        _height = height();
        return _height;
    }

    friend ostream &operator<<(ostream &outs, const tree_node<T> &t_node)
    {
        outs << "|" << t_node._item << "|";
    }
};

// template <typename T>
// void tree_insert(tree_node<T> *&root, const T &insert_me);

template <typename T>
bool tree_insert(tree_node<T> *&root, const T &insert_me);

template <typename T>
tree_node<T> *tree_search(tree_node<T> *root, const T &target);

template <typename T>
bool tree_search(tree_node<T> *root, const T &target, tree_node<T> *&found_ptr);

template <typename T>
void tree_print(tree_node<T> *root, int depth = 0, ostream &outs = cout);

template <typename T> // prints detailes info about each node
void tree_print_debug(tree_node<T> *root, int depth = 0, ostream &outs = cout);

template <typename T> // clear the tree
void tree_clear(tree_node<T> *&root);

template <typename T> // erase target from the tree
bool tree_erase(tree_node<T> *&root, const T &target);

template <typename T> // erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T> *&root, T &max_value);

template <typename T> // print in_order
void in_order(tree_node<T> *root, ostream &outs = cout);

template <typename T> // print pre_order
void pre_order(tree_node<T> *root, ostream &outs = cout);

template <typename T> // print post_order
void post_order(tree_node<T> *root, ostream &outs = cout);

template <typename T> // string in_order
string in_order_string(tree_node<T> *root);

template <typename T> // string pre_order
string pre_order_string(tree_node<T> *root);

template <typename T> // string post_order
string post_order_string(tree_node<T> *root);

template <typename T> // return copy of tree pointed to by root
tree_node<T> *tree_copy(tree_node<T> *root);

template <typename T> // Add tree src to dest
void tree_add(tree_node<T> *&dest, const tree_node<T> *src);

template <typename T> // sorted array of ints -> tree
tree_node<T> *tree_from_sorted_list(const T *a);

template <typename T> // sorted array -> tree
tree_node<T> *tree_from_sorted_list(const T *a, int size);

template <typename T>
tree_node<T> *rotate_right(tree_node<T> *&root);

template <typename T>
tree_node<T> *rotate_left(tree_node<T> *&root);

template <typename T>
tree_node<T> *rotate(tree_node<T> *&root); // decide which rotate is needed based on balance factortemplate <typename T>

/************************************************************/

// template <typename T>
// void tree_insert(tree_node<T> *&root, const T &insert_me)
// {
//     if (!root) // if the root IS nullptr
//     {
//         root = new tree_node<T>(insert_me); // allocate space for new tree node and pass in item
//     }
//     else if (insert_me < root->_item) // if the insert_me item is less than root's item, do a recursive call with root's right pointer
//     {
//         tree_insert(root->_left, insert_me);
//     }
//     else // if (insert_me > root->_item) // if the insert_me item is greater than root's item, do a recursive call with root's left pointer
//     {
//         tree_insert(root->_right, insert_me);
//     }

//     root->update_height();
// }

template <typename T>
bool tree_insert(tree_node<T> *&root, const T &insert_me)
{
    if (!root) // if the root IS nullptr
    {
        root = new tree_node<T>(insert_me); // allocate space for new tree node and pass in item
        return true;
    }
    else if (insert_me == root->_item)
    {
        root->_item = insert_me; // overwrite the existing item
        return false;
    }
    else if (insert_me < root->_item) // if the insert_me item is less than root's item, do a recursive call with root's right pointer
    {
        if (tree_insert(root->_left, insert_me))
        {
            root->update_height();
            rotate(root);
            return true;
        }
        else
            return false;
    }
    else // if (insert_me > root->_item) // if the insert_me item is greater than root's item, do a recursive call with root's left pointer
    {
        if (tree_insert(root->_right, insert_me))
        {
            root->update_height();
            rotate(root);
            return true;
        }
        else
            return false;
    }
}

template <typename T>
tree_node<T> *tree_search(tree_node<T> *root, const T &target)
{
    if (!root) // base case, if root IS nullptr, return
    {
        return root;
    }
    else if (root->_item == target) // if the item at root is the target, return the pointer to root
    {
        return root;
    }
    else if (target < root->_item) // if the target is less than the item at root, do recursive call with root's left pointer
    {
        return tree_search(root->_left, target);
    }
    else // if (target > root->_item) // if the target is greater than the item at root, do recursive call with root's right pointer
    {
        return tree_search(root->_right, target);
    }
}

template <typename T>
bool tree_search(tree_node<T> *root, const T &target, tree_node<T> *&found_ptr)
{
    if (!root) // if root IS nullptr
    {
        found_ptr = nullptr; // base case, if root IS nullptr, set found_ptr to nullptr and return false
        return false;
    }
    else if (root->_item == target) // if the item at root is the target, set found_ptr and return true
    {
        found_ptr = root;
        return true;
    }
    else if (target < root->_item) // if the target is less than the item at root, do recursive call with root's left pointer
    {
        return tree_search(root->_left, target, found_ptr);
    }
    else // if (target > root->_item) // if the target is greater than the item at root, do recursive call with root's right pointer
    {
        return tree_search(root->_right, target, found_ptr);
    }
}

template <typename T>
void tree_print(tree_node<T> *root, int depth, ostream &outs)
{
    if (root) // if root is NOT nullptr
    {
        tree_print(root->_right, depth + 1, outs);
        outs << setw(4 * depth) << "[" << root->_item << "]" << endl;
        tree_print(root->_left, depth + 1, outs);
    }
}

template <typename T> // prints details info about each node
void tree_print_debug(tree_node<T> *root, int depth, ostream &outs)
{
    if (root) // if root is NOT nullptr
    {
        tree_print_debug(root->_right, depth + 1, outs);
        outs << setw(4 * depth) << "[" << root->_item << "] H: " << root->_height << " BF: " << root->balance_factor() << endl;
        tree_print_debug(root->_left, depth + 1, outs);
    }
}

template <typename T> // clear the tree
void tree_clear(tree_node<T> *&root)
{
    if (root) // if root is NOT nullptr
    {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = nullptr;
    }
}

template <typename T>                                 // erase target from the tree
bool tree_erase(tree_node<T> *&root, const T &target) // uses code from search, but also updates height on recursive calls
{
    if (!root) // if root IS nullptr
    {
        return false;
    }
    else if (root->_item == target) // if the item at root is the target
    {
        if (!root->_left) // if root's left pointer IS nullptr
        {
            tree_node<T> *hold = root; // hold the node we want to delete

            root = root->_right; // set root to it's right node pointer
            delete hold;         // delete the node we are erasing
            hold = nullptr;
        }
        else // the root's left pointer is NOT nullptr
        {
            // and we want the left child's rightmost node to replace the item in the target node
            T max_value;                             // this gets set in remove_max
            tree_remove_max(root->_left, max_value); // this deletes the left child's rightmost node
            root->_item = max_value;
        }

        if (root) // if root is not nullptr, update height
        {
            root->update_height();
            rotate(root);
        }

        return true;
    }
    else if (target < root->_item) // if the target is less than the item at root, do recursive call with root's left pointer
    {
        if (tree_erase(root->_left, target)) // need this in an if statement in order to update height
        {
            root->update_height();
            rotate(root);
            return true;
        }
        else
            return false;
    }
    else // else the target is greater than the item at root, do recursive call with root's right pointer
    {
        if (tree_erase(root->_right, target)) // need this in an if statement in order to update height
        {
            root->update_height();
            rotate(root);
            return true;
        }
        else
            return false;
    }
}

template <typename T> // erase right-most node from the tree -> max_value
void tree_remove_max(tree_node<T> *&root, T &max_value)
{
    if (!root) // if root IS nullptr just return
    {
        return;
    }
    else if (root->_right) // if root's right pointer is NOT nullptr
    {
        tree_remove_max(root->_right, max_value);
        root->update_height();
        rotate(root);
    }
    else // root's right pointer IS nullptr and we store root's item in max_value and delete the node
    {
        max_value = root->_item; // store the current value of root's item

        if (root->_left) // if root's left node is NOT nullptr, that left node becomes the max and we want to store it's info in the current root (and delete the left node)
        {
            tree_node<T> *hold = root; // set hold pointer to the current root so we can delete it later
            root = root->_left;        // set root to root->_left, so that root's parent is now pointing there

            delete hold; // delete root's original left node
            hold = nullptr;
        }
        else // otherwise root is a leaf node and we can just delete it
        {
            delete root;
            root = nullptr;
        }
    }
}

template <typename T> // print in_order
void in_order(tree_node<T> *root, ostream &outs)
{
    if (root) // if root is NOT nullptr
    {
        in_order(root->_left, outs);
        outs << " " << root->_item << " ";
        in_order(root->_right, outs);
    }
}

template <typename T> // print pre_order
void pre_order(tree_node<T> *root, ostream &outs)
{
    if (root) // if root is NOT nullptr
    {
        outs << " " << root->_item << " ";
        pre_order(root->_left, outs);
        pre_order(root->_right, outs);
    }
}

template <typename T> // print post_order
void post_order(tree_node<T> *root, ostream &outs)
{
    if (root) // if root is NOT nullptr
    {
        post_order(root->_left, outs);
        post_order(root->_right, outs);
        outs << " " << root->_item << " ";
    }
}

template <typename T> // string in_order
string in_order_string(tree_node<T> *root)
{
    string s = "";

    if (root) // if root is NOT nullptr
    {
        s += in_order_string(root->_left);
        s += '[' + to_string(root->_item) + ']';
        s += in_order_string(root->_right);
    }

    return s;
}

template <typename T> // string pre_order
string pre_order_string(tree_node<T> *root)
{
    string s = "";

    if (root) // if root is NOT nullptr
    {
        s += '[' + to_string(root->_item) + ']';
        s += pre_order_string(root->_left);
        s += pre_order_string(root->_right);
    }

    return s;
}

template <typename T> // string post_order
string post_order_string(tree_node<T> *root)
{
    string s = "";

    if (root) // if root is NOT nullptr
    {
        s += post_order_string(root->_left);
        s += post_order_string(root->_right);
        s += '[' + to_string(root->_item) + ']';
    }

    return s;
}

template <typename T> // return copy of tree pointed to by root
tree_node<T> *tree_copy(tree_node<T> *root)
{
    if (root) // if root is NOT nullptr, return a new node, do recursive call inside constructor
    {
        return new tree_node<T>(root->_item,
                                tree_copy(root->_left),   // first recursive call for left node
                                tree_copy(root->_right)); // second recursive call for right node
    }
    else
        return nullptr;
}

template <typename T> // Add tree src to dest
void tree_add(tree_node<T> *&dest, const tree_node<T> *src)
{
    if (src) // if src root is NOT nullptr
    {
        tree_add(dest, src->_left);
        tree_insert(dest, src->_item);
        tree_add(dest, src->_right);
    }
}

template <typename T> // sorted array of ints -> tree
tree_node<T> *tree_from_sorted_list(const T *a)
{
    int size = 0;
    const T *walker = a;

    while (*walker != -1)
    {
        size++;
        walker++;
    }

    return tree_from_sorted_list(a, size);
}

// template <typename T> // sorted array -> tree
// tree_node<T> *tree_from_sorted_list(const T *a, int size)
// {
//     const T *first = a;                 // address of the first  element
//     const T *middle = first + size / 2; // address of the middle element
//     const T *last = first + size - 1;   // address of the last element

//     if (first <= last) // if the first pointer is less than or equal to the last pointer (list is not empty)
//     {
//         // it's a shame this beautiful return statement had to go to waste :'(
//         // return a new tree node and do recursive call in the ctor using the first half and second half of the sorted list
//         return new tree_node<T>(*middle,
//                                 tree_from_sorted_list(first, middle - first),
//                                 tree_from_sorted_list(middle + 1, last - middle));
//     }
//     else
//         return nullptr;
// }

template <typename T> // sorted array -> tree
tree_node<T> *tree_from_sorted_list(const T *a, int size)
{
    assert(size >= 0 && "size was negative");

    const T *start = a;
    const T *end = start + size;

    tree_node<T> *root = nullptr;

    for (const T *walker = start; walker != end; walker++)
    {
        tree_insert(root, *walker);
    }

    return root;
}

template <typename T>
tree_node<T> *rotate_right(tree_node<T> *&root)
{
    assert(root && root->_left && "root or root->_left was nullptr");

    tree_node<T> *hold;

    hold = root->_left;
    root->_left = hold->_right;
    hold->_right = root;
    root->update_height();
    hold->update_height(); // this would only ever be necessary on a right-heavy tree, but keep it here anyway
    root = hold;

    return root;
}

template <typename T>
tree_node<T> *rotate_left(tree_node<T> *&root)
{
    assert(root && root->_right && "root or root->_right was nullptr");

    tree_node<T> *hold;

    hold = root->_right;
    root->_right = hold->_left;
    hold->_left = root;
    root->update_height();
    hold->update_height(); // this would only ever be necessary on a left-heavy tree, but keep it here anyway
    root = hold;

    return root;
}

template <typename T>
tree_node<T> *rotate(tree_node<T> *&root)
{
    assert(root && "root was nullptr");

    if (root->balance_factor() == 2) // the tree is left heavy
    {
        if (root->_left->balance_factor() < 0) // if the subnode is right heavy
            rotate_left(root->_left);

        rotate_right(root);
    }
    else if (root->balance_factor() == -2) // the tree is right heavy
    {
        if (root->_right->balance_factor() > 0) // if the subnode is left heavy
            rotate_right(root->_right);

        rotate_left(root);
    }

    return root;
}

#endif /* AVL_FUNCTIONS_H */
