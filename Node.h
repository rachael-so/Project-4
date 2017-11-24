//
//  Node.h
//  p4
//
//  Created by Rachael So on 11/11/17.
//  Copyright © 2017 Rachael So. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <iostream>

using namespace std;

/****************************************************************************
 ****************************************************************************
 *                                                                          *
 *                        class Node declaration                            *
 *                                                                          *
 ****************************************************************************
 ****************************************************************************/

class Node
{
public:
    Node(int, int);
    ~Node();
    int numKeys;
    int depth;
    int *keys;
    Node **children;
    bool isLeaf;
private:
    int size;
};

Node::Node(int size, int depth)
{
    this->size = size;
    this->keys = new int[size+1];
    this->numKeys = 0;
    this->depth = depth;
    this->isLeaf = false;
    this->children = NULL;
}

Node::~Node()
{
    delete [] keys;
}

#endif /* Node_h */
