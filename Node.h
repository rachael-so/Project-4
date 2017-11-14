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
    int *a;
    int *children;
    bool leaf;
};

Node::Node(int size)
{
    this->size = size;
    this->a = new int[size];
    this->children = new int[size];
}

Node::~Node()
{
    delete [] a;
    delete [] children;
}

#endif /* Node_h */
