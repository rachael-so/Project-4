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
    
    BTree tree(3);
    
    tree.insert(1);
    tree.insert(2);
    tree.insert(7);
    
    return 0;
}
