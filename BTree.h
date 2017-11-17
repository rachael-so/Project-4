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
    int search(Node*, int);
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
        Node* first = new Node(m);
        root = first;
        first->isLeaf = true;
    }
    else {
        int i = 0;
        int k = i;
        Node* current = root;
        Node* prev;
        while (current->isLeaf == false) {
            while (key > current->keys[i]) {
                i++;
            }
            prev = current;
            current = current->children[i];
        }
        if (current->isLeaf == true) {
            for (int j = current->numKeys-1; j > i; j--) {
                current->keys[j] = current->keys[j-1];
            }
            current->keys[i] = key;
            
            if (current->numKeys == current->size) {
                if (current == root) {
                    Node* parent = new Node(m);
                    root = parent;
                    parent->children[0] = current;
                    splitChild(parent, current, 0);
                }
                else {
                    splitChild(prev, current, k);
                }
            }
        }
        else {
            prev = current;
            current = current->children[i];
            k = i;
        }
    }
}

void BTree::splitChild(Node *parent, Node *child, int i)
{
    Node rightChild(child->size+1);
    rightChild.isLeaf = true;
    int mid = child->numKeys/2+1;
    
    for (int j = mid+1; j < child->numKeys; j++) {
        int k = 0;
        rightChild.keys[j] = child->keys[k];
        k++;
        rightChild.numKeys++;
        child->keys[j] = NULL;
        child->numKeys--;
    }
    
    int insertMe = child->keys[mid];
    child->keys[mid] = NULL;
    child->numKeys--;
    
    for (int j = parent->numKeys-1; j > i; j--) {
        parent->keys[j] = parent->keys[j-1];
    }
    parent->keys[i] = insertMe;
    parent->numKeys++;
    
    //add right child
    parent->children[i]->numKeys++;
    parent->children[i+1]->keys = child->keys;
    
    //check if parent is over and if so then call function
    if (parent->numKeys == parent->size) {
        //recursive call????
    }
}

int BTree::remove(int key)
{
    Node *current = root;
    int removeMe = search(current, key);
    
    while (removeMe == -1 && current->children != NULL) {
        int i = 0;
        while (key > current->keys[i]) {
            i++;
        }
        current = current->children[i];
        removeMe = search(current, key);
    }
    
    if (removeMe == key){
        if (current->isLeaf == true) {
            //delete key
        }
        else {
            if (current->numKeys == (m/2-1)) {
                //at minimum number of keys
            }
            else {
                
            }
        }
    }
    else {
        //throw error: key not found
    }
    
    return key;
}

int BTree::search(Node* searchMe, int key)
{
    int low = 0, mid, high = searchMe->numKeys - 1;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (key < searchMe->keys[mid]) {
            high = mid - 1;
        }
        else if (key > searchMe->keys[mid]) {
            low = mid + 1;
        }
        else
            return mid;
    }
    return -1;
}

void BTree::print()
{
    
}

#endif /* BTree_h */
