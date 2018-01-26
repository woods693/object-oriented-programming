#include "hashtable.h"
#include <vector>
//W
//Assignment 5
// hash function, uses Horner's method
// Assume input string consists only of lower-case a to z
int HashTable::Hash(string input) const
{
	int length = input.length(); //gets length of string
	int key = 0;
	int asc = 0;
	for(int i = 0; i < length; i++)
	{
		asc = input[i] - 96; //gets the asc number of the letter
		if(i == 0) //first letter is not touched
		{
			key = asc;
		}
		else
		{
			key = key * 32 + asc; 
			key = key % maxsize; //modulo by maxsize
		}

	}
	return key;
}


// helper function to find smallest prime number greater than supplied parameter
int HashTable::SmallestPrime(int n) const
{
	int is_prime = 0; 
	if(n == 1) //if n = 1, prime is automatically 2
	{
		return 2;
	}
	n++; //greater than n
	while(is_prime == 0)
	{
		int prime = 0;
		for(int i = 1; i <= n; i++)
		{
			if(n % i == 0)
			{
				prime++;
			}
		}
		if(prime > 2) //if more than 2, not prime
		{
			n++;
		}
		else
		{
			is_prime = 1;	//jumps out of while loop
		}
	}
	return n;
}


// helper function to determine whether a number is prime
bool HashTable::IsPrime(int n) const
{
	int prime = 0;
	if(n == 2)
	{
		return true;
	}
	for(int i = 1; i <= n; i++)
	{
		if(n % i == 0)
		{
			prime++;
		}
	}
	if(prime > 2)
	{
		return false;	
	}
	else
	{
		return true;
	}
}

//works
//public:
// default constructor
// creates an array of size 101
HashTable::HashTable()
{
	maxsize = 101;
	size = 0;
	table = new LinkedList[maxsize];
}

//works
// parameterized constructor
// creates an array of size = smallest prime number > 2n
HashTable::HashTable(int n)
{
	maxsize = SmallestPrime(2*n);
	size = 0;
	table = new LinkedList[maxsize];
}

//works
// copy constructor
// Creates deep copy of sourceht
HashTable::HashTable(const HashTable& sourceht)
{
	
	maxsize = sourceht.maxsize;
	size = sourceht.size;
	//iterate through and copy from each linked list
	for(unsigned int i = 0; i < maxsize; i++)
	{
		table[i] = LinkedList(sourceht.table[i]);
	}
}


// destructor
HashTable::~HashTable()
{
	//iterate through and delete each linkedlist
	for(unsigned int i = 0; i < maxsize; i++)
	{
		table[i].RemoveAll();
	}
	size = 0; //nothing in table
	delete [] table;//delete
}

//works
// overloaded assignment operator
HashTable& HashTable::operator=(const HashTable& sourceht)
{
	if(this != &sourceht) 
	{
		if(table != NULL)
		{
			//deletes all lists .. then delete table
			for(unsigned int i = 0; i < maxsize; i++)
			{
				table[i].RemoveAll();
			}
			delete [] table;
		}
		//copy maxsize and size over from sourceht
		maxsize = sourceht.maxsize;
		size = sourceht.size;
		//creat the new table using maxsize
		table = new LinkedList[maxsize];
		//copy contents from souceht
		for(unsigned int i = 0; i < maxsize; i++)
		{
			table[i] = sourceht.table[i];
		}
	}
	return *this;
}




//works
// Insertion
// If item does not already exist, inserts and returns true
//   otherwise returns false
bool HashTable::Insert(string value)
{
	int key = Hash(value); //generates key 
	if(table[key].Contains(value) == false) //if value not in table
	{
		table[key].Insert(value);
		size++;
		return true;
	}
	return false;
}

//works
// Removal
// If item exists, removes and returns true
//   otherwise returns false
bool HashTable::Remove(string value)
{
	int key = Hash(value);
	if(table[key].Contains(value) == true) //if value is in table
	{
		table[key].Remove(value);
		size--;
		return true;
	}
	return false;
}

//works
// Search
// Returns true if item exists, false otherwise
bool HashTable::Search(string value) const
{
	int key = Hash(value);
	if(table[key].Contains(value) == true) //uses key to find right index in array
	{
		return true;
	}
	return false;
}

//works
// Returns the number of items stored in the hash table
int HashTable::Size() const
{
	return size;
}

//works
// Returns the size of the underlying array
int HashTable::MaxSize() const
{
	return maxsize;
}


// Returns the load factor as size / maxsize.
// Note that due to separate chaining, load factor can be > 1.
double HashTable::LoadFactor() const
{
	double load = double(size)/double(maxsize);
	return load;
}

//more work
// Resizes the hashtable into a larger array.
// Return false if n is smaller than current array size.
// Else, set array size to the smallest prime number larger than n
//   and re-hash all contents into the new array, delete the old array and return true.
bool HashTable::Resize(unsigned int n)
{
	if(n <= maxsize) //returns false when n less than maxsize
	{
		return false;
	}

	//new table
	int newsize = SmallestPrime(n);
	LinkedList* old = table;
	table = new LinkedList[newsize]; //creates table with the new size;
	
	//vecter to collect data from old array
	vector<string> all; //this contains all the old stuff
	for(unsigned int i = 0; i < maxsize; i++)
	{
		vector<string> temp = old[i].Dump();
		all.insert(all.end(), temp.begin(), temp.end()); //inserts temp to end of all
	}

	//delete old table
	for(unsigned int i = 0; i < maxsize; i++) //iterates through to delete linked lists
	{
		old[i].RemoveAll();
	}
	delete [] old;
	size = 0;  //nothing in table
	
	//rehashing into new table
	maxsize = newsize;
	for(unsigned int j = 0; j < all.size(); j++)
	{
		Insert(all[j]);
		size++;
	}
	return true;
}
