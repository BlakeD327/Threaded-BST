/**
 * @file ThreadedBST.cpp
 * @author Group: Jaylon Nelson-Sellers, Jeff Kern, Blake Dupar
 * @brief An implementation file for a threaded binary search tree. Creates a binary 
 *  search tree and threads	together nodes in inorder succession using pointers. 
 * @version 0.1
 * @date 2021-12-11
 * 
 */

#include <iostream>
#include <math.h>
#include "ThreadedBST.h"

using namespace std;

/**
 * @brief Construct a new BSTNode object
 * @param item 
 */
BSTNode::BSTNode(int item) {
	this->item = item;
	this->leftChildPtr = nullptr;
	this->rightChildPtr = nullptr;
	this->isThreadedLeft = false;
	this->isThreadedRight = false;
}

/**
 * @brief Construct a new ThreadedBST object
 */
ThreadedBST::ThreadedBST() {
	root = nullptr;
	count = 0;
}


/**
 * @brief Construct a new ThreadedBST object
 * @param numOfNodes 
 */
ThreadedBST::ThreadedBST(const int& numOfNodes) {
	root = nullptr;
	count = 0;
	if (numOfNodes >= 1) {
		insertMultipleNodes(1, numOfNodes);
		setThread(root);
	}
}

/**
 * @brief Construct a new ThreadedBST object by copying the given tree
 * @param copyTree 
 */
ThreadedBST::ThreadedBST(const ThreadedBST& copyTree) {
	root = nullptr;
	count = 0;
	//cheeky method for copy content
	if (copyTree.count > 0) {
		insertMultipleNodes(1, copyTree.count);
		setThread(root);
	}
}

/**
 * @brief Destroy the ThreadedBST object
 */
ThreadedBST::~ThreadedBST() {
	clear(root);
}

/**
 * @brief passes to the insert function a number of values
 * @param min the minimum passed value
 * @param max the maximum passed value
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

/**
 * @brief Inserts a value into the tbst by inserting a node into the tree recursively
 * @param newItem the value to be inserted into the tree
 */
void ThreadedBST::insert(const int& newItem) {
	insert(root, newItem);
}

/**
 * @brief Inserts a value into the tbst by inserting a node into the tree recursively
 * @param node the BSTNode object
 * @param newItem the value to be inserted into the tree
 * @return BSTNode* 
 */
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

/**
 * @brief attaches thread pointers to nodes
 * @param node the BSTNode object
 */
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

/**
 * @brief returns the most left node in the tree
 * @param node the BSTNode object
 * @return BSTNode* 
 */
BSTNode* ThreadedBST::getFarthestLeft(BSTNode* node) const {
	//checks if Node is null
	if (node == nullptr)
		return nullptr;
	//Goes as far left as possible
	while (node->leftChildPtr != nullptr && !(node->isThreadedLeft))
		node = node->leftChildPtr;
	return node;
}

/**
 * @brief returns the most right node in the tree
 * @param node the BSTNode object
 * @return BSTNode* 
 */
BSTNode* ThreadedBST::getFarthestRight(BSTNode* node) const {
	//checks if Node is null
	if (node == nullptr)
		return nullptr;
	//Goes as far right as possible
	while (node->rightChildPtr != nullptr && !(node->isThreadedRight))
		node = node->rightChildPtr;

	return node;
}

/**
 * @brief returns the depth of the tree
 * @return int 
 */
int ThreadedBST::getDepth() const {
	return log(count + 1);
}

/**
 * @brief prints the inorder traversal of the tbst
 */
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

/**
 * @brief clear function for the tbst. Deletes a all nodes and set current to root
 * @param node the BSTNode object
 */
void ThreadedBST::clear(BSTNode* node) {
	//Case 1: Node is not empty
	if (node != nullptr) {
		//Case 1.A: Node has left Child
		if (!(node->isThreadedLeft)) {
			//Recursively clears left child
			clear(node->leftChildPtr);		}
		//Case 1.B: Node has right Child
		if (!(node->isThreadedRight)) {
			//Recursively clears right child
			clear(node->rightChildPtr);		}
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

/**
 * @brief returns inorder successor predecessor
 * @param curr the current node
 * @return BSTNode* 
 */
BSTNode* ThreadedBST::inPred(BSTNode* curr) {
    if (curr->isThreadedLeft == true)
        return curr->leftChildPtr; 
    curr = curr->leftChildPtr;
    while (curr->isThreadedRight == false)
        curr = curr->rightChildPtr;
    return curr;
}

/**
 * @brief returns inorder successor using left and right children (Used in deletion)
 * @param curr the current node
 * @return BSTNode* 
 */
BSTNode* ThreadedBST::inSucc(BSTNode* curr) {
    if (curr->isThreadedRight == true)
        return curr->rightChildPtr;
 
    curr = curr->rightChildPtr;
    while (curr->isThreadedLeft == false)
        curr = curr->leftChildPtr;
    return curr;
}

/**
 * @brief delete function for the tbst.
 * 		locates the node to be deleted by the value and calls the function to delete it 
 * @param value the value of the node being removed
 * @return true 
 * @return false 
 */
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

/**
 * @brief remove case for a leaf node
 * @param parent pointer to parent BSTNode
 * @param curr pointer to current BSTNode
 */
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

/**
 * @brief remove case for a node with only one child
 * @param parent pointer to parent BSTNode
 * @param curr pointer to current BSTNode
 */
void ThreadedBST::removeCaseB(BSTNode* parent, BSTNode* curr) {
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

/**
 * @brief remove case for a node with 2 children
 * @param parent pointer to parent BSTNode
 * @param curr pointer to current BSTNode
 */
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
