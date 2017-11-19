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
    
    return 0;
}
