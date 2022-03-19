#include "avlbst.h"
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {

    // BinarySearchTree<int, int>* tree = new BinarySearchTree<int,int>();
    AVLTree<int, int>* tree = new AVLTree<int,int>();

    const pair<int,int> a(1, 1);
    const pair<int,int> b(2, 2);
    const pair<int,int> c(3, 3);
    const pair<int,int> d(4, 4);
    const pair<int,int> e(5, 5);
    const pair<int,int> f(6, 6);
    const pair<int,int> g(7, 7);
    const pair<int,int> h(8, 8);
    const pair<int,int> i(9, 9);
    const pair<int,int> j(10, 10);
    const pair<int,int> k(11, 11);
    const pair<int,int> l(12, 12);
    const pair<int,int> m(13, 13);
    const pair<int,int> n(14, 14);
    const pair<int,int> o(15, 15);
    const pair<int,int> p(16, 16);

    
    tree->insert(a);
    tree->insert(b);
    tree->insert(c);
    const pair<int,int> c1(3, 5);
    tree->insert(c1);
    tree->insert(d);
    tree->insert(e);
    tree->insert(f);
    tree->insert(g);
    tree->insert(h);
    tree->insert(i);
    tree->insert(j);
    tree->insert(k);
    tree->insert(l);
    tree->insert(m);    
    

    // tree->insert(e);
    // tree->insert(a);
    // tree->insert(d);
    // tree->insert(g);
    // tree->insert(h);
    // tree->insert(i);
    // tree->insert(b);
    // const pair<int, int> a1(1, 3);
    // tree->insert(a1);
    // tree->remove(5);
    // tree->insert(c);

    // tree->clear();
    
    tree->print();

    // BinarySearchTree<int, int>::iterator ptr = tree->begin();
    // for(int i = 0; i < 8; ++i) {
    //     cout << ptr->first << endl;
    //     ++ptr;
    // }
    // tree->~BinarySearchTree(); // didn't need to call this with delete tree following
    // tree->~AVLTree();

    delete tree;
    return 0;
}