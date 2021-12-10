
#include <iostream>
#include "ThreadedBST.h"

using namespace std;

// Driver code
int main()
{
    ThreadedBST b;
    BSTNode* root = NULL;
    b.insert(root, 5);
    b.insert(root, 3);
    b.insert(root, 2);
    b.insert(root, 4);
    b.insert(root, 7);
    b.insert(root, 6);
    b.insert(root, 8);
 
    b.insert(root, 9);
    return 0;
}
