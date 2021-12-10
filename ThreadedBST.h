/**
 * skiplist.cpp
 * 
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * 
 * Created by Blake Dupar
 * 11/22/2021
 */
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

/**
 * @brief Construct a new SNode object with 
 *    value parameter and four null direction pointers
 * 
 * @param value 
 */
SNode::SNode(int value) {
  this->value = value;
  this->Next = nullptr;
  this->Prev = nullptr;
  this->Up = nullptr;
  this->Down = nullptr;
}

// array of Depth SNode* objects as FrontGuards linking levels
//SNode **FrontGuards;
// array of Depth SNode* objects as RearGuards linking levels
//SNode **RearGuards;

/**
 * @brief Construct a new Skip List:: Skip List object
 * Initializes the depth to be the desire value.
 * Creates Depth number of FrontGuards and RearGuards.
 * @param maxLevel 
 * @param probability 
 */
SkipList::SkipList(int maxLevel, int probability) {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  this->maxLevel = maxLevel;
  // Create the front and rear guards to be the desired depth
  this->FrontGuards = new SNode*[maxLevel];
  this->RearGuards = new SNode*[maxLevel];
  auto NewFront = new SNode(INT_MIN);
  auto NewBack = new SNode(INT_MAX);

  NewFront->Next = NewBack;
  NewBack->Prev = NewFront;

  this->FrontGuards[0] = NewFront;
  this->RearGuards[0] = NewBack;
  for (int Index = 1; Index < maxLevel; Index++) {
    NewFront = new SNode(INT_MIN);
    NewBack = new SNode(INT_MAX);

    NewFront->Next = NewBack;
    NewBack->Prev = NewFront;
    this->FrontGuards[Index] = NewFront;
    this->RearGuards[Index] = NewBack;

    NewFront->Down = FrontGuards[Index - 1];
    FrontGuards[Index - 1]->Up = NewFront;

    NewBack->Down = RearGuards[Index - 1];
    RearGuards[Index - 1]->Up = NewBack;
  }
}

/**
 * @brief determine if new node shuold be inserted at higher list
 * 
 * @return true if modulus of random num is less than the set probability
 */
bool SkipList::shouldInsertAtHigher() const {
  int number = rand() % 2;
    //50% chance to add to higher level
    if(number==1)
        return  true;
    return false;
}


/**
 * @brief Accepts a vector of values and attempts to insert an SNode
 * with its value in the skipList by calling the normal add method 
 * @param values 
 * @return true
 */

bool SkipList::add(const vector<int> &values) {
  for (int num : values) {
    add(num);
  }
  return true;
}

/**
 * @brief Accepts a data value and attempts to insert an SNode
 *   with its' value into the SkipList.
 * @param value 
 * @return false if the data value already exists in the list.
 */
bool SkipList::add(int value) {
  // Create a pointer to the beginning of the list
  SNode* Curr = FrontGuards[0]->Next;
  // Move forward until you find a duplicate or something greater
  while (Curr->Next != nullptr && Curr->value < value) {
    Curr = Curr->Next;
  }
  if (Curr->value == value) {
    return false;
  }
  // Make a new node and insert it into the SkipList
  SNode* NewNode = new SNode(value);
  addBefore(NewNode, Curr);

  int CurrDepth = 0;
  while (CurrDepth < maxLevel) {
  //keep looking to see if you can add to the higher level 
    if(shouldInsertAtHigher()) {
      SNode* newUpper = new SNode(value);
      newUpper->Down = NewNode;
      NewNode->Up = newUpper;

      SNode* curPtr = NewNode->Prev;
      while(curPtr == nullptr) {
        curPtr = curPtr->Prev;
      }
      curPtr = curPtr->Up;
      curPtr = curPtr->Next;
      addBefore(NewNode, curPtr);

      NewNode = newUpper;
      CurrDepth++;
    } else {
      break;
    }
  }
  return true;
}

/**
 * @brief Given a SNode, place it before the given NextNode
 * 
 * @param NewNode 
 * @param NextNode 
 */
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
  // Link next to node in front
  NewNode->Next = NextNode;
  // Link prev to node behind
  NewNode->Prev = NextNode->Prev;
  // Link node in back to new node
  NextNode->Prev->Next = NewNode;
  // Link node in front to new node
  NextNode->Prev = NewNode;
}

/**
 * @brief Destructor
 * 
 */
SkipList::~SkipList() {
  // need to delete individual nodes
  if (maxLevel == 0) return;
  //start on first element
  SNode* Curr = FrontGuards[0]->Next;
  while (Curr->Next != nullptr) {
    SNode* last = Curr;
    Curr = Curr->Next;
    delete last;
  }
  //delete last element
  delete Curr;
}

/**
 * @brief Accepts an int value and attempts to remove all nodes
 *    with data matching that value from the SkipList.
 * @param data 
 * @return true if the data value was in the list and was removed
 * @return false otherwise
 */
bool SkipList::remove(int data) {
  SNode *curPtr = FrontGuards[0]->Next;
  bool found = false;
  while (!found) {
    if (curPtr->value == data) {
      found = true;
      SNode *nodeToDeletePtr = curPtr;
      curPtr = curPtr->Next;
      //nodeToDeletePtr->value = nullptr;
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
    } else {
      curPtr = curPtr->Next;
    }    
  }
  /*if (curPtr->value = nullptr) {
    return false;
  }  */
  return true;  
}

/**
 * @brief Given a data value returns a pointer to that node in the
 *    list at the highest level.
 * @param value 
 * @return SNode*
 */
SNode *SkipList::containsSNode(int value) const {
  bool found = false;
  SNode *curPtr = FrontGuards[0];
  while(!found && curPtr != nullptr) {
    if (value == curPtr->value){
      found = true;
    } else {
      curPtr = curPtr->Next;
    }
  }  
  return curPtr;
}

/**
 * @brief Checks to see whether or not a data value exists in the list
 * 
 * @param value 
 * @return true if the value exists in the SkipList.
 * @return false otherwise
 */
bool SkipList::contains(int value) const {
  return (containsSNode(value) != nullptr);
}

/**
 * @brief Displays all the elements of the SkipList by level.
 * 
 * @param Out 
 * @param SkipL 
 * @return ostream& 
 */
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--) {
    Out << "Level " + to_string(Index) + ": ";
    auto Curr = SkipL.FrontGuards[Index]->Next;
    auto Last = SkipL.RearGuards[Index]; 
    if (Curr != nullptr && Curr != Last) {
      Out<< to_string(Curr->value);
      Curr = Curr->Next;
    }    
    while(Curr != nullptr && Curr != Last) {
      Out<< " --> " + to_string(Curr->value);
      Curr = Curr->Next;
    }
    Out << "\n";
  }
  return Out;
}
