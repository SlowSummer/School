// Implementation file for the NumberList class
#include <iostream>  // For cout  and NULL
#include "NumberList.h"
using namespace std;

//**************************************************
// appendNode appends a node containing the        *
// value pased into num, to the end of the list.   *
//**************************************************

void NumberList::appendNode(double num)
{
   ListNode *newNode;  // To point to a new node
   ListNode *nodePtr;  // To move through the list

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = num;
   newNode->next = NULL;

   // If there are no nodes in the list
   // make newNode the first node.
   if (head == NULL) // or !head
      head = newNode;
   else  // Otherwise, insert newNode at end.
   {
      // Initialize nodePtr to head of list.
      nodePtr = head;

      // Find the last node in the list.
      while (nodePtr->next) // or nodePtr->next != NULL
         nodePtr = nodePtr->next;

      // Insert newNode as the last node.
      nodePtr->next = newNode;
   }
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************

void NumberList::displayList() const
{
   ListNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      cout << nodePtr->value << endl;

      // Move to the next node.
      nodePtr = nodePtr->next;
   }
}

//**************************************************
// The insertNode function inserts a node with     *
// num copied to its value member.                 *
//**************************************************

void NumberList::insertNode(double num)
{
   ListNode *newNode;             // A new node
   ListNode *nodePtr;             // To traverse the list
   ListNode *previousNode = NULL; // The previous node

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = num;
   
   // If there are no nodes in the list
   // make newNode the first node
   if (head == NULL)
   {
      head = newNode;
      newNode->next = NULL;
   }
   else  // Otherwise, insert newNode
   {
      // Position nodePtr at the head of list.
      nodePtr = head;

      // Initialize previousNode to NULL.
      previousNode = NULL;

      // Skip all nodes whose value is less than num.
      while (nodePtr != NULL && nodePtr->value < num)
      {  
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If the new node is to be the 1st in the list,
      // insert it before all other nodes.
      if (previousNode == NULL)
      {
         head = newNode;
         newNode->next = nodePtr;
      }
      else  // Otherwise insert after the previous node.
      {
         previousNode->next = newNode;
         newNode->next = nodePtr;
      }
   }
}

//**************************************************
// The deleteNode function searches for a node     *
// with num as its value. The node, if found, is   *
// deleted from the list and from memory.          *
//**************************************************

void NumberList::deleteNode(double num)
{
   ListNode *nodePtr;       // To traverse the list
   ListNode *previousNode = NULL;  // To point to the previous node

   // If the list is empty, do nothing.
   if (head == NULL)
      return;
   
   // Determine if the first node is the one.
   if (head->value == num)
   {
      nodePtr = head->next;
      delete head;
      head = nodePtr;
   }
   else
   {
      // Initialize nodePtr to head of list
      nodePtr = head;

      // Skip all nodes whose value member is 
      // not equal to num.
      while (nodePtr != NULL && nodePtr->value != num)
      {  
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If nodePtr is not at the end of the list, 
      // link the previous node to the node after
      // nodePtr, then delete nodePtr.
      if (nodePtr)
      {
         previousNode->next = nodePtr->next;
         delete nodePtr;
      }
   }
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

NumberList::~NumberList()
{
   ListNode *nodePtr;   // To traverse the list
   ListNode *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != NULL)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}


//**************************************************
// TO DO: The copy constructor function            *
// This function copies the list correctly	   *
//**************************************************
NumberList::NumberList(const NumberList& origList)
{
    ListNode* currNode;
    ListNode* nextNode;
    
    if (origList.head == NULL)
    {
        head = NULL;
    }
    else
    {
        head = new ListNode;
        head->value = origList.head->value;
        
        currNode = head;
        nextNode = origList.head->next;

        //Copy remaining nodes
        while (nextNode)
        {
            currNode->next = new ListNode;
            currNode = currNode->next;
            currNode->value = nextNode->value;

            nextNode = nextNode->next;
        }

        //Set the tail node
        currNode->next = NULL;
    }
}


//**************************************************
// TO DO: Overload the default assignment operator *
// This function assigns a list correctly	   *
//**************************************************
NumberList& NumberList::operator=(const NumberList& listToCopy)
{
    //Ptrs to travers new list
    ListNode* currNode;
    ListNode* nextNode;

    //Ptrs to travers previous list
    const ListNode* copyCurrNode;
    const ListNode* copyNextNode;

    //Return if list is the same
    if (this == &listToCopy)
    {
        return *this;
    }

    //Delete original nodes
    currNode = this->head;

    while (currNode)
    {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

    //Return if listToCopy is NULL
    if (listToCopy.head == NULL)
    {
        head = NULL;

        return *this;
    }

    //Initialize pointers to listToCopy
    copyCurrNode = listToCopy.head;
    copyNextNode = listToCopy.head->next;

    //Create new head
    this->head = new ListNode;
    this->head->value = copyCurrNode->value;

    //Iterate the next node to copy
    copyCurrNode = copyNextNode;


    //Set currNode to list head
    currNode = this->head;

    //Copy remaining nodes
    while (copyCurrNode)
    {
        //Itterate copyNextNode
        copyNextNode = copyNextNode->next;

        currNode->next = new ListNode;
        currNode = currNode->next;
        currNode->value = copyCurrNode->value;

        copyCurrNode = copyNextNode;
    }

    //Sets tail to NULL
    currNode->next = NULL;

    return *this;
}

