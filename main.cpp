/**
 * @file main.cpp
 * @author Group: Jaylon Nelson-Sellers, Jeff Kern, Blake Dupar
 * @brief An driver file for a threaded binary search tree. Creates a binary 
 *  search tree and threads	together nodes in inorder succession using pointers. 
 * @version 0.1
 * @date 2021-12-11
 * 
 */

#include <iostream>
#include "ThreadedBST.h"

using namespace std;

// Driver code
int main(int argc, char** argv)
{
    ThreadedBST testArgs(atoi(argv[0]));
    testArgs.inorder();


    //Demo Test
    ThreadedBST test1(35);
    cout << test1.getDepth() << endl;
    test1.inorder();
    cout << endl << endl;


    cout << "Begin removing evens: " << endl;
    // For loop to remove evens
    for (int i = 2; i <= 35 ; i++) {
        test1.remove(i);
        test1.inorder();
        cout << endl;
        i++;
    }


    // ThreadedBST b;
    // b.insert(5);
    // b.insert(3);
    // b.insert(2);
    // b.insert(4);
    // b.insert(7);
    // b.insert(6);
    // b.insert(8);
    // b.inorder();
    // cout << endl;
    // b.remove(4);
    // b.inorder();
    cout << endl;

    return 0;
}
