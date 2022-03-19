#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    Node<Key, Value>* insertHelper(const Key& key, const Value& value, Node<Key, Value>* parent);
    void recurseDeleteBST (Node<Key,Value>* node);
    Node<Key, Value>* allTheWayLeft(Node<Key, Value>* node) const;
    int childCount(Node<Key, Value>* node);
    Node<Key, Value>* returnParentofDeletedNode(Node<Key, Value>* node, bool setRightToNull);
    int height(Node<Key, Value>* node) const;
    bool subtreesBalanced(Node<Key, Value>* node) const;



protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() :
    current_(NULL)
{

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return this->current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing. Finds successor.
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{   
    if (current_->getParent() == NULL && current_->getRight() != NULL) {
        // is root node
        current_ = current_->getRight();
        while (current_->getLeft() != NULL) {
            current_ = current_->getLeft();
        }
    }
    else if (current_->getParent() != NULL && current_ == current_->getParent()->getRight()) {
        // if has parent, and is right child
        // if has right child
        if (current_->getRight() != NULL) {
            current_ = current_->getRight();
            while (current_->getLeft() != NULL) {
                current_ = current_->getLeft();
            } 
        }
        else {
            // if doesn't have right child
            while (current_->getParent() != NULL) {
                current_ = current_->getParent();
                if (current_->getParent() != NULL && 
                    current_->getParent()->getLeft() != NULL && 
                    current_== current_->getParent()->getLeft()) {
                        
                    current_ = current_->getParent();
                    return *this;
                }
            }
            current_ = NULL;
        }
    }
    else if (current_->getParent() != NULL && current_ == current_->getParent()->getLeft()) {
        if (current_->getRight() != NULL) {
            current_ = current_->getRight();
            while (current_->getLeft() != NULL) {
                current_ = current_->getLeft();
            } 
        }
        else current_ = current_->getParent(); // if has parent, and is left child, get parent
    }
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() :
    root_(NULL)
{
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    if (this->root_ == NULL) {
        this->root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    }
    else {
        Node<Key, Value>* curr = this->root_;
        while (true) {
            if (keyValuePair.first == curr->getKey()) {
                curr->setValue(keyValuePair.second);
                return;
            }
            else if (keyValuePair.first < curr->getKey() && curr->getLeft() != NULL) {
                curr = curr->getLeft();
            }
            else if (keyValuePair.first > curr->getKey() && curr->getRight() != NULL) {
                curr = curr->getRight();
            }
            else if (keyValuePair.first < curr->getKey() && curr->getLeft() == NULL) {
                curr->setLeft(insertHelper(keyValuePair.first, keyValuePair.second, curr));
                return; // didn't break, that's why this entered infinite loop
            }
            else if (keyValuePair.first > curr->getKey() && curr->getRight() == NULL) {
                curr->setRight(insertHelper(keyValuePair.first, keyValuePair.second, curr));
                return;
            }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::insertHelper(const Key& key, const Value& value, Node<Key, Value>* parent)
{
    Node<Key, Value>* toInsert = new Node<Key, Value>(key, value, parent);
    return toInsert;
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
   
    Node<Key, Value>* toDelete = internalFind(key);

    if (toDelete == NULL) return;

    bool setRightToNull = false; // can tell us which pointer to set as NULL for parent
     // need while loop to mimic Cote algorithm
    while (true) {
        Node<Key, Value>* toSwap = toDelete; // to what does toDelete refer to after nodeSwap? This ought to take care of it.
        if (childCount(toDelete) == 0) { // no children
            toSwap = returnParentofDeletedNode(toDelete, setRightToNull); // delete occurs inside this function
            return;
        }
        else if (childCount(toDelete) == 1) { // left child
            toSwap = toDelete->getLeft();
            nodeSwap(toDelete, toSwap);
            setRightToNull = false;
        }
        else if (childCount(toDelete) == 2) { // right child
            toSwap = toDelete->getRight();
            setRightToNull = true;
            nodeSwap(toDelete, toSwap);
        }
        else if (childCount(toDelete) == 3) { // 2 children
            toSwap = predecessor(toDelete);
            setRightToNull = true; // biggest of left subtree, will have no right child. Will be pointed to by right.
            nodeSwap(toDelete, toSwap);
        }
    }
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::childCount(Node<Key, Value>* node)
{
    if (node->getLeft() == NULL && node->getRight() == NULL) return 0; // no pointers occupied
    else if (node->getLeft() != NULL && node->getRight() == NULL) return 1; // first (left) pointer occupied
    else if (node->getLeft() == NULL && node->getRight() != NULL) return 2; // second (right) pointer occupied
    else if (node->getLeft() != NULL && node->getRight() != NULL) return 3; // both child pointers occupied
    else return 100;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::returnParentofDeletedNode(Node<Key, Value>* node, bool setRightToNull)
{
    Node<Key, Value>* parent = node->getParent();
    if (setRightToNull) {
        parent->setRight(NULL);
    }
    else parent->setLeft(NULL);

    delete node;
    return parent;
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // this would be the biggest element in the left subtree
    current = current->getLeft();
    while (current->getRight() != NULL) {
        current = current->getRight(); // this should be how to access predecessor
    }
    return current;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    recurseDeleteBST(root_);
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::recurseDeleteBST(Node<Key,Value>* node)
{
    // POST ORDER TRAVERSAL. Must be recursive.
    if (node == NULL) return;
    
    if (node == root_) root_ = NULL; // mandatory, otherwise root_ won't know where to point
    
    if (node->getLeft() == NULL && node->getRight() != NULL) {
        recurseDeleteBST(node->getRight());
        delete node;
    }
    else if (node->getLeft() != NULL && node->getRight() == NULL) {
        recurseDeleteBST(node->getLeft());
        delete node;
    }
    else if (node->getLeft() != NULL && node->getRight() != NULL) {
        recurseDeleteBST(node->getLeft());
        recurseDeleteBST(node->getRight());
        delete node;
    }
    else {
        delete node;
        return;
    }
    
    // else if (node->getLeft() == NULL && node->getRight() != NULL) {
    //     // this condition only one left? But its inclusion gums up algorithm.
    //     delete node;
    //     return;
    // }
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    if (root_ == NULL) return root_;
    else return allTheWayLeft(root_); // need helper for this helper bc no intake of node
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::allTheWayLeft(Node<Key, Value>* node) const
{
    if (node->getLeft() == NULL) return node;

    return allTheWayLeft(node->getLeft());
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    Node<Key, Value>* curr = root_;
    if (curr == NULL) return NULL; // unsure if this necessary but it seemed to help so gonna leave it

    while (true) {
        if (key == curr->getKey()) {
            return curr;
        }
        else if (key < curr->getKey() && curr->getLeft() != NULL) {
            curr = curr->getLeft();
        }
        else if (key > curr->getKey() && curr->getRight() != NULL) {
            curr = curr->getRight();
        }
        else {
            return NULL;
        }
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return subtreesBalanced(this->root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::subtreesBalanced(Node<Key, Value>* node) const
{
    if (node == NULL) return true;

	int leftHeight = height(node->getLeft());
	int rightHeight = height(node->getRight());

	if (leftHeight == rightHeight || leftHeight - rightHeight == 1 
	|| rightHeight - leftHeight == 1) {
		return subtreesBalanced(node->getLeft()) && subtreesBalanced(node->getRight());
	}
	else return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* node) const {
	if (node == NULL)  return 0;
    // to match constructor: node exists, height 1. No node, height 0. x children, height 1 + x.

	if (height(node->getLeft()) >= height(node->getRight())) {
        return 1 + height(node->getLeft());
    }
	else {
        return 1 + height(node->getRight());
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
