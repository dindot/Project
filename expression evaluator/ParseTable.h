// File: ParseTable.h
// Class provided: ParseTable
//
//	Constructors for ParseTable class:
//		ParseTable()
//		postcondition: Initialize two stacks S1, S2 to NULL
//
//		ParseTable(stack S1, stack S2)
//		postcondition: Populate stacks S1, S2 with string input
//
//		ParseTable(const ParseTable& S) { in = S.in; }
//		postcondition: Copies the string input in S, replaces as new value in
//
//	Manipulator/Accessor functions for Parser class:
//		void stateChecker(stack &S1, stack &S2, std::string input, std::string &fromS2)
//		postcondition: The resulting token is placed in its respective stack based on parsetable actions

#ifndef PARSETAB_H
#define PARSETAB_H
#include "stack.h"
#include "queue.h"

class ParseTable
{
	private: 
		std::string in;
	public:
		ParseTable() { stack S1, S2; S1.push("NULL"); S2.push("NULL"); }
		ParseTable(stack S1, stack S2) { S1.push(in); S2.push(in); }
		ParseTable(const ParseTable& S) { in = S.in; }

		void stateChecker(stack &S1, stack &S2, std::string input, std::string &fromS2);
};
#endif

