#include <iostream>
#include <iomanip>

template <class ItemType> struct BSTNode
{
private:
  ItemType item; //Value
  BSTNode <ItemType> *leftChildPtr; //Left Pointer
  BSTNode <ItemType> *rightChildPtr; //Right Pointer
  bool isThreadedLeft;	//Bool of left Thread
  bool isThreadedRight;	//Bool of Right Thread

};

using namespace std;

class ThreadedBST {	
	friend ostream &operator<<(ostream &out, const SkipList &skip);

	// Parameterized constructor
	ThreadedBST(int rootItem);

	//This is a different method from the one above, This one creates n number of nodes
	//in nonincremental order
	ThreadedBST(const int &n);

  	//Destructor
  	~ThreadedBST();

 	//Get Depth
  	int getDepth() const;

	// Insert function
	ThreadedBST* Insert(ThreadedBST* root, ItemType value);

	// Completes an inorder traversal of the threaded BST
	void Inorder(ThreadedBST* root);

	// Remove
	void remove(tbst<ItemType> *node, ItemType value);

	// Copy
	ThreadedBST(const ThreadedBST<ItemType> &tree);

	// Remove Even
	void removeEven();
	
	//We'll have to pick between these two, I have no preferance but if we're in the Tree we have access to the root already.

 	//Inorder Traverse for testing
 	void inorderTraverse();

	// Completes an inorder traversal of the threaded BST
	void Inorder(ThreadedBST* root);

	// Clear
	void clear();

};
