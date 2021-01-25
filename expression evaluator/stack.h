// File: stack.h
// Class provided: stack
//
//	Constructors for stack class:
//		stack()
//		postcondition: initialize cursor to 0
//		
//	Manipulator/Accessor functions for stack class:
//		void push(string data)
//		postcondition: inserts data to stack, increment cursor
//		
//		void pop()
//		precondition: stack must at least one entry, else empty stack mssg
//		postcondition: removes value from top of stack
//
//		void peek()
//		postcondition: displays value at top of stack
//
//		bool isEmpty()
//		postcondition: returns true if cursor is 0
//
//		bool isFull()
//		postcondition: display number of items in stack and return true if full

#ifndef STACK_H
#define STACK_H
#include "linkedlist.h"

class stack : public linkedlist
{
	private:
		int cursor;

	public:
		stack();
		void push(std::string data);
		std::string pop();
		std::string peek() { return start(); }
		bool isEmpty() { if (cursor == 0) return true; }
		int isFull();
		int getCursor() { return cursor; }
};
#endif
