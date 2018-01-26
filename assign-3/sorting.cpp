// File:        sorting.cpp
// Author:      Geoffrey Tien
//              (your name)
// Date:        2015-06-10
// Description: Skeleton file for CMPT 225 assignment #3 sorting functions and helpers
//              Function bodies to be completed by you!

// Complete your sorting algorithm function implementations here

// write a few comments...

template <class T>
int SelectionSort(T arr[], int n)
{
	int smallest; //keeps track of smallest index
	int barcount = 0;
	T temp; //holds onto data when switching
	for(int i = 0; i < n; i++)
	{
		smallest = i;
		for(int j = i+1; j <= n-1; j++)
		{
			barcount++; 
			if(arr[smallest] >= arr[j])
			{
				smallest = j;
			}
		}
		//swap
		temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
	}
	return barcount;
}

//more work
// write a few comments...
template <class T>
int Quicksort(T arr[], int n)
{
	int counter = 0;
	QuicksortHelper(arr, 0, n-1,counter);
	return counter;
}

//more work 
// write a few comments...
template <class T>
void QuicksortHelper(T arr[], int low, int high, int& counter)
{
	if(low < high)
	{
		int pivot = QSPartition(arr, low, high,counter);
		if(pivot > 1)
		{
			QuicksortHelper(arr, low, pivot - 1,counter);
		}
		if(pivot + 1 < high)
		{
			QuicksortHelper(arr, pivot + 1, high,counter);
		}
	}
}

// write a few comments...
template <class T>
int QSPartition(T arr[], int low, int high, int& counter)
{
	T pivot = arr[low];
	do
	{
		while (arr[low] < pivot)
		{
			counter++;
			low++;//increments low when less than pivot
		}
		while (arr[high] > pivot)
		{
			counter++;
			high--;//decrements high when greater than pivot
		}
		if(low < high)//swaps the last and first elements
		{
			T temp = arr[high];
			arr[high] = arr[low];
			arr[low] = temp;
		}
	}while(low != high); 
	return low;
}

// write a few comments...
template <class T>
int Mergesort(T arr[], int n)
{
	int counter = 0;
	MergesortHelper(arr,0,n-1,n,counter);
	return counter;
}

// write a few comments...
template <class T>
void MergesortHelper(T arr[], int low, int high, int n, int& counter)
{
	int mid;
	if(low < high)
	{
		mid = (low + high)/ 2;
		MergesortHelper(arr, low, mid, mid, counter); //low - to - mid
		MergesortHelper(arr, mid+1, high, n-mid, counter); //mid_1 - to - high
		Merge(arr, low, mid, high, n, counter);
	}
}

// write a few comments...
//Notes*
//create two temp arrays for merging
//copy remainder over after comparing
//the one left are larger ones
//remember to delete temp after
template <class T>
void Merge(T arr[], int low, int mid, int high, int n, int& counter)
{
	int a1 = mid - low + 1;
	int a2 = high - mid;
	int leftPos, rightPos, k;

	//temporary arrays
	T* Left = new T[a1];
	T* Right = new T[a2];

	//data copy
	for(rightPos = 0; rightPos < a2; rightPos++) //right
	{
		Right[rightPos] = arr[mid + 1 + rightPos];
	}
		for(leftPos = 0; leftPos < a1; leftPos++) //left
	{
		Left[leftPos] = arr[low + leftPos];
	}

	//merging part
	leftPos = 0; rightPos = 0; k = low;
	while(leftPos < a1 && rightPos < a2)
	{
		if(Left[leftPos] > Right[rightPos])
		{
			arr[k] = Right[rightPos];
			rightPos++;
		}
		else
		{
			arr[k] = Left[leftPos];
			leftPos++;
		}
		k++;
		counter++;
	}

	//copy remaining elements of Right[]..only if needed
	while(rightPos < a2)
	{
		arr[k] = Right[rightPos];
		k++;
		rightPos++;
	}
		//copy remaining elements of Left[]..only if needed
	while(leftPos < a1)
	{
		arr[k] = Left[leftPos];
		k++;
		leftPos++;
	}

	//deleting temporary arrays
	delete[] Right;
	delete[] Left;
}

// write a few comments...
template <class T>
int ShellSort(T arr[], int n)
{
	int j;
	int count = 0;
	int k = n;
	if(k != 0) //checks if array is empty or not
	{
		while(k != 1) //exits when k reduces to 1
		{
			k = k/2; //keep halving k
			for(int i = k; i < n; i++)
			{
				T temp = arr[i]; //creat temp to store array data ... for swap later
				for(j = i; j - k >= 0 && arr[j - k] > temp; j = j - k)
				{
					arr[j] = arr[j - k]; 
					count++;
				}
				arr[j] = temp;
			}
		}
	}
	else
	{
		cout << "empty array";
	}
	return count;
}