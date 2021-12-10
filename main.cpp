
#include <iostream>
#include "ThreadedBST.h"

using namespace std;

// Driver code
int main()
{
    ThreadedBST b;
    BSTNode* root = NULL;
    b.Insert(5);
    b.Insert(3);
    b.Insert(2);
    b.Insert(4);
    b.Insert(7);
    b.Insert(6);
    b.Insert(8);
 
    b.Inorder(root);
    return 0;
}
