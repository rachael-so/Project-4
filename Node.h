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
    Node(int);
    ~Node();
    int size;
    int numKeys;
    int *keys;
    Node **children;
    bool isLeaf;
};

Node::Node(int size)
{
    this->size = size;
    this->keys = new int[size+1];
    this->numKeys = 0;
    this->isLeaf = false;
}

Node::~Node()
{
    delete [] keys;
}

#endif /* Node_h */
