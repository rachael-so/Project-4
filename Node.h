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
private:
    int size;
    int* a;
public:
    Node(int,int);
    ~Node();
};

Node::Node(int size, int degree)
{
    this->size = size;
    this->a = new int[size];
}

Node::~Node()
{
    delete [] a;
}

#endif /* Node_h */
