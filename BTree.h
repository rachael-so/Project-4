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
    int size;
    int height;
    Node* root;
public:
    BTree();
    ~BTree();
    void insert(int);
    int remove(int);
    void print();
};

BTree::BTree()
{
    this->size = 0;
    this->height = 0;
    this->root = NULL;
}

BTree::~BTree()
{
    
}

void BTree::insert(int key)
{
    
}

int BTree::remove(int key)
{
    return key;
}

void BTree::print()
{
    
}

#endif /* BTree_h */
