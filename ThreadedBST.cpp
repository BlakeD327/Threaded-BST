
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

ThreadedBST::ThreadedBST(const ThreadedBST& copyTree) {
	root = nullptr;
	count = 0;
	//cheeky method for copy content
	if (copyTree.count > 0) {
		insertMultipleNodes(1, copyTree.count);
		setThread(root);
	}

}

ThreadedBST::~ThreadedBST() {
	clear(root);
}

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
			leftNode->isThreadedRight = (true);
			setThread(node->leftChildPtr);
		}
		if (!(node->isThreadedRight) && node != getFarthestRight(root)) {
			BSTNode* rightNode = getFarthestLeft(node->rightChildPtr);
			rightNode->leftChildPtr = (node);
			rightNode->isThreadedLeft = (true);
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


// In order Predecessor
BSTNode* ThreadedBST::inPred(BSTNode* ptr)
{
    if (ptr->isThreadedLeft == true)
        return ptr->leftChildPtr;
 
    ptr = ptr->leftChildPtr;
    while (ptr->isThreadedRight == false)
        ptr = ptr->rightChildPtr;
    return ptr;
}

// Returns inorder successor using left
// and right children (Used in deletion)
BSTNode* ThreadedBST::inSucc(BSTNode* ptr)
{
    if (ptr->isThreadedRight == true)
        return ptr->rightChildPtr;
 
    ptr = ptr->rightChildPtr;
    while (ptr->isThreadedLeft == false)
        ptr = ptr->leftChildPtr;
 
    return ptr;
}


bool ThreadedBST::remove(int value) {
    BSTNode *parent = nullptr, *curr = root;
    bool found = false;

    // Search value in BST : find BSTNode and its
    // parent.
    while (curr != nullptr) {
        if (value == curr->item) {
            found = true;
            break;
        }
        parent = curr;
        if (value < curr->item) {
            if (curr->isThreadedLeft == false)
                curr = curr->leftChildPtr;
            else
                break;
        }
        else {
            if (curr->isThreadedRight == false)
                curr = curr->rightChildPtr;
            else
                break;
        }
    } // end while
    // Two Children
    if (curr->isThreadedLeft == false && curr->isThreadedRight == false)
        removeCaseC(parent, curr);
 
    // Only Left Child
    else if (curr->isThreadedLeft == false)
        removeCaseB(parent, curr);
 
    // Only Right Child
    else if (curr->isThreadedRight == false)
        removeCaseB(parent, curr);
 
    // No child
    else
        removeCaseA(parent, curr);
 
    return found;
}

// Here 'parent' is pointer to parent BSTNode and 'curr' is
// pointer to current BSTNode.
void ThreadedBST::removeCaseA(BSTNode* parent, BSTNode* curr) {
    // If BSTNode to be deleted is root
    if (parent == nullptr)
        root = nullptr;
 
    // If BSTNode to be deleted is left
    // of its parent
    else if (curr == parent->leftChildPtr) {
        parent->isThreadedLeft = true;
        parent->leftChildPtr = curr->leftChildPtr;
    }
    else {
        parent->isThreadedRight = true;
        parent->rightChildPtr = curr->rightChildPtr;
    }
 
    // Free memory and return new root
    delete(curr);
}

// Here 'parent' is pointer to parent BSTNode and 'curr' is
// pointer to current BSTNode.
void ThreadedBST::removeCaseB(BSTNode* parent, BSTNode* curr)
{
    BSTNode* child;
 
    // Initialize child BSTNode to be deleted has
    // left child.
    if (curr->isThreadedLeft == false)
        child = curr->leftChildPtr;
 
    // BSTNode to be deleted has right child.
    else
        child = curr->rightChildPtr;
 
    // BSTNode to be deleted is root BSTNode.
    if (parent == nullptr)
        root = child;
 
    // BSTNode is left child of its parent.
    else if (curr == parent->leftChildPtr)
        parent->leftChildPtr = child;
    else
        parent->rightChildPtr = child;
 
    // Find successor and predecessor
    BSTNode* s = inSucc(curr);
    BSTNode* p = inPred(curr);
	 
    // If curr has left subtree.
    if (curr->isThreadedLeft == false)
        p->rightChildPtr = s;
 
    // If curr has right subtree.
    else {
        if (curr->isThreadedRight == false)
            s->leftChildPtr = p;
    }
 
    delete(curr);
}

// Here 'parent' is pointer to parent Node and 'curr' is
// pointer to current Node.
void ThreadedBST::removeCaseC(BSTNode* parent, BSTNode* curr) {

    // Find inorder successor and its parent.
    BSTNode* parsucc = curr;
    BSTNode* succ = curr->rightChildPtr;
 
    // Find leftmost child of successor
    while (succ->isThreadedLeft==false) {
        parsucc = succ;
        succ = succ->leftChildPtr;
    }
 
    curr->item = succ->item;
 
    if (succ->isThreadedLeft == true && succ->isThreadedRight == true)
        removeCaseA(parsucc, succ);
    else
        removeCaseB(parsucc, succ);
}
