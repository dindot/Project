// File: ParseTable.cpp
// Class implementation: ParseTable
#include "ParseTable.h"
#include <iostream>

 std::string storeit;

void ParseTable::stateChecker(stack& S1, stack& S2, std::string input, std::string& fromS2)
{
// The entire ParseTable implementation with its actions on what stack to place the token based on what is 
// located at top of each stack, this process will result in postfix expression creation
	top:
	
	if (input.find_first_not_of("ABCDXYZ") && fromS2 == "NULL" || input.find_first_not_of("ABCDXYZ") && fromS2 == "=" || input.find_first_not_of("ABCDXYZ") && fromS2 == "+" || input.find_first_not_of("ABCDXYZ") && fromS2 == "-" || input.find_first_not_of("ABCDXYZ") && fromS2 == "*" || input.find_first_not_of("ABCDXYZ") && fromS2 == "/" || input.find_first_not_of("ABCDXYZ") && fromS2 == "(")
		S1.push(input);
	else if ((input == "COS" || input == "SIN" || input == "ABS" || input == "SQRT") && (fromS2 == "=" || fromS2 == "+" || fromS2 == "-" || fromS2 == "*" || fromS2 == "/" || fromS2 == "("))
		S2.push(input);
	else if (input == "=" && fromS2 == "NULL")
		S2.push(input);
	else if (input == "=" && fromS2 != "NULL")
		std::cout << "Error occurred, input not valid." << std::endl;
	else if ((input == "+" || input == "-") && fromS2 == "NULL")
		std::cout << "Error occurred, input not valid." << std::endl;
	else if (((input == "+" || input == "-") && fromS2 == "="))
		S2.push(input);
	else if (((input == "+" || input == "-" || input == "*" || input == "/") && (fromS2 == "SIN" || fromS2 == "COS" || fromS2 == "SQRT" || fromS2 == "ABS")))
	{
			S1.push(S2.peek());
			S2.pop();
			S2.push(input);
	}
	else if (((input == "+" || input == "-") && (fromS2 == "+" || fromS2 == "-")))
	{
		S1.push(S2.peek());
		S2.pop();
		fromS2 = S2.peek();
		goto top;				// Rerun the parse action checks at top
	}
	else if ((input == "+" || input == "-") && (fromS2 == "*" || fromS2 == "/"))
	{
		S1.push(S2.peek());
		S2.pop();
		fromS2 = S2.peek();
		goto top;				// Rerun the parse action checks at top
	}
	else if ((input == "+" || input == "-") && fromS2 == "(")
		S2.push(input);
	else if ((input == "*" || input == "/") && fromS2 == "NULL")
		std::cout << "Error occurred, input not valid." << std::endl;
	else if ((input == "*" || input == "/") && fromS2 == "=")
		S2.push(input);
	else if ((input == "*" || input == "/") && (fromS2 == "+" || fromS2 == "-"))
		S2.push(input);
	else if ((input == "*" || input == "/") && (fromS2 == "*" || fromS2 == "/"))
	{
		S1.push(S2.peek());
		S2.pop();
		fromS2 = S2.peek();
		goto top;
	}
	else if ((input == "*" || input == "/") && fromS2 == "(")
		S2.push(input);
	else if ((input == "(" && fromS2 == "NULL"))
		std::cout << "Error occurred, input not valid." << std::endl;
	else if ((input == "(" && (fromS2 == "+" || fromS2 == "-" || fromS2 == "=" || fromS2 == "(" || fromS2 == "*" || fromS2 == "/")))
		S2.push(input);
	else if (input == ")" && (fromS2 == "NULL" || fromS2 == "="))
		std::cout << "Error occurred, input not valid." << std::endl;
	else if ((input == ")" && (fromS2 == "+" || fromS2 == "-" || fromS2 == "(" || fromS2 == "*" || fromS2 == "/" || fromS2 == "SIN" || fromS2 == "COS" || fromS2 == "SQRT" || fromS2 == "ABS")))
	{
		while (S2.peek() != "(")
		{
			S1.push(S2.peek());
			S2.pop();
		}
		if (S2.peek() == "(")
			S2.pop();
	}
	else
		S1.push(input);
}
