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
    Node(float);
    ~Node();
    int numKeys;
    int *keys;
    Node **children;
    bool isLeaf;
private:
    int size;
};

Node::Node(float m)
{
    this->size = m-1;
    this->keys = new int[size];
    this->numKeys = 0;
    this->isLeaf = false;
    this->children = NULL;
}

Node::~Node()
{
    delete [] keys;
    size = 0;
    numKeys = 0;
    children = NULL;
}


#endif /* Node_h */
