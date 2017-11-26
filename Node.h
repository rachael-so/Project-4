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
#include <cmath>

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
    int search(int);
    void remove(int);
    void removeFromNonLeaf(int);
    void borrowFromPrev(int);
    void borrowFromNext(int);
    void merge(int);
    int numKeys;
    int *keys;
    Node **children;
    bool isLeaf;
private:
    int size;
    int minKeys;
};

Node::Node(float m)
{
    this->size = m-1;
    this->keys = new int[size];
    this->numKeys = 0;
    this->isLeaf = false;
    this->children = NULL;
    this->minKeys = ceil(m/2)-1;
}

Node::~Node()
{
    delete [] keys;
    size = 0;
    numKeys = 0;
    children = NULL;
}

int Node::search(int key)
{
    int i = 0;
    while (i < numKeys && key > keys[i]) {
        i++;
    }

    return i;
}

void Node::remove(int key)
{
    int idx = search(key);
    
    //check if key is in this node
    if (idx < numKeys && keys[idx] == key) {
        //check if leaf
        if (isLeaf) {
            //remove key
            for (int i = idx+1; i < numKeys; i++)
                keys[i-1] = keys[i];
            numKeys--;
        }
        else {
            removeFromNonLeaf(idx);
        }
    }
    else {
        if (isLeaf) {
            cout << "child not found in tree\n";
        }
        else {
            //check if child has too little keys to traverse into
            if ((children[idx]->isLeaf && children[idx]->numKeys < minKeys) ||
                (!children[idx]->isLeaf && children[idx]->numKeys <= minKeys))
            {
                //borrow from previous sibling if possible
                if (idx != 0 && ((children[idx-1]->numKeys > minKeys)
                    || (!children[idx-1]->isLeaf && children[idx-1]->numKeys >= minKeys))) {
                    borrowFromPrev(idx);
                }
                //can't borrow from previous sibling then borrow from next sibling
                else if (idx != numKeys && ((children[idx+1]->numKeys > minKeys) ||
                        (!children[idx+1]->isLeaf && children[idx+1]->numKeys >= minKeys))) {
                    borrowFromNext(idx);
                }
                //if both siblings are at minimum keys then merge
                else {
                    //check if next child is last child if so merge on idx-1 else merge on idx
                    if (idx == numKeys)
                        merge(idx-1);
                    else
                        merge(idx);
                }
            }
            
            //call remove key on child
            if (idx == numKeys+1)
                //child was merged so remove on previous sibling
                children[idx-1]->remove(key);
            else
                children[idx]->remove(key);
        }
    }
}

void Node::removeFromNonLeaf(int idx)
{
//    cout << "in removeFromNonLeaf\n";
    //save current key at idx
    int key = keys[idx];

    if (children[idx]->numKeys >= minKeys) {
        //find leaf
        Node *current = children[idx];
        while (!current->isLeaf)
            current = current->children[current->numKeys];
        
        //set idx to rightmost key of left subtree (predecessor)
        int pred = current->keys[current->numKeys-1];
        keys[idx] = pred;
        
        //call remove on pred starting from child
        children[idx]->remove(pred);
    }
    else if  (children[idx+1]->numKeys >= minKeys) {
        //find leaf
        Node *current = children[idx+1];
        while (!current->isLeaf)
            current = current->children[0];
        
        //set idx to leftmost key of right subtree (successor)
        int succ = current->keys[0];
        keys[idx] = succ;
        
        //call remove on succ
        children[idx+1]->remove(succ);
    }
    else {
        //both children are at min keys
        merge(idx);
        children[idx]->remove(key);
    }
}

void Node::borrowFromPrev(int idx)
{
//    cout << "in borrowFromPrev\n";
    Node *child = children[idx];
    Node *sibling = children[idx-1];
    
    //make room in child
    for (int i = child->numKeys-1; i >= 0; i--)
        child->keys[i+1] = child->keys[i];
    
    if (!child->isLeaf)
    {
        for(int i = child->numKeys; i >= 0; i--)
            child->children[i+1] = child->children[i];
    }
    
    //demote
    child->keys[0] = keys[idx-1];
    child->numKeys++;
    
    //adjust pointers
    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];
    
    //promote
    keys[idx-1] = sibling->keys[sibling->numKeys-1];
    sibling->numKeys--;
}

void Node::borrowFromNext(int idx)
{
//    cout << "in borrowFromNext\n";
    Node *child = children[idx];
    Node *sibling = children[idx+1];
    
    //demote
    child->keys[(child->numKeys)] = keys[idx];
    child->numKeys++;
    
    //adjust children pointers
    if (!child->isLeaf)
        child->children[(child->numKeys)] = sibling->children[0];
    
    //promote
    keys[idx] = sibling->keys[0];
    
    //close up sibling
    for (int i = 1; i < sibling->numKeys; i++)
        sibling->keys[i-1] = sibling->keys[i];
    
    if (!sibling->isLeaf)
    {
        for(int i=1; i<=sibling->numKeys; i++)
            sibling->children[i-1] = sibling->children[i];
    }
    sibling->numKeys--;
}

void Node::merge(int idx)
{
//    cout << "in merge\n";
    Node *child = children[idx];
    Node *sibling = children[idx+1];
    
    //demote
    child->keys[minKeys-1] = keys[idx];
    child->numKeys++;
    
    //copy keys and child pointers
    for (int i = 0; i < sibling->numKeys; i++) {
        child->keys[i+minKeys] = sibling->keys[i];
        child->numKeys++;
    }
    
    if (!child->isLeaf)
    {
        for(int i = 0; i <= sibling->numKeys; i++)
            child->children[i+minKeys] = sibling->children[i];
    }
    
    //close up keys
    for (int i = idx+1; i < numKeys; i++)
        keys[i-1] = keys[i];
    //close up pointers
    for (int i = idx+2; i <= numKeys; i++)
        children[i-1] = children[i];
    
    numKeys--;
    
    // Freeing the memory occupied by sibling
    delete sibling;
}

#endif /* Node_h */
