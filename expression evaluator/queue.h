// File: queue.h
// Class provided: queue
//
// Constructors for queue class:
//		queue()
//		postcondition: initialize start to 0
//
// Manipulator/Accessor functions for queue class:
//		void enqueue(string data) 
//		postcondition: inserts data into queue, increment start
//
//		void dequeue()
//		postcondition: remove value from end of list, decrement start
//
//		bool isEmpty() 
//		postcondition: returns true when start is 0
//
//		bool isFull()
//		postcondition: returns true when start is not 0
//
//		void sortData() 
//		precondition: pass the length of queue (start)
//		postcondition: sorts all data in currently in queue
//
//		bool searchData(string x) 
//		postcondition: returns true if x found in queue, else not in queue

#ifndef QUEUE_H
#define QUEUE_H
#include "linkedlist.h"

class queue: public linkedlist
{
	private:
		int start;

	public:
		queue() { start = 0; }
		void enqueue(std::string data) { insert(data); start++; }
		void dequeue() { removeEnd(); start--; }
		bool isEmpty() { if (start == 0) return true; }
		bool isFull() { if (start != 0) return true; }
		void sortData() { sort(start); }
		bool searchData(std::string x) { return search(x); }
};
#endif
