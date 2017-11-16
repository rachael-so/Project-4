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
    int m;
    int height;
    Node* root;
public:
    BTree(int);
    ~BTree();
    void insert(int);
    void splitChild(Node*, Node*, int);
    int remove(int);
    void print();
};

BTree::BTree(int m)
{
    this->m = m;
    this->height = 0;
    this->root = NULL;
}

BTree::~BTree()
{
    
}

void BTree::insert(int key)
{
    if (root == NULL) {
        
    }
}

void BTree::splitChild(Node *parent, Node *child, int i)
{
    Node rightChild(child->size+1);
    int mid = child->numKeys/2+1;
    
    for (int j = mid+1; j < child->numKeys; j++) {
        int k = 0;
        rightChild.keys[j] = child->keys[k];
        k++;
        rightChild.numKeys++;
        child->keys[j] = NULL;
        child->numKeys--;
    }
    
    child->keys[mid] = NULL;
    child->numKeys--;
    
    for (int j = i-1; j < parent->numKeys; j++) {
        parent->keys[j+1] = parent->keys[j];
    }
    parent->keys[i-1] = mid;
    parent->numKeys++;
    
    //add right child
    parent->children->numKeys++;
    parent->children->keys[i+1] = *child->keys;
    
    //check if parent is over and if so then call function
    if (parent->numKeys == parent->size) {
        //recursive call????
    }
}

int BTree::remove(int key)
{
    return key;
}

void BTree::print()
{
    
}

#endif /* BTree_h */
