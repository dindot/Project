// File: linkedlist.h
// Class provided: linkedlist
//
//	Constructors for linkedlist class:
//		linkedlist()
//		postcondition: declare head as new Drecord type, initialize key, prev, next to null
//
//		linkedlist(Drecord* newHead) 
//		postcondition: initialize the head with pointer passed through newHead
//
//		linkedlist(const linkedlist& newHead)
//		postcondition: copy the newHead to head value
//
//	Destructor:
//		~linkedlist()
//		postcondition: deletes the head and list
//
//	Manipulator/Accessor functions for linkedlist class:
//		void insert(string newData)
//		postcondition: newData gets inserted to list
//
//		void print()
//		postcondition: prints out the entire list
//
//		void remove()
//		postcondition:	removes list entry from start of list
//
//		void removeEnd()
//		postcondition: removes list entry from end of list
//
//		bool search(string data)
//		postcondition: returns true if data found in list, else false returned
//
//		void sort(int count)
//		postcondition: sorts the list entries in list to be displayed
//
//		int getCount()
//		postcondition: returns count (# of entries in list)
//
//		void iterate(int count)
//		postcondition: iterates through end of list display each iteration
//
//		void start()
//		postcondition: displays list entry value at end of list

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include "Drecord.h"

class linkedlist
{
	private:
		Drecord* head;
		int count;

	public:
		linkedlist();
		linkedlist(Drecord *newHead) { head = newHead; }
		linkedlist(const linkedlist& newHead) { head = newHead.head; }
		~linkedlist() { delete head; }
		void insert(std::string newData);
		void print();
		std::string remove();
		void removeEnd();
		bool search(std::string data);
		void sort(int count);
		int getCount() { return count; }
		void iterate(int count);
		std::string start();
};
#endif
