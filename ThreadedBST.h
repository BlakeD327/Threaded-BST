#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <iostream>
#include <iomanip>

using namespace std;

class BSTNode {
	friend class ThreadedBST;
private:
	explicit BSTNode(int item);
	int item; //Value
	BSTNode* leftChildPtr; //Left Pointer
	BSTNode* rightChildPtr; //Right Pointer
	bool isThreadedLeft;	//Bool of left Thread
	bool isThreadedRight;	//Bool of Right Thread
};

class ThreadedBST {
	//friend ostream& operator<<(ostream& out, const ThreadedBST& tree);

private:
	BSTNode* root = nullptr;
	int count;

public:
	// Parameterized constructor
	explicit ThreadedBST();

	//This is a different method from the one above, 
	// This one creates n number of nodes
	//  in nonincremental order
	ThreadedBST(const int& n);

	//Destructor
	virtual ~ThreadedBST();

	void insertMultipleNodes(const int& min, const int& max);

	BSTNode* insert(BSTNode* node, const int& data);



	// Insert function
	//void Insert(const int& item);

	void setThread(BSTNode* node);

	BSTNode* getFarthestLeft(BSTNode* node) const;

	BSTNode* getFarthestRight(BSTNode* node) const;

	// Remove
	void remove(BSTNode& node, int value);

	// Copy
	ThreadedBST(const ThreadedBST& tree);

	// Remove Even
	void removeEven();

	//void Inorder();

	// Completes an inorder traversal of the threaded BST
	//void Inorder(BSTNode* node);

	//Get Depth
	int getDepth() const;

	// Clear
	void clear(BSTNode* node);
};
#endif
