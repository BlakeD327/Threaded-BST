
#include <iostream>
#include <math.h>
#include "ThreadedBST.h"

using namespace std;

BSTNode::BSTNode(int item) {
	this->item = item;
	this->leftChildPtr = nullptr;
	this->rightChildPtr = nullptr;
	this->isThreadedLeft = false;
	this->isThreadedRight = false;
}

ThreadedBST::ThreadedBST() {
	root = nullptr;
	count = 0;
}

//Set number of nodes
ThreadedBST::ThreadedBST(const int& numOfNodes) {
	root = nullptr;
	count = 0;
	if (numOfNodes >= 1) {
		insertMultipleNodes(1, numOfNodes);
		setThread(root);
	}
}

ThreadedBST::~ThreadedBST() {
	clear(root);
}

/**
void ThreadedBST::Insert(const int& item) {
	// if the tree is empty, create a new node and set it as root
	if (root == nullptr) {
		root = new BSTNode(item);
		return;
	}
	// start with the root node
	BSTNode* curr = root;
	// pointer to store the parent of the current node
	BSTNode* parent = nullptr;

	// traverse the tree and find the parent node of the given item
	while (curr != nullptr) {
		// update the parent to the current node
		parent = curr;

		// if the given item is less than the current node, go to the
		// left subtree; otherwise, go to the right subtree.
		if (item < curr->item) {
			if (curr->isThreadedLeft == true) {
				break;
			}
			else {
				curr = curr->leftChildPtr;
			}
		}
		else {
			if (curr->isThreadedRight == true) {
				break;
			}
			else {
				curr = curr->rightChildPtr;
			}
		}
	} //end while loop

	// construct a node and assign it to the appropriate parent pointer
	BSTNode* newNode = new BSTNode(item);
	newNode->isThreadedRight = newNode->isThreadedLeft = true;

	if (item < parent->item) {
		//set newNode's left ptr to its parent's old left ptr
		newNode->leftChildPtr = parent->leftChildPtr;
		//newNode's right ptr points back at parent
		newNode->rightChildPtr = parent;
		//parent points to newNode
		parent->leftChildPtr = newNode;
		//set parent's isThreadedLeft(bool) to false as it now has
		// a lwft node
		parent->isThreadedLeft = false;
	}
	else {
		newNode->rightChildPtr = parent->rightChildPtr;
		newNode->leftChildPtr = parent;
		parent->rightChildPtr = newNode;
		parent->isThreadedRight = false;
	}
}

*/

void ThreadedBST::insertMultipleNodes(const int& min, const int& max) {
	int middle = (min + max) / 2;
	//recursive case
	if (middle != min && middle != max) {
		insert(middle);
		insertMultipleNodes(min, middle - 1);
		insertMultipleNodes(middle + 1, max);
	}
	//Base Case if either the min or max is reached
	else {
		insert(max);
		if (min != max) {
			insert(min);
		}
	}
}

void ThreadedBST::insert(const int& newItem) {
	insert(root, newItem);
}

BSTNode* ThreadedBST::insert(BSTNode* node, const int& newItem) {
	//Case 1: If the tree is empty, return a single new
	if (node == nullptr) {
		count++;
		if (root == nullptr) {
			root = new BSTNode(newItem);
			return root;
		}
		return new BSTNode(newItem);
	}
	BSTNode* tempNode = nullptr;

	//Case 2: Go recursively through the tree
	if (newItem < node->item) {
		tempNode = insert(node->leftChildPtr, newItem);
		node->leftChildPtr = tempNode;
	}
	else {
		tempNode = insert(node->rightChildPtr, newItem);
		node->rightChildPtr = tempNode;
	}

	return node;
}


void ThreadedBST::setThread(BSTNode* node) {
	if (node != nullptr) {
		if (!(node->isThreadedLeft) && node != getFarthestLeft(root)) {
			BSTNode* leftNode = getFarthestRight(node->leftChildPtr);
			leftNode->rightChildPtr = (node);
			leftNode->isThreadedRight=(true);
			setThread(node->leftChildPtr);
		}
		if (!(node->isThreadedRight) && node != getFarthestRight(root)) {
			BSTNode* rightNode = getFarthestLeft(node->rightChildPtr);
			rightNode->leftChildPtr=(node);
			rightNode->isThreadedLeft= (true);
			setThread(node->rightChildPtr);
		}
	}
}


BSTNode* ThreadedBST::getFarthestLeft(BSTNode* node) const {
	//checks if Node is null
	if (node == nullptr)
		return nullptr;

	//Goes as far left as possible
	while (node->leftChildPtr != nullptr && !(node->isThreadedLeft))
		node = node->leftChildPtr;

	return node;
}

BSTNode* ThreadedBST::getFarthestRight(BSTNode* node) const {
	//checks if Node is null
	if (node == nullptr)
		return nullptr;

	//Goes as far right as possible
	while (node->rightChildPtr != nullptr && !(node->isThreadedRight))
		node = node->rightChildPtr;

	return node;

}

int ThreadedBST::getDepth() const {
	return log(count + 1);
}


void ThreadedBST::inorder() {
	setThread(root);
	BSTNode* current = getFarthestLeft(root);
	while (current != NULL) {
		printf("%d ", current->item);

		// If this node is a thread node, then go to
		// inorder successor
		if (current->isThreadedRight)
			current = current->rightChildPtr;
		else // Else go to the leftmost child in right
			 // subtree
			current = getFarthestLeft(current->rightChildPtr);
	}
}

void ThreadedBST::clear(BSTNode* node) {
	//Case 1: Node is not empty
	if (node != nullptr) {
		//Case 1.A: Node has left Child
		if (!(node->isThreadedLeft)) {
			//Recursively clears left child
			clear(node->leftChildPtr);
		}

		//Case 1.B: Node has right Child
		if (!(node->isThreadedRight)) {
			//Recursively clears right child
			clear(node->rightChildPtr);
		}

		//Deletes children
		node->leftChildPtr = nullptr;
		node->rightChildPtr = nullptr;

		//Case 1.C: Node has no pointers
		if (node->leftChildPtr == nullptr &&
			node->rightChildPtr == nullptr) {
			delete node;
			node = nullptr;
		}
	}
}
