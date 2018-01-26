//W
#ifdef _CIRCULARLINKEDLIST_H_
#include <stdexcept>
#include <iostream>

//#include "circularlinkedlist.h"

// helper function for deep copy
// Used by copy constructor and operator
template <class T>
void CircularLinkedList<T>::CopyList(const CircularLinkedList<T>& ll)
{	 
	if(ll.head != NULL )
	{
		head = new Node<T>(ll.head->data); //creates new Node called head with data from ll's head
		size++; //increments size by 1
		
		//initializes the circularlinked list
		head->prev = head;
		head->next = head;

		Node<T>* currOld = ll.head; //keeps track of old list
		Node<T>* curr = head;// new list 
		

		currOld = currOld->next;

		while(currOld != ll.head)
		{
			//updating new linked list
			Node<T>* newNode = new Node<T>(currOld->data);
			curr->next = newNode;
			newNode->prev = curr;
			newNode->next = head;
			head->prev = newNode;

			//increments curr & currOld
			curr = curr->next;
			currOld = currOld->next;

			size++;
		}
	}		
}



// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void CircularLinkedList<T>::DeleteList()
{
	if(head != NULL)
	{
	
		//creating nodes
		Node<T>* temp = head->next;
		Node<T>* curr = temp->next;

		while(temp != head)
		{
			delete temp;
			temp = curr;
			curr = curr->next;
		
		} 
		//deletes the head 
		head = NULL;
		size = 0;
	}
}


//Jon says nothing for this
// default constructor
template <class T>
CircularLinkedList<T>::CircularLinkedList()
{
	size = 0;
	head = NULL;
}

// copy constructor, performs deep copy of list elements
template <class T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& ll)
{
	CopyList(ll);
}

	
// destructor
template <class T>
CircularLinkedList<T>::~CircularLinkedList()
{
	DeleteList();	
}


//More Work
// Accessors
// Returns the number of items in the list
template <class T>
int CircularLinkedList<T>::Count() const
{
	return size;
}

// Returns whether the list contains any items
template <class T>
bool CircularLinkedList<T>::IsEmpty() const
{
	if(head == NULL)
	{
		return true;
	}
	return false;
}
//whatever function returns bool, 
// Returns existence of item
template <class T>
bool CircularLinkedList<T>::Contains(T item) const
{
	
	if(!IsEmpty())
	{
		Node<T>* curr; 
		while(curr != head)
		{
			if(curr == NULL)
			{
				curr = head;
			}
			if(curr->data == item)
			{
				return true;
			}
			curr = curr->next;
		}
	}
	return false;	
}

// Returns item at index (0-indexed)
// Throws exception for empty list or invalid indexT
template <class T>
T CircularLinkedList<T>::ElementAt(int p) const
{
	if(!IsEmpty() && p < size)
	{
		Node<T>* curr = head;
		for(int i = 0; i < p; i++)
		{
			curr = curr->next;
		}
		return curr->data;
	}
	else
	{
		throw std::out_of_range("CircularLinkedList:: index out of range or emptylist");
	}

}


// Inserts an item at the tail end of the list in constant time
// POST: List contains item at the tail end, size increases by 1
// PARAM: item = item to be inserted
template <class T>
void CircularLinkedList<T>::Insert(T item)
{
	if(head) //checks if empty list
	{	
		Node<T>* curr = head->prev; 
		curr->next = new Node<T>(item);
		curr->next->next = head;
		head->prev = curr->next;  
		curr->next->prev = curr;
		size++;
	}
	else //if empty, creates a new head Node
	{
		head = new Node<T>(item);
		head->prev = head;
		head->next = head;
		size = 1;
	}
}

    
 
// Inserts an item in position p (0-indexed)
// Throws exception for invalid index
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
template <class T>
void CircularLinkedList<T>::InsertAt(T item, int p)
{
	if(p < size) //checks if legal index
	{
		Node<T>* curr = head;
		Node<T>* newNode = new Node<T>(item);
		for(int i = 0; i < p;i++)
		{
			curr = curr->next;
		}

		////
		curr->prev->next = newNode;
		newNode->prev = curr->prev;
		newNode->next = curr;
		curr->prev = newNode;
		size++;
		
		if(p == 0) //edge case 
		{
		head = newNode;
		}
	}
	else if (p == size) //inserting at the end
	{
		Insert(item);
	}

	else if(size == 0 && p == 0) //inserting into empty list
	{
		Node<T>* newNode = new Node<T>(item);
		head = newNode;
		head->prev = head;
		head->next = head;
	}
	else //throw
	{
		throw std::out_of_range("CircularLinkedList:: index out of range");
	}

}

// Removes and returns an item from position p (0-indexed)
// Throws error if list is empty or index invalid
// POST:  Item is removed from list and associated Node memory is deallocated
// PARAM: p = position from where item will be removed
template <class T>
T CircularLinkedList<T>::RemoveAt(int p)
{
	if(p < size)
	{
		Node<T>* curr = head;
		for(int i = 0; i < p;i++)
		{
			curr = curr->next;
		}
		if(p == 0)
		{
			head = head->next;
		}
		/////////
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		
		T temp = curr->data;
		delete curr;
		size--;
		
		if(size == 0)
		{
			head = NULL;
		}
		
		return temp;
	}
	else
	{
		throw std::out_of_range("CircularLinkedList:: index out of range");
	}
}

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 =list2 -> should do nothing
template <class T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& ll)
{
	if(this != &ll)
	{
		DeleteList(); //call upon delete
		CopyList(ll); //call upon copy
	}
	return *this;
}

#endif