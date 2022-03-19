#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
    // std::pair<const Key, Value>* find(const Key& key);
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // MY HELPER FUNCTIONS
    // AVLNode<Key, Value>* findAVLNode(const Key& key); // returns AVLNode
    void rotateLeft(AVLNode<Key, Value>* node);
    void rotateRight(AVLNode<Key, Value>* node);
    AVLNode<Key, Value>* unbalancedNode(AVLNode<Key, Value>* node); // find which node to set as z when rotating
    void recursiveSetHeight(AVLNode<Key, Value>* node); // use height() to set heights recursively after rotations. Usually root that's plugged in.
    void balanceAVLTree(AVLNode<Key, Value>* toInsert);
    AVLNode<Key, Value>* returnParent(AVLNode<Key, Value>* node, bool& setRightToNull);
    //subtreesBalanced is gonna be mad useful
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // parent is what we're tryna find
    // need to have root base case
    // else set either left or right
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key,Value>*>(this->root_);
    AVLNode<Key, Value>* toInsert = curr;
    if (curr == NULL) {
        AVLNode<Key, Value>* toInsert = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        this->root_ = toInsert;
    }
    else {
        // this while loops takes us till we've found our desired parent
        while (true) {
            if (new_item.first == curr->getKey()) {
                AVLNode<Key, Value>* newValue = static_cast<AVLNode<Key,Value>*>(this->internalFind(new_item.first)); 
                newValue->setValue(new_item.second);
                break;
            }
            else if (new_item.first < curr->getKey() && curr->getLeft() != NULL) {
                curr = curr->getLeft();
            }
            else if (new_item.first > curr->getKey() && curr->getRight() != NULL) {
                curr = curr->getRight();
            }
            else if (new_item.first < curr->getKey() && curr->getLeft() == NULL) {
                toInsert = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
                curr->setLeft(toInsert);
                toInsert->setParent(curr);
                break;
            }
            else if (new_item.first > curr->getKey() && curr->getRight() == NULL) {
                toInsert = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
                curr->setRight(toInsert);
                toInsert->setParent(curr);
                break;
            }
        }
    }
    balanceAVLTree(toInsert);
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // can't just delete Node when deleting AVLNode. Would cause memory leaks.
    AVLNode<Key, Value>* toDelete = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if (toDelete == NULL) return;

    bool setRightToNull = false; // can tell us which pointer to set as NULL for parent
    AVLNode<Key, Value>* toSwap = toDelete;
     // need while loop to mimic Cote algorithm
    while (true) {
        if (this->childCount(toDelete) == 0) { // no children
            toSwap = static_cast<AVLNode<Key,Value>*>(returnParent(toDelete, setRightToNull)); // delete occurs inside this function
            return;
        }
        else if (this->childCount(toDelete) == 1) { // left child
            toSwap = toDelete->getLeft();
            setRightToNull = false;
            nodeSwap(toDelete, toSwap);
        }
        else if (this->childCount(toDelete) == 2) { // right child
            toSwap = toDelete->getRight();
            setRightToNull = true;
            nodeSwap(toDelete, toSwap);
        }
        else if (this->childCount(toDelete) == 3) { // 2 children
            toSwap = static_cast<AVLNode<Key,Value>*>(this->predecessor(toDelete));
            setRightToNull = true; // biggest of left subtree, will have no right child. Will be pointed to by right.
            nodeSwap(toDelete, toSwap);
        }
    }
    balanceAVLTree(toSwap);
    return;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::returnParent(AVLNode<Key, Value>* node, bool& setRightToNull)
{
    AVLNode<Key, Value>* parent = node->getParent();
    if (setRightToNull) {
        parent->setRight(NULL);
    }
    else parent->setLeft(NULL);

    if (parent->getRight() == NULL && parent->getLeft() == NULL) parent->setHeight(1);
    else if (parent->getRight() != NULL || parent->getLeft() != NULL) parent->setHeight(2);

    delete node;
    return parent;
}

