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

/*Set number of nodes
//Set number of nodes
ThreadedBST::ThreadedBST(const int& numOfNodes) {
	root = nullptr;
	count = 0;
	if (numOfNodes >= 1) {
		insertMultipleNodes(1, numOfNodes);
		setThread(root);
	}
}*/

ThreadedBST::~ThreadedBST() {
	clear(root);
}


 //MINE
BSTNode* ThreadedBST::insert(BSTNode* node, const int& newItem) {
	// if the tree is empty, create a new node and set it as root
	if (root == nullptr) {
		root = new BSTNode(newItem);
		return root;
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
		if (newItem < curr->item) {
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
	BSTNode* newNode = new BSTNode(newItem);
	newNode->isThreadedRight = newNode->isThreadedLeft = true;
	if (newItem < parent->item) {
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
	return node;
}


/**
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
*/

void ThreadedBST::insert(const int& newItem) {
	insert(root, newItem);
}
/** new inserts
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
	//checks if node exists
	if (node != nullptr) {
		//checks if left thread exists and node isn't farthest left
		if (!(node->isThreadedLeft) && node != getFarthestLeft(root)) {
			//Sets Values if so
			BSTNode* leftTempNode = getFarthestRight(node->leftChildPtr);
			leftTempNode->rightChildPtr = node;
			leftTempNode->isThreadedRight = true;
			//Recursively sets left child
			setThread(node->leftChildPtr);
		}
		//Checks if right thread exissts and node isn't farthest left
		if (!(node->rightChildPtr) && node != getFarthestRight(root)) {
			//Sets Values if so
			BSTNode* rightTempNode = getFarthestLeft(node->rightChildPtr);
			rightTempNode->leftChildPtr = node;
			rightTempNode->isThreadedLeft= true;
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
*/

int ThreadedBST::getDepth() const {
	return log2(count + 1);
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


bool ThreadedBST::hasLeftChild(BSTNode* targetNode) {
	BSTNode* temp = targetNode;
	return(!temp->isThreadedLeft && temp->leftChildPtr != nullptr);
}

bool ThreadedBST::hasRightChild(BSTNode* targetNode) {
	BSTNode* temp = targetNode;
	return(!temp->isThreadedRight && temp->rightChildPtr != nullptr);
}

/**
 * Calls the real recursive in order traversal and hands it the tree's root
 */
void ThreadedBST::Inorder() {
	recInorder(root);
}

/**
 * Main recursive function for in order.
 * The recursive function calls on print nodes to handle printing.
 * @param root - the ThreadedBST tree for traversal
 * @param printCount - count of elements */
void ThreadedBST::recInorder(BSTNode* root) {
    // as long as the root is not null, recurses left children, then right children
    if(root != NULL)
    {
        if(hasLeftChild(root)) {
            recPreOrder(root->leftChildPtr);
        }
        //printNodes(&root);
		cout << root->item << endl;
        if(hasRightChild(root)) {
            recPreOrder(root->rightChildPtr);
        }        
    }
}

/**
 * Calls the real recursive pre order traversal and hands it the tree's root
 */
void ThreadedBST::PreOrder(){
    recPreOrder(root);
}

/**
 * Main recursive function for preorder.
 * The recursive function calls on print nodes to handle printing.
 * @param root - the ThreadedBST tree for traversal
 * @param printCount - count of elements
 */
void ThreadedBST::recPreOrder(BSTNode* root) {
    // as long as the root is not null, recurses left children, then right children
    if(root != NULL) {
        //printNodes(&root);  
		cout << root->item << endl;      
        if(hasLeftChild(root)) {
            recPreOrder(root->leftChildPtr);
        }        
        if(hasRightChild(root)) {
            recPreOrder(root->rightChildPtr);
        }
    }
}

/**
void ThreadedBST::Inorder() {
	//recInorder(root);
	if (root == nullptr) {
		return;
	}
	BSTNode* curr = root;
	while(curr->leftChildPtr != nullptr) {
		curr = curr->leftChildPtr;
	}
	while (curr != nullptr) {
		cout << curr->item << endl;
		curr = curr->rightChildPtr;
	}
}
*/
/**
void ThreadedBST::recInorder(BSTNode* root) {
	if (root == nullptr) {
		return;
	}	
}*/
