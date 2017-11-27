//
//  BTree.h
//  p4
//
//  Created by Rachael So on 11/11/17.
//  Copyright © 2017 Rachael So. All rights reserved.
//

#ifndef BTree_h
#define BTree_h

#include "Node.h"

using namespace std;

/****************************************************************************
 ****************************************************************************
 *                                                                          *
 *                        class BTree declaration                           *
 *                                                                          *
 ****************************************************************************
 ****************************************************************************/

class BTree
{
private:
    float m;
    int height;
public:
    BTree(int);
    ~BTree();
    void clear(Node*);
    void insert(int);
    void insertToNonFull(int, Node*);
    void splitChild(Node*, Node*, int);
    void remove(int);
    void removeInLeaf(Node*, Node*, int, int, int);
    void removeAtMin(Node*, int, int);
    int search(Node*, int);
    void print(Node*);
    Node *root;
};

BTree::BTree(int m)
{
    this->m = m;
    this->height = 0;
    this->root = NULL;
}

BTree::~BTree()
{
    clear(root);
}

void BTree::clear(Node *current)
{
    //depth first recurrsion through all children
    for (int i = 0; i <= current->numKeys && !current->isLeaf; i++) {
        clear(current->children[i]);
    }
    
    for (int i = 0; i <= current->numKeys; i++) {
        delete current;
    }
    
    if (!current->isLeaf) {
        //delete children array
        delete [] current->children;
        current->children = NULL;
    }
}

void BTree::insert(int key)
{
    //check if tree is empty
    if (root == NULL) {
        //create new node
        Node *first = new Node(m);
        root = first;
        first->isLeaf = true;
        
        //insert key into node
        first->keys[0] = key;
        first->numKeys++;
        height++;
    }
    else {
        //check if root is full
        if (root->numKeys == m-1) {
            //create new root
            Node *parent = new Node(m);
            height++;
            Node *child = root;
            root = parent;
            
            //make old root child of new root
            int size = m;
            parent->children = new Node*[size];
            parent->children[0] = child;
            
            
            //split child, which updates new root with median
            splitChild(parent, child, 0);
            
            //find correct child to insert into
            if (key < parent->keys[0]) {
                insertToNonFull(key, parent->children[0]);
            }
            else {
                insertToNonFull(key, parent->children[1]);
            }
        }
        else {
            insertToNonFull(key, root);
        }
    }
//    print(root);
//    cout << endl;
}

void BTree::insertToNonFull(int key, Node *current)
{
    //check if leaf node
    if (current->isLeaf == true) {
        //find location to insert
        int i = 0;
        while (key > current->keys[i] && i < current->numKeys) {
            i++;
        }
        
        //make room for insert
        for (int j = current->numKeys; j > i; j--)
            current->keys[j] = current->keys[j-1];
        
        //insert key
        current->keys[i] = key;
        current->numKeys++;
    }
    else {
        //find correct child to insert into
        int i = 0;
        while (key > current->keys[i] && i < current->numKeys) {
            i++;
        }
        Node *child = current->children[i];
        
        //check if child is full
        if (current->children[i]->numKeys == m-1) {
            //split child, which updates current node with median
            splitChild(current, current->children[i], i);
            
            //find correct child to insert into
            if (key < current->keys[i]) {
                 child = current->children[i];
            }
            else {
                child = current->children[i+1];
            }
        }
        
        insertToNonFull(key, child);
    }
    
}


void BTree::splitChild(Node *parent, Node *child, int i)
{
    //create new right child
    Node *rightChild = new Node(m);
    rightChild->isLeaf = child->isLeaf;
    if (child->children != NULL) {
        int size = m;
        rightChild->children = new Node*[size];
    }
    
    //find median index of child
    int mid = child->numKeys/2;
    
    //copy left half of child into new right child
    int origNumKeys = child->numKeys;
    int j = mid+1, k = 0;
    while (j < origNumKeys) {
        rightChild->keys[k] = child->keys[j];
        if (child->children != NULL) {
            rightChild->children[k] = child->children[j];
            child->children[j] = NULL;
        }
        rightChild->numKeys++;
        child->keys[j] = NULL;
        child->numKeys--;
        j++;
        k++;
    }
    if (child->children != NULL) {
        rightChild->children[k] = child->children[j];
        rightChild->children[j] = NULL;
    }
    
    //save median in a variable
    int insertMe = child->keys[mid];
    child->keys[mid] = child->keys[mid+1];
    child->numKeys--;
    
    //make room in parent to insert the median value
    for (int j = parent->numKeys; j > i; j--) {
        parent->keys[j] = parent->keys[j-1];
    }
    
    //insert median value into parent
    parent->keys[i] = insertMe;
    parent->numKeys++;
    
    //make room to add right child
    for (int j = parent->numKeys+1; j > i+1; j--) {
        parent->children[j] = parent->children[j-1];
    }
    
    //add right child
    parent->children[i+1] = rightChild;
}

void BTree::remove(int key)
{
    if (root == NULL)
    {
        cout << "tree is empty\n";
    }
    
    // Call the remove function starting at root
    root->remove(key);
    
    //check root and adjust
    if (root->numKeys == 0)
    {
        Node *temp = root;
        if (root->isLeaf)
            root = NULL;
        else
            root = root->children[0];
        
        delete temp;
    }
}

void BTree::print(Node *treeRoot)
{
    //print out keys
    for (int i = 0; i < treeRoot->numKeys; i++) {
        cout << treeRoot->keys[i];
        if (i < treeRoot->numKeys-1) {
            cout << ",";
        }
    }
    
    //print out children depth first using recurrsion
    for (int i = 0; i <= treeRoot->numKeys && !treeRoot->isLeaf; i++) {
            cout << "[";
            print(treeRoot->children[i]);
            cout << "]";
    }
    
}

#endif /* BTree_h */
