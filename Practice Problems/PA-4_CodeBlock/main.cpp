// Author : Andrew Bracken
//
// Serial Number / s : 6
//
// Programming Assignment Number 4
//
// Fall 2023 - CS 3358 - 1
//
// Due Date : 10/16/2023
//
// Instructor: Husain Gholoom.
//
// Program implements a linked list stack and queue and preforms
// various functions to manipulate each.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>

using namespace std;


struct Node
{
	char data;
	Node* link;
};

class Stack
{
private:
	Node* head;
	Node* tail;

public:
	Stack();
	~Stack();
	void push(char);
	void pop();
	void removeW();
	void display();
	bool isEmpty();
};

class Queue
{
private:
	Node* head;
	char min;
	char max;

public:
	Queue();
	~Queue();
	void enqueue(char);
	void dequeue(int);
	void insert(char, int);
	void removeX();
	void display();
	void findMinMax();
	bool isEmpty();
};

bool checkChoiceRange(char&);
char getUserChoice();


int main()
{
	char userChoice = NULL; // char representing user's choice

	Queue q; // queue being manipulated
	Stack s; // stack being manipulated

	srand(time(NULL)); //seed rand with time

	cout << "Welcome to Linked List- Stack / Queue program.\n\n";

	while (userChoice != 'X' && userChoice != 'x')
	{
		cout << "Please select one of the following: \n";

		cout << "\tA. Build a stack that consist of 5 random capital"
			<< " letters\n\t   that are >= 'C' and <= 'K'\n";
		cout << "\tB. Build a queue that consist of 5 random capital"
			<< " letters\n\t   that are >= 'H' and <= 'S'\n";
		cout << "\tC. Insert the element 'W' in the stack (LIFO).\n";
		cout << "\tD. Insert the element 'X' in the stack (LIFO).\n";
		cout << "\tE. Remove and element from the stack (LIFO).\n";
		cout << "\tF. Insert the element 'X' in the queue (FIFO).\n";
		cout << "\tG. Insert an element 'A' in the 2nd location in"
			<< "the queue.\n";
		cout << "\tH. Remove the first element from the queue (FIFO)\n";
		cout << "\tI. Remove the 4the element from the queue\n";
		cout << "\tJ. Find Min element in the queue, and Max element in the"
			<< "\n\t   queue.\n";
		cout << "\tK. Delete the entire stack.\n";
		cout << "\tL. Remove 'W' from the stack.\n";
		cout << "\tM. Delete the entire queue.\n";
		cout << "\tN. Remove an 'X' from the queue.\n";
		cout << "\tX. Exit the program.\n\n";

		userChoice = getUserChoice();

		switch (userChoice)
		{
		case 'A':
			if (s.isEmpty())
			{
				for (int i = 0; i < 5; i++)
				{
					char randChar = rand() % 9 + 67;
					s.push(randChar);
				}

				s.display();
			}
			else
			{
				s.~Stack();

				for (int i = 0; i < 5; i++)
				{
					char randChar = rand() % 9 + 67;
					s.push(randChar);
				}

				s.display();
			}
			break;

		case 'B':
			if (q.isEmpty())
			{
				for (int i = 0; i < 5; i++)
				{
					char randChar = rand() % 12 + 72;
					q.enqueue(randChar);
				}

				q.display();
			}
			else
			{
				q.~Queue();

				for (int i = 0; i < 5; i++)
				{
					char randChar = rand() % 12 + 72;
					q.enqueue(randChar);
				}

				q.display();
			}
			break;

		case 'C':
			s.push('W');

			s.display();

			break;

		case 'D':
			s.push('X');

			s.display();

			break;

		case 'E':
			s.pop();

			break;

		case 'F':
			q.enqueue('X');

			q.display();

			break;

		case 'G':
			q.insert('A', 1);

			q.display();

			break;

		case 'H':
			q.dequeue(0);

			break;

		case 'I':
			q.dequeue(3);

			break;

		case 'J':
			q.findMinMax();

			break;

		case 'K':
			if (s.isEmpty())
			{
				cout << "ERROR: Stack is already empty\n\n";
			}
			else
			{
				s.~Stack();

				s.display();
			}

			break;

		case 'L':
			s.removeW();

			s.display();

			break;

		case 'M':
			if (q.isEmpty())
			{
				cout << "ERROR: Queue is already empty\n\n";
			}
			else
			{
				q.~Queue();

				q.display();
			}

			break;

		case 'N':
			q.removeX();

			break;

		case 'X':
			break;

		default:
			break;
		}
	}

	cout << "Linked List, Stack, Queue Operations\n\n"
		<< ".\n.\n.\n\n\nLL / Stack & Queue Program is implemented"
		<< " By :\nAndrew Bracken - October 16th, 2023";

	return 0;
}

