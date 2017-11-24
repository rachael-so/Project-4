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
    void print(Node*);
};

BTree::BTree(int m)
{
    this->m = m;
    this->height = 0;
    this->root = NULL;
}

BTree::~BTree()
{
    for (int i = 0; root->children[i] != NULL; i++){
        root->children[i] = NULL;
        delete [] root->children[i];
    }
}

void BTree::insert(int key)
{
    if (root == NULL) {
        Node* first = new Node(m, 0);
        root = first;
        first->isLeaf = true;
        first->keys[0] = key;
        first->numKeys++;
        height++;
    }
    else {
        int i = 0;
        int k = 0;
        Node* current = root;
        Node* prev = root;
        while (current->isLeaf == false) {
            while (key > current->keys[k] && k < current->numKeys) {
                k++;
            }
            prev = current;
            current = current->children[k];
        }
//        if (current->isLeaf == true) {
        while (key > current->keys[i] && i < current->numKeys) {
            i++;
        }
        if (i != current->numKeys) {
            for (int j = current->numKeys; j > i; j--)
                current->keys[j] = current->keys[j-1];
        }
        current->keys[i] = key;
        current->numKeys++;
        
        if (current->numKeys == m) {
            if (current == root) {
                Node* parent = new Node(m, 0);
                height++;
                root = parent;
                parent->children = new Node*[m+1];
                parent->children[0] = current;
                current->depth++;
                splitChild(parent, current, 0);
            }
            else {
                splitChild(prev, current, k);
            }
        }
//        }
//        else {
//            prev = current;
//            current = current->children[i];
//            k = i;
//        }
    }
    
    print(root);
    cout << endl;
}

void BTree::splitChild(Node *parent, Node *child, int i)
{
//    cout << "in splitChild\n";
    Node* rightChild = new Node(m, child->depth);
    rightChild->isLeaf = true;
    int mid = child->numKeys/2;
//    cout << "mid: " << mid << endl;
    
    int origNumKeys = child->numKeys;
    for (int j = mid+1, k = 0; j < origNumKeys; j++, k++) {
        rightChild->keys[k] = child->keys[j];
        rightChild->numKeys++;
        child->keys[j] = NULL;
        child->numKeys--;
    }
    
    int insertMe = child->keys[mid];
    child->keys[mid] = child->keys[mid+1];
    child->numKeys--;
    
    for (int j = parent->numKeys; j > i; j--) {
        parent->keys[j] = parent->keys[j-1];
    }
    
    parent->keys[i] = insertMe;
    parent->numKeys++;
    
    //add right child
    for (int j = parent->numKeys+1; j > i+1; j--) {
        parent->children[j] = parent->children[j-1];
    }
    
    parent->children[i+1] = rightChild;
    
    //check if parent is over and if so then call function
    if (parent->numKeys == m) {
        //recursive call????
        cout << "help me...\n";
    }
}

//NOT COMPLETE
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
    //WHAT IF ROOT
    if (removeMe != -1){
        if (current->isLeaf == true) {
            //delete key
            for (int i = removeMe; i < current->numKeys; i++) {
                current->keys[i] = current->keys[i+1];
            }
            current->numKeys--;
        }
        else {
            Node* child1 = current->children[removeMe];
            Node* child2 = current->children[removeMe+1];
            
            if (child1->numKeys == (m/2) && child2->numKeys == (m/2)) {
                //combine children
                for (int i = 0, j = child1->numKeys; i < child2->numKeys; i++, j++) {
                    child1[j] = child2[i];
                }
                delete [] child2;
                child2 = NULL;
            }
            else {
                //find which child has more keys
                if (child1->numKeys > child2->numKeys) {
                    current->keys[removeMe] = child1->keys[child1->numKeys-1];
                    child1->keys[child1->numKeys-1] = NULL;
                }
                else {
                    current->keys[removeMe] = child2->keys[0];
                    for (int i = child2->keys[child2->numKeys]; i > 0; i--) {
                        child2->keys[i-1] = child2->keys[i];
                    }
                }
            }
        }
    }
    else {
        cout << "key not found to remove\n";
    }
    
    print(this->root);
    cout << endl;
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

void BTree::print(Node* treeRoot)
{
//    cout << "here\n";
    for (int i = 0; i < treeRoot->numKeys; i++) {
        cout << treeRoot->keys[i];
        if (i < treeRoot->numKeys-1) {
            cout << ",";
        }
    }
    
    int i = 0;
    while (i < treeRoot->numKeys && treeRoot->depth <= height-1) {
        if (treeRoot->children != NULL) {
    //           cout << "here\n";
            cout << "[";
            print(treeRoot->children[i]);
            cout << "]";
    //            if (i == treeRoot->numKeys) {
    //                cout << "[ ";
    //                print(treeRoot->children[i+1]);
    //                cout << "] ";
    //            }
            }
        i++;
    }

    if (treeRoot->children != NULL && treeRoot->depth <= height-1) {
        cout << "[";
        print(treeRoot->children[i]);
        cout << "]";
    }
    
}

#endif /* BTree_h */
