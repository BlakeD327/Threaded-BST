
#include <iostream>
#include "ThreadedBST.h"

using namespace std;

// Driver code
int main()
{

    //Demo Test
    ThreadedBST test1(35);
    cout << test1.getDepth() << endl;
    test1.inorder();
    cout << endl;

    ThreadedBST b;
    b.insert(5);
    b.insert(3);
    b.insert(2);
    b.insert(4);
    b.insert(7);
    b.insert(6);
    b.insert(8);

    b.inorder();
    return 0;
}
