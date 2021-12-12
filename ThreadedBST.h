/**
 * @file ThreadedBST.h
 * @author Group: Jaylon Nelson-Sellers, Jeff Kern, Blake Dupar
 * @brief A header file for a threaded binary search tree. Creates a binary 
 *  search tree and threads	together nodes in inorder succession using pointers. 
 * @version 0.1
 * @date 2021-12-11
 * 
 */

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
	explicit ThreadedBST();

	ThreadedBST(const int& n);

	ThreadedBST(const ThreadedBST& tree);

	virtual ~ThreadedBST();
	
	void insertMultipleNodes(const int& min, const int& max);

	void insert(const int& item);

	BSTNode* insert(BSTNode* node, const int& data);

	void setThread(BSTNode* node);

	BSTNode* getFarthestLeft(BSTNode* node) const;

	BSTNode* getFarthestRight(BSTNode* node) const;

	void inorder();

	int getDepth() const;

	void clear(BSTNode* node);

	bool remove(int value);

	void removeCaseA(BSTNode* parent, BSTNode* curr);

	void removeCaseB(BSTNode* parent, BSTNode* curr);

	void removeCaseC(BSTNode* parent, BSTNode* curr);

	BSTNode* inSucc(struct BSTNode* curr);

	BSTNode* inPred(struct BSTNode* curr);
};
#endif