bool checkChoiceRange(char &choice)
{
	choice = toupper(choice); //convert to uppercase

	if (!isalpha(choice))
	{
		return false;
	}
	else if(choice > 'N' && choice != 'X')
	{
		return false;
	}
	else
	{
		return true;
	}
}

char getUserChoice()
{
	char choice;

	cout << "Enter your choice:";
	cin >> setw(1) >> choice;
	cout << "\n\n";

	while (!cin.good() || !checkChoiceRange(choice))
	{
		// error message
		cout << "ERROR: Choice must be a single character A-N or "
			<< "X to exit.\n\n";

		// clear in stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		// prompt input again
		cout << "Enter your choice:";
		cin >> setw(1) >> choice;
		cout << "\n\n";
	}

	// clear in stream
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}


Stack::Stack()
{
	head = NULL;
	tail = NULL;
}

Stack::~Stack()
{
	Node* temp = head;

	while (temp != 0)
	{
		Node* next = temp->link;
		delete temp;
		temp = next;
	}

	head = 0;
	tail = 0;
}

void Stack::push(char data)
{
	Node* newNode = new Node; // pointer to node being inserted
	newNode->data = data;
	newNode->link = NULL;

	if (head == 0) // stack is empty
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->link = newNode;
		tail = tail->link;
	}
}

void Stack::pop()
{
	if (head == 0) // error if stack is empty
	{
		cout << "ERROR: Stack is empty\n\n";
		return;
	}

	if (head == tail) // last element of stack
	{
		head = NULL;

		this->display();

		return;
	}

	Node* cursor = head; // pointer to traverse stack
	Node* temp = tail; // target node

	while (cursor->link != temp)
	{
		cursor = cursor->link;
	}

	delete temp;

	cursor->link = NULL;

	tail = cursor;

	this->display();
}

void Stack::removeW()
{
	if (head == 0) // stack is empty
	{
		cout << "ERROR: Stack is empty.\n\n";
		return;
	}

	if (tail->data == 'W') // if tail is a W
	{
		Node* cursor = head; // pointer used to traverse the list

		while (cursor->link != tail)
		{
			cursor = cursor->link;
		}

		delete tail;

		cursor->link = NULL;

		tail = cursor;

		return;
	}

	Node* cursor = head; // pointer used to traverse the list
	Node* previous = head; // pointer representing the node before target
	Node* target = NULL; // pointer to the last W in the stack

	while (cursor != tail)
	{
		if (cursor->data == 'W')
		{
			target = cursor;
		}

		cursor = cursor->link;
	}

	if (target == 0) // return if no W's in the stack
	{
		return;
	}

	while (previous->link != target) // itterate to node before target
	{
		previous = previous->link;
	}

	previous->link = target->link;

	delete target;
}

void Stack::display()
{

	if (head == 0) // check if stack is empty
	{
		cout << "Stack: Empty\n\n";
		return;
	}

	cout << "Stack: ";

	Node* cursor = head; // pointer used to traverse the queue

	while (cursor->link != 0)
	{
		cout << cursor->data << " ";

		cursor = cursor->link;
	}

	cout << cursor->data << "\n\n";
}