template<class Key, class Value>
void AVLTree<Key, Value>::recursiveSetHeight(AVLNode<Key, Value>* node)
{   
    // not used
    if (node == NULL) return;
    node->setHeight(this->height(node));
    if (node->getLeft() != NULL) {
        recursiveSetHeight(node->getLeft());
    }
    if (node->getRight() != NULL) {
        recursiveSetHeight(node->getRight()); // thought we doubled up here at first but I realize we don't
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::balanceAVLTree(AVLNode<Key, Value>* toInsert)
{
    if (toInsert == NULL) {
        return;
    }
    
    if (!this->isBalanced()) {
        AVLNode<Key, Value>* toBalance = unbalancedNode(toInsert); // grandparent node

        if (toBalance != NULL) {
            if (toBalance->getLeft() != NULL && toBalance->getRight() != NULL) {
                if (this->height(toBalance->getLeft()) >= this->height(toBalance->getRight())) {
                    rotateRight(toBalance);
                }
                else rotateLeft(toBalance);
            }
            else if (toBalance->getLeft() == NULL && toBalance->getRight() != NULL) {
                rotateLeft(toBalance);
            }
            else if (toBalance->getLeft() != NULL && toBalance->getRight() == NULL) {
                rotateRight(toBalance);
            }
        }
    }
    recursiveSetHeight(static_cast<AVLNode<Key,Value>*>(this->root_));
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::unbalancedNode(AVLNode<Key, Value>* node)
{
    int leftHeight = 0; // if there's nothing there it's 0. Same with right.
    int rightHeight = 0;
    if (node == NULL) return NULL; // shouldn't happen

    if (node->getParent() != NULL) {
        node = node->getParent();

        if (node->getLeft() != NULL) { 
            leftHeight = this->height(node->getLeft());
        }
        if (node->getRight() != NULL) {
            rightHeight = this->height(node->getRight());
        }

        if (leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1) return node;
        else return unbalancedNode(node);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* z = node;
    AVLNode<Key, Value>* y = z->getRight();
    AVLNode<Key, Value>* x = y->getRight();

    // for a single rotation... call for doubles after.
    if (z == this->root_) {
        this->root_ = y;
        y->setParent(NULL);
    }
    else {
        AVLNode<Key, Value>* parent = z->getParent();// parent of z to become parent of y
        if (parent->getRight() == z) {
            parent->setRight(y);
        }
        else if (parent->getLeft() == z) {
            parent->setLeft(y);
        }
        y->setParent(parent);
    }
    if (y->getLeft() != NULL) z->setRight(y->getLeft());
    else z->setRight(NULL);

    if (z->getRight() != NULL) {
        z->getRight()->setParent(z);
    }
    y->setLeft(z);
    z->setParent(y);
    balanceAVLTree(y);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* z = node;
    AVLNode<Key, Value>* y = node->getLeft();
    AVLNode<Key, Value>* x = y->getLeft();

    // for a single rotation... call for doubles after.
    if (node == this->root_) {
        this->root_ = y;
        y->setParent(NULL);
    }
    else {
        AVLNode<Key, Value>* parent = z->getParent();// parent of z to become parent of y
        if (parent->getRight() == z) {
            parent->setRight(y);
        }
        else if (parent->getLeft() == z) {
            parent->setLeft(y);
        }
        y->setParent(parent);
    }
    if (y->getRight() != NULL) z->setLeft(y->getRight());
    else z->setLeft(NULL);
    if (z->getLeft() != NULL) {
        z->getLeft()->setParent(z);
    }
    y->setRight(z);
    z->setParent(y);
    // recursiveSetHeight(y);
    balanceAVLTree(y);
}

// template<class Key, class Value>
// std::pair<const Key, Value>* AVLTree<Key, Value>::find(const Key& key)
// {
//     AVLNode<Key, Value>* found = static_cast<AVLNode<Key,Value>*>(this->internalFind);
//     return found->getItem();
// }

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = this->height(n1);
    n1->setHeight(this->height(n2));
    n2->setHeight(tempH);
}


#endif
