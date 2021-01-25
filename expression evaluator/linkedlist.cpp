// File: linkedlist.cpp
// Class implementation: linkedlist

#include <iostream>
#include <iomanip>
#include "linkedlist.h"

linkedlist::linkedlist()
{
	head = new Drecord;
	head->setKey("NULL");
	head->setPrev(NULL);
	head->setNext(NULL);
	count = 0;
}

std::string linkedlist::start()
{
	Drecord* current = head->getNext();	 // Set next to address of next value pointed by head

	if (current != NULL)
		return current->getKey();
	else
		std::cout << "Empty list" << std::endl;
}

void linkedlist::iterate(int count)
{
	for (int i = 1; i <= count; i++)			// For length of list
	{
		Drecord* current = head->getNext();
		
		if (current != NULL)
		{
			current = current->getNext();		// Keep getting next entry
			if (current == NULL)
				return;							// Exit when end reached
			head->setNext(current);				// Advance the head
		}
		
		if (i == (count - 2))
			// Display the value at end of list
			std::cout << "Currently at: " << current->getKey() << std::endl;
		else
			std::cout << current->getKey() << std::endl;		// Display each iteration
	}
}

void linkedlist::sort(int count)
{
	for (int i = 0; i < count; i++)
	{
		Drecord* current = head->getNext();
		Drecord* next = head->getNext()->getNext();

		for (int j = i + 1; j < count; j++)
		{	// Compare the list entry to next entry
			if (current->getKey() > next->getKey())
			{	// Swap if first entry is greater
				std::string temp = current->getKey();
				current->setKey(next->getKey());
				next->setKey(temp);
			}
			current = next;		// Point current to next Drecord in list
			if (next->getNext() != NULL)
				next = next->getNext();		// Point next to next Drecord to be compared
			else
				break;						// Return when reached end of list
		}
	}
}

void linkedlist::insert(std::string newData)
{
	Drecord* newRec = new Drecord;
	newRec->setKey(newData);
	newRec->setNext(head->getNext());	// Place first value at start list

	if (head->getNext() != NULL)		
	{
		// When list not empty, link to previous Drecord
		(head->getNext())->setPrev(newRec);
	}

	head->setNext(newRec);		// Link the next Drecord
	newRec->setPrev(NULL);		
	count++;					// Keep track of # of insertions made
}

std::string linkedlist::remove()
{
	Drecord* prev = head;
	prev->setNext(prev->getNext()->getNext());	// Remove from start of list
	return prev->getKey();
}

void linkedlist::removeEnd()
{
	Drecord* prev = head;
	if (head->getNext() == NULL)		// If list empty delete the head
		delete head;

	while (prev->getNext()->getNext() != NULL)
		prev = prev->getNext();			// Advance until end of list reached
	delete(prev->getNext());			// Remove last entry in list
	prev->setNext(NULL);
}

bool linkedlist::search(std::string data)
{
	Drecord* current = head->getNext();

	while (current != NULL)
	{
		if (current->getKey() == data)		// While list not empty compare data passed with data in list
			return true;
		else
			current = current->getNext();	// Advance through each list entry
	}
	return false;
}

void linkedlist::print()
{
	Drecord* newRec = head->getNext();
	
	while (newRec != NULL)		// Format output to display list entries in report
	{
		std::cout << newRec->getKey() << " ";
				 
		newRec = newRec->getNext();		// Point to the next entry in list
	}
	std::cout << std::internal << '\n';
}