bool Stack::isEmpty()
{
	if (head == 0)
	{
		return true;
	}
	{
		return false;
	}
}


Queue::Queue()
{
	head = NULL;
	min = 'S'; // initialize to max possible value
	max = 'H'; // initialize to min possible value
}

Queue::~Queue()
{
	Node* temp = head;

	while (temp != 0)
	{
		Node* next = temp->link;
		delete temp;
		temp = next;
	}

	head = 0;
	min = NULL;
	max = NULL;
}

void Queue::enqueue(char data)
{
	Node* newNode = new Node; // pointer to node being inserted
	newNode->data = data;
	newNode->link = NULL;

	if (this->isEmpty()) // stack is empty
	{
		head = newNode;
	}
	else
	{
		Node* cursor = head; // pointer used to traverse the queue

		while (cursor->link != 0)
		{
			cursor = cursor->link;
		}

		cursor->link = newNode;
	}
}

void Queue::dequeue(int index)
{
	if (head == 0) // check if queue is empty
	{
		cout << "ERROR: Queue is empty\n\n";
		return;
	}

	Node* target = head; // pointer used to track the target node
	Node* previous = head; // pointer to node before target

	if (index == 0)
	{
		head = head->link;

		delete target;
	}
	else // if index is specified
	{
		for (int i = 0; i < index; i++)
		{
			if (i == index - 1)
			{
				previous = target;
			}

			target = target->link;
		}

		if (target == 0) // return if no ith element
		{
			this->display();

			return;
		}

		previous->link = target->link; // re-link

		delete target;
	}

	this->display();
}

void Queue::insert(char data, int index)
{
	Node* newNode = new Node; // pointer to node being inserted
	newNode->data = data;

	Node* previous = head; // pointer to node before newNode
	Node* cursor = head->link; // pointer to node after newNode

	for (int i = 1; i < index; i++) // itterate to proper index
	{
		cursor = cursor->link;
		previous = previous->link;
	}

	previous->link = newNode;
	newNode->link = cursor;
}

void Queue::removeX()
{
	if (head == 0) // check of queue is Empty
	{
		cout << "ERROR: Queue is empty\n\n";
		return;
	}

	Node* temp = head;	// temp pointer used for traversal
	Node* cursor = head->link; // pointer tracking target node

	if (head->data == 'X') // if head is the first X
	{
		head = head->link;

		delete temp;

		this->display();

		return;
	}

	while (cursor != 0)
	{
		if (cursor->data == 'X')
		{
			temp->link = cursor->link;

			delete cursor;

			this->display();

			return;
		}
		else
		{
			temp = temp->link; // itterate
			cursor = cursor->link; // itterate
		}
	}
}

void Queue::display()
{
	if (head == 0) // check if queue is empty
	{
		cout << "Queue: Empty\n\n";
		return;
	}

	cout << "Queue: ";

	Node* cursor = head; // pointer used to traverse the queue

	while (cursor->link != 0)
	{
		cout << cursor->data << " ";

		cursor = cursor->link;
	}

	cout << cursor->data << "\n\n";
}

void Queue::findMinMax()
{
	if (this->isEmpty()) // check if queue is empty
	{
		cout << "ERROR: Queue is empty\n\n";
		return;
	}

	Node* cursor = head; // pointer to travers queue
	min = head->data;
	max = head->data;

	while (cursor->link != 0)
	{
		if (cursor->data < min)
		{
			min = cursor->data;
		}

		if (cursor->data > max)
		{
			max = cursor->data;
		}

		cursor = cursor->link;
	}

	cout << "Min element in queue: " << min << "\n";
	cout << "Max element in queue: " << max << "\n\n";
}

bool Queue::isEmpty()
{
	if (head == 0)
	{
		return true;
	}
	{
		return false;
	}
}
