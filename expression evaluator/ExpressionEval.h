// File: ExpressionEval.h
// Class provided: ExpressionEval
//
//	Constructors for ExpressionEval class:
//		ExpressionEval()
//		postcondition: Initialize tempStack to NULL
//
//		ExpressionEval(string newExp)
//		postcondition: Assigns string value of newExp to express
//
//		ExpressionEval(const ExpressionEval& eval) { express = eval.express; }
//		postcondition: Copies express in eval to be assigned to original express
//
//	Manipulator/Accessor functions for linkedlist class:
//		void evaluate(stack &tempStack)
//		postcondition: evaluates postfix form, reduces so that expression displayed is single variable = to numeric value
//
//		float getVal(string letter)
//		postcondition: returns numeric value of the predefined string variable token of a,b,c,d

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include "stack.h"

class ExpressionEval
{
	private:
		stack tempStack;
		std::string express;
	public:
		ExpressionEval() { tempStack.push("NULL"); }
		ExpressionEval(std::string newExp) { express = newExp; }
		ExpressionEval(const ExpressionEval& eval) { express = eval.express; }

		void evaluate(stack &tempStack);
		float getVal(std::string letter);
};
#endif EXPRESSION_H

