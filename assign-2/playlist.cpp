#include <iostream>
#include "playlist.h"
//Woody Chen Lin Chang
//s.id: 301 231 083
//Cmpt 225 // Assignment 2

//Public
	// default constructor
PlayList::PlayList()
{
	nowplaying = 0; //initializes nowplaying to 0
}

    // ACCESSORS

    // Returns the number of items in the playlist
    // Calls LinkedList.Size();
int PlayList::Size() const
{
	return sequence.Count();	//calls upon couting function
}

    // MUTATORS

    // Advances the nowplaying counter by 1.
    // If the end of the list is reached, loop to the start of the list.
void PlayList::Play()
{
	if(nowplaying == sequence.Count()) //brings nowplaying back to front
	{
		nowplaying = 1;
	}
	else
	{
		nowplaying++; //increments
	}

}

    // Enqueues an item at the back of the playlist
    // nowplaying remains the same unless the added item is the first in an empty playlist
void PlayList::Add(Song song)
{
	if(sequence.Count() == 0)
	{
		sequence.Insert(song);
		nowplaying = 1;
	}
	else
	{
		sequence.Insert(song);
	}

}

    // Moves the item in nowplaying position up (towards the front) by 1, if playlist contains any items.
    // Has no effect if playlist is empty.
    // If item is already at the front, it remains at the front
    // POST:   position of nowplaying item is swapped with one ahead,
    //         nowplaying is reduced by 1 unless it is at the front of the list
void PlayList::MoveUp()
{
	//Makes sure list is not empty and nowplaying is not top
	if(!sequence.IsEmpty() && nowplaying != 1)
	{	
		Song temp = sequence.RemoveAt(nowplaying-1);
		sequence.InsertAt(temp, nowplaying-2);
		nowplaying--;
	}

}
    // Moves the item in nowplaying position down (towards the back) by 1, if playlist contains any items.
    // Has no effect if playlist is empty.
    // If item is already at the back, it remains at the back
    // POST:   position of item is swapped with one behind,
    //         nowplaying is increased by 1 unless it is at the back of the list
void PlayList::MoveDown()
{
	//Makes sure list is not empty and nowplaying is not at bottom
	if(!sequence.IsEmpty() && !(nowplaying == sequence.Count()))
	{
		Song temp = sequence.RemoveAt(nowplaying-1);
		sequence.InsertAt(temp,nowplaying);
		nowplaying++;
	}
}

    // Removes the nowplaying item from the playlist
    // POST: nowplaying item is removed, nowplaying index moves to next item (if any)
    //       if last item is removed, nowplaying index moves to new last item
void PlayList::Remove()
{
	//Makes sure list is not empty
	if(!sequence.IsEmpty())
	{
		Song temp = sequence.RemoveAt(nowplaying-1); //removes
		if(nowplaying-1 == sequence.Count())
		{
			nowplaying--; //decreases nowplaying by 1
		}
	}
}

    // OTHER

    // Prints the contents of the (1-indexed) playlist to console,
    //  with one song on each line of output, preceded by nowplaying icon and number, in the following format:
    // "<now playing><position>. <artist> - <title>"
    //  e.g. (* indicates nowplaying)
    //   1. dj whocares - my favourite song
    //  *2. dj whocares - my least favourite song
    //   3. mc noname - forgettable
void PlayList::PrintPlayList() const
{
	Song temp;
	for(int i = 0; i < sequence.Count();i++)
	{
		temp = sequence.ElementAt(i);
		if(nowplaying-1 == i)
		{
			cout << "*";
		}
		cout << i+1 << ". " << temp.GetArtist() << " - " << temp.GetTitle() << "\n";
		
	}
}

    // Returns a reference to the underlying CircularLinkedList object
    // You do not need to implement this function in your .cpp file.
    // NOTE: This is dangerous and should not be used in practice!
    //       This function is here only for the instructor/TA to check the correctness of your linked list!
CircularLinkedList<Song> PlayList::GetList() const
{
	return sequence;
}