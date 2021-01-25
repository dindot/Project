// File: ExpressionEval.cpp
// Class implementation: ExpressionEval
#include "ExpressionEval.h"
#include <stack>
#include <cmath>
#include <iomanip>

void ExpressionEval::evaluate(stack &tempStack)
{
	std::stack<float> eval;					// Create stack of floats
	
	std::string var1 = tempStack.peek();	// Store the first token, then pop it
	tempStack.pop();
	std::string var2;
	int count = tempStack.isFull();

	int sinmaker = 0, cosmaker = 0, sqrtmaker = 0, absmaker = 0;
	float rhs, lhs;

	// For the number of tokens, evaluate each token respectively to get numeric, pop off each from tempStack as used
	for (int i = 0; i <= count; i++)
	{
		if (tempStack.peek() == "A")
		{
			eval.push(getVal("A"));
			tempStack.pop();
		}
		else if (tempStack.peek() == "B")
		{
			eval.push(getVal("B"));
			tempStack.pop();
		}
		else if (tempStack.peek() == "C")
		{
			eval.push(getVal("C"));
			tempStack.pop();
		}
		else if (tempStack.peek() == "D")
		{
			eval.push(getVal("D"));
			tempStack.pop();
		}
		else if ((tempStack.peek().find_first_not_of("+-/*")))
		{
			rhs = eval.top();				// Store the rhs of equation
			eval.pop();						// Remove rhs from stack
			lhs = eval.top();				// Store remaining value as lhs
			eval.pop();						// Remove lhs from stack, empty
			if (tempStack.peek() == "+")	// Perform the operation on lhs and rhs, based on operator token
				eval.push(lhs + rhs);
			else if (tempStack.peek() == "-")
				eval.push(lhs - rhs);
			else if (tempStack.peek() == "/")
				eval.push(lhs / rhs);
			else if (tempStack.peek() == "*")
				eval.push(lhs * rhs);

			tempStack.pop();				// Remove the operator token from tempStack
		}
		// Cases for sin, cos, sqrt, abs functions supported
		else if ((tempStack.peek() == "SIN"))
		{
			sinmaker = 1;			// Flag that it appeared and remove from tempStack
			tempStack.pop();
		}
		else if ((tempStack.peek() == "COS"))
		{
			cosmaker = 1;
			tempStack.pop();
		}
		else if ((tempStack.peek() == "SQRT"))
		{
			sqrtmaker = 1;
			tempStack.pop();
		}
		else if ((tempStack.peek() == "ABS"))
		{
			absmaker = 1;
			tempStack.pop();
		}
		// If the last token in tempStack is = then store it, to be used for display in final expression
		else if (tempStack.peek() == "=")
		{
			var2 = tempStack.peek();
			tempStack.pop();
		}
		else
		{
			eval.push(stof(tempStack.peek()));
			tempStack.pop();
		}
			

	}
	// Check the flags, these unary operations are performed last so that any values in parenthesis will be performed first
	if (sinmaker == 1)
	{
		rhs = sin(eval.top());
		eval.pop();
		eval.push(rhs);
		sinmaker = 0;
	}
	else if (cosmaker == 1)
	{
		rhs = cos(eval.top());
		eval.pop();
		eval.push(rhs);
		cosmaker = 0;
	}
	else if (sqrtmaker == 1)
	{
		rhs = sqrt(eval.top());
		eval.pop();
		eval.push(rhs);
		sqrtmaker = 0;
	}
	else if (absmaker == 1)
	{
		rhs = abs(eval.top());
		eval.pop();
		eval.push(rhs);
		absmaker = 0;
	}
	
	// Display the single numeric value with the beginning variable and = stored from earlier
	std::cout << var1 << " " << var2 << " " << eval.top();
}

float ExpressionEval::getVal(std::string letter)
{
	// Return the numeric values of each predefined variable, to be used in eval stack
	if (letter.find_first_not_of("A"))
		return 5;
	else if (letter.find_first_not_of("B"))
		return 10;
	else if (letter.find_first_not_of("C"))
		return -1;
	else if (letter.find_first_not_of("D"))
		return 2;
}