//
//  main.cpp
//  p4
//
//  Created by Rachael So on 11/10/17.
//  Copyright © 2017 Rachael So. All rights reserved.
//

#include <iostream>
#include "BTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    BTree tree(5);
    
    tree.insert(2);
    tree.insert(3);
    tree.insert(11);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    tree.insert(32);
    tree.insert(20);
    tree.insert(100);
    tree.insert(23);
    tree.insert(93);
    tree.insert(27);
    tree.insert(99);
    tree.insert(6);
    tree.insert(4);
    tree.insert(5);
//    tree.insert(40);
    
    
    return 0;
}
