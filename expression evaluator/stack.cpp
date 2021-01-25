// File: stack.cpp
// Class implementation: stack

#include "stack.h"
#include <iostream>

stack::stack()
{
	cursor = 0;
}

void stack::push(std::string data)
{
	insert(data);
	cursor++;
}

std::string stack::pop()
{
	cursor--;
	/*std::string ifEmpty = "Empty stack.\n";
	if (cursor == 0)
	{
		std::cout << ifEmpty;
	}*/
	std::string rem = remove();
	return rem;
}

int stack::isFull()
{
	if (cursor != 0) 
	//	std::cout << cursor-1 << " Items in stack" << std::endl; 
	return (cursor-1);
}
