
//
//  main.cpp
//  p4
//
//  Created by Rachael So on 11/10/17.
//  Copyright © 2017 Rachael So. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "BTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string fName = argv[1];
    ifstream inputFile;
    
    if (argc < 2) {
        cout << "ERROR: NEED INPUT FILE";
    }
    else {
        //start of program
        //get file from command line argument
        inputFile.open(fName.c_str());
        
        //check if file opens
        if (!inputFile) {
            cout << "Failed to open file" << endl;
        }
        else if (inputFile) {
//            cout << "opened file!" << endl;
            
            string num;
            int m;
            int key;
            
            getline(inputFile, num);
            istringstream iss(num);
            iss >> m;
            
    BTree tree(m);
            
//            while (inputFile >> key) {
//                tree.insert(key);
//            }
//            tree.print(tree.root);
//            cout << endl;
    
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
            tree.insert(40);
            tree.insert(50);
        }
    }
    
    return 0;
}
