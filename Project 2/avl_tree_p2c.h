#pragma once

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
class AvlTree
{
public:
    /// @brief Default Constructo, sets the root to nullptr.
    AvlTree() : root{ nullptr } { }

    /// @brief Copy constructor.
    /// @param rhs The tree to deep copy from.
    AvlTree(const AvlTree& rhs) : root{ nullptr }
    {
        root = clone(rhs.root);
    }

    /// @brief Move constructor.
    /// @param rhs The tree to move from.
    AvlTree(AvlTree&& rhs) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    ~AvlTree() { makeEmpty(); }

    /// @brief Copy assignment operator overload.
    /// @param rhs The AvlTree to copy.
    /// @return Sets the current instance to a deep copy of another AvlTree class instance.
    AvlTree& operator=(const AvlTree& rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /// @brief Move assignment operator overload.
    /// @param rhs The AvlTree to move.
    /// @return Sets the current instance to a reference of another AvlTree class instance.
    AvlTree& operator=(AvlTree&& rhs)
    {
        std::swap(root, rhs.root);

        return *this;
    }

    /// @brief Count the number of nodes in the tree.
    /// @return The number of nodes in the tree.
    int count() const
    {
        return count(root);
    }

    /// @brief The average depth to find a node in the tree.
    /// @return The average depth of traversal.
    double avgDepth() const
    {
        return avgDepth(root, 0) / count(root);
    }

    /// @brief Find a node in the tree.
    /// @param x The node to find.
    /// @return A constant reference to the node.
    const Comparable* find(const Comparable& x) const
    {
        AvlNode* target = find(x, root);

        if (target == nullptr)
            return nullptr;

        return &target->element;
    }

    /// @brief Find a node in the tree.
    /// @param x The rvalue node to find.
    /// @return A constant reference to the node.
    const Comparable* find(Comparable&& x) const
    {
        AvlNode* target = find(std::move(x), root);

        if (target == nullptr)
            return nullptr;

        return &target->element;
    }

    /// @brief Counts the amount of recursive calls to find a node in the tree.
    /// @param x The node to find.
    /// @return The amount of recursive calls.
    int findRecursionCount(const Comparable& x) const
    {
        return findRecursionCount(x, root);
    }

    /// @brief Counts the amount of recursive calls to find a node in the tree.
    /// @param x The rvalue node to find.
    /// @return The amount of recursive calls.
    int findRecursionCount(Comparable&& x) const
    {
        return findRecursionCount(std::move(x), root);
    }

    /// @brief Find the smallest node in the tree.
    /// @return A constant reference to the smallest node.
    /// @exception UnderflowException If the tree is empty.
    const Comparable& findMin() const
    {
        if (isEmpty())
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /// @brief Find the largest node in the tree.
    /// @return A constant reference to the largest node.
    /// @exception UnderflowException If the tree is empty.
    const Comparable& findMax() const
    {
        if (isEmpty())
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /// @brief Checks to see if the given node is in the tree.
    /// @param x The node to check.
    /// @return True if the node is in the tree, false otherwise.
    bool contains(const Comparable& x) const
    {
        return contains(x, root);
    }

    /// @brief Checks to see if the tree is empty.
    /// @return True if the tree is empty, false otherwise.
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /// @brief Print the tree in order.
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    /// @brief Make the tree logically empty.
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /// @brief Inserts a node into the tree.
    /// @param x The node to insert.
    void insert(const Comparable& x)
    {
        insert(x, root);
    }

    /// @brief Inserts a rvalue node into the tree.
    /// @param x The rvalue node to insert.
    void insert(Comparable&& x)
    {
        insert(std::move(x), root);
    }

    /// @brief Removes a node from the tree.
    /// @param x The node to remove.
    void remove(const Comparable& x)
    {
        remove(x, root);
    }

    /// @brief Counts the amount of recursive calls to remove a node from the tree.
    /// @param x The node to remove.
    /// @return The amount of recursive calls.
    int removeRecursionCount(const Comparable& x) const
    {
        return removeRecursionCount(x, root);
    }

private:
    struct AvlNode
    {
        Comparable element;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(const Comparable& ele, AvlNode* lt, AvlNode* rt, int h = 0)
            : element{ ele }, left{ lt }, right{ rt }, height{ h }
        { }

        AvlNode(Comparable&& ele, AvlNode* lt, AvlNode* rt, int h = 0)
            : element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h }
        { }
    };

    static const int ALLOWED_IMBALANCE = 1;
    AvlNode* root;

    int count(AvlNode* t) const
    {
        if (t == nullptr)
            return 0;

        return 1 + count(t->left) + count(t->right);
    }

    double avgDepth(AvlNode* t, int depth) const
    {
        if (t == nullptr)
            return 0;

        return depth + avgDepth(t->left, depth + 1) + avgDepth(t->right, depth + 1);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable& x, AvlNode*& t)
    {
        if (t == nullptr)
            t = new AvlNode{ x, nullptr, nullptr };
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            t->element.Merge(x);

        balance(t);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable&& x, AvlNode*& t)
    {
        if (t == nullptr)
            t = new AvlNode{ std::move(x), nullptr, nullptr };
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
            t->element.Merge(std::move(x));

        balance(t);
    }

    AvlNode* find(const Comparable& x, AvlNode* t) const
    {
        if (t == nullptr)
            return nullptr;
        else if (x < t->element)
            return find(x, t->left);
        else if (x > t->element)
            return find(x, t->right);
        else
            return t;
    }

    AvlNode* find(Comparable&& x, AvlNode* t) const
    {
        if (t == nullptr)
            return nullptr;
        else if (x < t->element)
            return find(std::move(x), t->left);
        else if (x > t->element)
            return find(std::move(x), t->right);
        else
            return t;
    }

    int findRecursionCount(const Comparable& x, AvlNode* t) const
    {
        if (t == nullptr)
            return 0;
        else if (x < t->element)
            return 1 + findRecursionCount(x, t->left);
        else if (x > t->element)
            return 1 + findRecursionCount(x, t->right);

        return 0;
    }

    int findRecursionCount(Comparable&& x, AvlNode* t) const
    {
        if (t == nullptr)
            return 0;
        else if (x < t->element)
            return 1 + findRecursionCount(std::move(x), t->left);
        else if (x > t->element)
            return 1 + findRecursionCount(std::move(x), t->right);

        return 0;
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable& x, AvlNode*& t)
    {
        if (t == nullptr)
            return;   // Item not found; do nothing

        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    int removeRecursionCount(const Comparable& x, AvlNode* t) const
    {
        if (t == nullptr)
            return 0;
        else if (x < t->element)
            return 1 + removeRecursionCount(x, t->left);
        else if (x > t->element)
            return 1 + removeRecursionCount(x, t->right);
        else if (t->left != nullptr && t->right != nullptr)
            return 2 + findMinRecursionCount(t->right) + removeRecursionCount(findMin(t->right)->element, t->right);

        return 0;
    }

    // Assume t is balanced or within one of being balanced
    void balance(AvlNode*& t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode* findMin(AvlNode* t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    int findMinRecursionCount(AvlNode* t) const
    {
        if (t == nullptr || t->left == nullptr)
            return 0;

        return 1 + findMinRecursionCount(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode* findMax(AvlNode* t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable& x, AvlNode* t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true;    // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, AvlNode *t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match

            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode*& t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(AvlNode* t) const
    {
        if (t != nullptr)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode* clone(AvlNode* t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode* t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode*& k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode*& k1)
    {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode*& k3)
    {
        AvlNode* k2 = k3->left->right;
        k3->left->right = k2->left;
        k2->left = k3->left;
        k3->left->height = max(height(k3->left->left), height(k3->left->right)) + 1;
        k2->height = max(height(k2->right), k3->left->height) + 1;
        k3->left = k2;

        AvlNode* k1 = k3->left;
        k3->left = k1->right;
        k1->right = k3;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        k1->height = max(height(k1->left), k3->height) + 1;
        k3 = k1;
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode*& k1)
    {
        AvlNode* k2 = k1->right->left;
        k1->right->left = k2->right;
        k2->right = k1->right;
        k1->right->height = max(height(k1->right->left), height(k1->right->right)) + 1;
        k2->height = max(height(k2->left), k1->right->height) + 1;
        k1->right = k2;

        AvlNode* k3 = k1->right;
        k1->right = k3->left;
        k3->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k3->height = max(height(k3->right), k1->height) + 1;
        k1 = k3;
    }
};