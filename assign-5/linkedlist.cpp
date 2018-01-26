#include "linkedlist.h"
//W
//#include <vector>
//private:  

//works
// helper method for deep copy
void LinkedList::CopyList(const LinkedList& ll)
{
	vector<string> temp = ll.Dump(); //puts the list into a vecter
	for(int i = int (temp.size()) - 1; i >= 0; i--) //traverses the vecter backwards and inserts
	{
		Insert(temp[i]);
	}

}

//works
//public:
// default constructor
LinkedList::LinkedList()
{
	size = 0;
	head = NULL;
}

//works
// copy constructor
// deep copies source list
LinkedList::LinkedList(const LinkedList& ll)
{
	CopyList(ll);
}

//works
// destructor
LinkedList::~LinkedList()
{
	RemoveAll();
}

//works
// overloaded assignment operator
// deep copies source list after deallocating existing memory (if necessary)
LinkedList& LinkedList::operator=(const LinkedList& ll)
{
	if(this != &ll)
	{
		RemoveAll(); //call upon delete
		CopyList(ll); //call upon copy
	}
	return *this;
}

//works
// Inserts an item at the front of the list
void LinkedList::Insert(string s)
{
	if(size == 0) //sets head to new node when empty
	{
		head = new Node(s,NULL);
		size++;
	}
	else
	{
		Node* insert = new Node(s,head);
		head = insert;
		size++;
	}
}

//works
// Removes an item from the list.
// Returns true if item successfully removed
// False if item is not found
bool LinkedList::Remove(string s)
{
	Node* curr = NULL;
	Node* pre = NULL;
	//empty string
	if(head == NULL)
	{
		return false;
	}
	//checks if head is s
	if(head->data == s)
	{
		curr = head->next;
		delete head;
		head = curr;
		size--;
		return true;
	}
	//when head is not s
	curr = head->next;
	pre = head;

	while(curr != NULL)
	{
		if(curr->data == s)
		{
			pre->next = curr->next;
			delete curr;
			size--;
			return true;
		}
		pre = pre->next;
		curr= curr->next;

	}
	return false;
}

//works
void LinkedList::RemoveAll()
{
	Node* curr = head;
	while(curr != NULL)
	{
		curr = head->next;
		delete head;
		head = curr;
		size--;
	}

	head = NULL;
}

//works
// Checks if an item exists in the list
bool LinkedList::Contains(string s) const
{
	Node* curr = head;
	while(curr != NULL)
	{
		if(curr->data == s)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;

}

//works
// Return the number of items in the list
unsigned int LinkedList::Size() const
{
	return size;
}


//works
// Returns a vector containing the list contents using push_back
vector<string> LinkedList::Dump() const
{
	Node* curr = head;
	vector<string> list_vecter; //creates vecter 
		for(unsigned int i = 0; i < size; i++)
		{
			if(curr != NULL) //iterates through
			{
				list_vecter.push_back(curr->data); //pushes contents into vecter
				curr = curr->next;
			}
		}
	return list_vecter;
}
