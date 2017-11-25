//
//  BTree.h
//  p4
//
//  Created by Rachael So on 11/11/17.
//  Copyright © 2017 Rachael So. All rights reserved.
//

#ifndef BTree_h
#define BTree_h

#include <cmath>
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
    void insert(int);
    void insertToNonFull(int, Node*);
    void splitChild(Node*, Node*, int);
    void remove(int);
    int search(Node*, int);
    void print(Node*);
    Node* root;
};

BTree::BTree(int m)
{
    this->m = m;
    this->height = 0;
    this->root = NULL;
}

BTree::~BTree()
{
//    for (int i = 0; root->children[i] != NULL; i++){
//        root->children[i] = NULL;
//        delete [] root->children[i];
//    }
}

void BTree::insert(int key)
{
    //check if tree is empty
    if (root == NULL) {
        //create new node
        Node* first = new Node(m);
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
            Node* parent = new Node(m);
            height++;
            Node* child = root;
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

void BTree::insertToNonFull(int key, Node* current)
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
        Node* child = current->children[i];
        
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
    Node* rightChild = new Node(m);
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

//void BTree::remove(int key)
//{
//    Node* current = root;
//    int idx = search(current, key);
//    
//    while (current->keys[idx] != key && current->isLeaf == false) {
//        
//        //initialize child to move into
//        Node* child = current->children[idx];
//        
//        //check if child is at minimum value (m/2-1)
//        if (child->numKeys == m/2-1) {
//            //check if siblings are at minimum
//            if ((idx == 0 && current->children[idx+1]->numKeys == m/2-1)
//                || (idx == current->numKeys && current->children[idx-1]->numKeys == m/2-1)
//                || (idx > 0 && idx < current->numKeys-1
//                    && current->children[idx+1]->numKeys == m/2-1
//                    && current->children[idx-1]->numKeys == m/2-1)) {
//                    //udjust child and siblingChild
//                    Node* siblingChild;
//                    if (idx == current->numKeys) {
//                        siblingChild = child;
//                        child = current->children[idx-1];
//                    }
//                    else {
//                        siblingChild = current->children[idx+1];
//                    }
//                    
//                    //merge child and sibling leaving room for median
//                    int origNumKeys = child->numKeys;
//                    int i = 0, j = origNumKeys+1;
//                    while (i < siblingChild->numKeys) {
//                        child->keys[j] = siblingChild->keys[i];
//                        child->numKeys++;
//                        //if not leaf nodes udjust the children
//                        if (child->isLeaf == false) {
//                            child->children[j] = siblingChild->children[i];
//                        }
//                        i++;
//                        j++;
//                    }
//                    if (child->isLeaf == false) {
//                        child->children[j] = siblingChild->children[i];
//                    }
//                    delete [] siblingChild->keys;
//                    siblingChild = NULL;
//                    
//                    //insert median
//                    child->keys[origNumKeys] = current->keys[idx];
//                    child->numKeys++;
//                    
//                    //udjust keys and pointers in current
//                    for (int i = idx; i < current->numKeys; i++) {
//                        current->keys[i] = current->keys[i+1];
//                        current->children[i+1] = current->children[i+2];
//                    }
//                    current->numKeys--;
//                    
//                    if (root->numKeys == 0) {
//                        delete [] root->keys;
//                        root = child;
//                        height--;
//                    }
//
//                }
//            else {
//                //find which sibling child has more keys
//                Node* siblingChild;
//                if (current->children[idx-1] == NULL
//                    || current->children[idx+1]->numKeys > current->children[idx-1]->numKeys) {
//                    siblingChild = current->children[idx+1];
//                    
//                    //demote a key from current
//                    child->keys[child->numKeys] = current->keys[idx];
//                    child->numKeys++;
//                    
//                    //edit sibling’s child pointers and attach one to the new key in child
//                    child->children[child->numKeys] = siblingChild->children[0];
//                    
//                    //promote key from sibling to current
//                    current->keys[idx] = siblingChild->keys[0];
//                    
//                    //delete promoted key from sibling
//                    int i = 0;
//                    while (i < siblingChild->numKeys) {
//                        siblingChild->keys[i] = siblingChild->keys[i+1];
//                        if (child->isLeaf == false) {
//                            child->children[i] = siblingChild->children[i+1];
//                        }
//                        i++;
//                    }
//                    if (child->isLeaf == false) {
//                        child->children[i] = siblingChild->children[i+1];
//                    }
//                    siblingChild->numKeys--;
//                }
//                else {
//                    siblingChild = current->children[idx-1];
//                    
//                    //make room in child
//                    int i = child->numKeys;
//                    while (i > 0) {
//                        child->keys[i] = child->keys[i-1];
//                        if (child->isLeaf == false) {
//                            child->children[i+1] = child->children[i];
//                        }
//                        i--;
//                    }
//                    
//                    //demote a key from current
//                    child->keys[0] = current->keys[idx];
//                    
//                    //edit sibling’s child pointers and attach one to the new key in child
//                    child->children[0] = siblingChild->children[siblingChild->numKeys];
//                    
//                    //promote key from sibling to current
//                    current->keys[idx] = siblingChild->keys[siblingChild->numKeys-1];
//                    siblingChild->keys[siblingChild->numKeys-1] = NULL;
//                    siblingChild->numKeys--;
//                }
//            }
//            //move into child
//            current = child;
//            idx = search(current, key);
//        }
//        else {
//            //move into child
//            current = child;
//            idx = search(current, key);
//        }
//        
//    }
//    
//    if (current->isLeaf) {
//        if (current->keys[idx] != key) {
//            cout << "key is not found in tree\n";
//            return;
//        }
//        else {
//            //remove key
//            for (int i = idx; i < current->numKeys; i++) {
//                current->keys[i] = current->keys[i+1];
//            }
//            current->numKeys--;
//        }
//    }
//    else  {
//        Node* leftChild = current->children[idx];
//        Node* rightChild = current->children[idx+1];
//        if (leftChild->numKeys == m/2-1 && rightChild->numKeys == m/2-1) {
//            //merge children
//            for (int i = 0, j = leftChild->numKeys; i < rightChild->numKeys; i++, j++) {
//                leftChild[j] = rightChild[i];
//            }
//            delete [] rightChild;
//            rightChild = NULL;
//            
//            //remove key and adjust pointers
//            int i = idx;
//            while (i < current->numKeys) {
//                current->keys[i] = current->keys[i+1];
//                current->children[i+1] = current->children[i+2];
//                i++;
//            }
//            current->children[i+1] = current->children[i+2];
//            current->numKeys--;
//        }
//        else {
//            while (current->isLeaf == false) {
//                int deleteMe = current->keys[idx];
//                leftChild = current->children[idx];
//                rightChild = current->children[idx+1];
//        
//                //find which child is larger and promote a key
//                if (leftChild->numKeys > rightChild->numKeys) {
//                    current->keys[idx] = leftChild->keys[leftChild->numKeys-1];
//                    
//                    //demote the key to remove into child
//                    int i = rightChild->numKeys;
//                    while (i > 0) {
//                        rightChild[i] = rightChild[i-1];
//                        if (rightChild->isLeaf == false)
//                            rightChild->children[i+1] = rightChild->children[i];
//                        i--;
//                    }
//                    if (rightChild->isLeaf == false)
//                        rightChild->children[i+1] = rightChild->children[i];
//                    
//                    rightChild->keys[0] = deleteMe;
//                    rightChild->numKeys++;
//                    if (rightChild->isLeaf == false) {
//                        rightChild->children[0] = leftChild->children[leftChild->numKeys];
//                        leftChild->children[leftChild->numKeys] = NULL;
//                    }
//                    leftChild->keys[leftChild->numKeys-1] = NULL;
//                    leftChild->numKeys--;
//                    
//                    //move into child
//                    idx = 0;
//                    current = rightChild;
//                }
//                else {
//                    current->keys[idx] = rightChild->keys[0];
//                    leftChild->keys[leftChild->numKeys] = deleteMe;
//                    leftChild->numKeys++;
//                    if (leftChild->isLeaf == false )
//                        leftChild->children[leftChild->numKeys] = rightChild->children[0];
//                    
//                    int i = 0;
//                    while (i < rightChild->numKeys) {
//                        rightChild->keys[i] = rightChild->keys[i+1];
//                        if (rightChild->isLeaf == false)
//                            rightChild->children[i] = rightChild->children[i+1];
//                        i++;
//                    }
//                    if (rightChild->isLeaf == false)
//                        rightChild->children[i] = NULL;
//                    rightChild->numKeys--;
//                    
//                    //move into child
//                    idx = leftChild->numKeys-1;
//                    current = leftChild;
//                }
//            }
//            //remove key
//            for (int i = idx; i < current->numKeys; i++) {
//                current->keys[i] = current->keys[i+1];
//            }
//            current->numKeys--;
//
//        }
//    }
//    
//}

void BTree::remove(int key)
{
    //search tree for value and keep track of parent
    Node* current = root;
    Node* parent;
    int idx = search(current, key);
    int parentIdx;
    
    while (current->keys[idx] != key && current->isLeaf == false) {
        parent = current;
        parentIdx = idx;
        current = current->children[idx];
        idx = search(current, key);
    }

}

int BTree::search(Node* searchMe, int key)
{
    int i = 0;
    while (key > searchMe->keys[i]) {
        i++;
    }
    
    return i;
}

void BTree::print(Node* treeRoot)
{
    for (int i = 0; i < treeRoot->numKeys; i++) {
        cout << treeRoot->keys[i];
        if (i < treeRoot->numKeys-1) {
            cout << ",";
        }
    }
    
    int i = 0;
    while (i < treeRoot->numKeys && treeRoot->isLeaf == false) {
        if (treeRoot->children != NULL) {
            cout << "[";
            print(treeRoot->children[i]);
            cout << "]";
            }
        i++;
    }

    if (treeRoot->isLeaf == false) {
//        cout << "here\n";
        cout << "[";
        print(treeRoot->children[i]);
        cout << "]";
    }
    else {
        while (i < treeRoot->numKeys) {
            if (treeRoot->children != NULL) {
                cout << "[";
                print(treeRoot->children[i]);
                cout << "]";
            }
            i++;
        }
    }
    
}

#endif /* BTree_h */
