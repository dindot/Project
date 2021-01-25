/*	CISP 430 Data Structures Preamble

	Program: Expression Evaluator
	Author: Din Bostandzic
	Date: March 11, 2020
	Purpose: // This program is an expression evaluator that takes in a user input
			// expression (supporting variables a,b,c,d which come with predefined 
			// values within program) and then uses parser with space as the delimiter,
			// to break up each token from the string, which gets applied to a stack
			// and used in parse table to determine all actions on how that infix
			// expression that was entered gets converted to postfix mode. Once in 
			// postfix, the numeric values are popped into the eval stack that evaluates
			// and reduces the expression into a single numeric value printed to screen.

	Date          WhoWhat
	March 11      Bostandzic first source file edits
	April 29	  Bostandzic second source file edits
			
*/

#include <iostream>
#include "Drecord.cpp"
#include "linkedlist.cpp"
#include "stack.cpp"
#include "queue.h"
#include "ExpressionEval.h"
#include "Parser.h"
#include "ParseTable.h"
using namespace std;

char keep;

int main()
{
	int parencount = 0;
	char stop = 'y';
	bool go = true;
	string expression;

	stack S1, S2, tempStack;
	ParseTable table;
	ExpressionEval eval;

	cout << "Expression Evaluator -- Supports following variables with preset values: (A = 5, B = 10, C = -1, D = 2)" << endl;
	cout << "Supports math function: sin, cos, sqrt, abs" << endl;
	cout << "Supports variables X, Y, Z if desired to be used in lefthand side (LHS) of expression" << endl << endl;
	do
	{
	top:
		cout << "Enter expression (separate each character with a single space) to be converted to postfix, then evaluated: ";
		getline(cin, expression);

		// Check for balanced number of parenthesis in expression
		for (unsigned int i = 0; i < expression.length(); i++)
		{
			char c = expression[i];
	
			if (c == '(')
				parencount++;
			else if (c == ')')
				parencount--;
			if (c == '/')
				keep = c;
			if (keep && c == '0')
			{
				cout << "Can not divide by zero, please enter new equation." << endl;
				parencount = 0;
				goto top;
			}
				
		}
		if (parencount != 0)
		{
			parencount = 0;
			cout << "Parenthesis are imbalanced in expression, please check and rewrite." << endl;
			goto top;
		}

		Parser parse(expression, ' ');		// Parser with space as delimiter

		string token, token2 = "NULL";		// To collect tokens

		while (parse.HasMoreTokens())
		{
			token = parse.NextToken();
			for (unsigned int i = 0; i < token.length(); i++)
			{
				token[i] = toupper(token[i]);		// Convert to common case
			}
			if (token.find_first_not_of("ABCDXYZ"))
				table.stateChecker(S1, S2, token, token2);

			else if (token.find_first_not_of("()*/+-="))
			{
				table.stateChecker(S1, S2, token, token2);
				token2 = token;
				if (token2 == "SIN" || token2 == "COS" || token2 == "SQRT" || token2 == "ABS" )
					token2 = S2.peek();
				
				if (token2 == ")")
					token2 = S2.peek();
			}
			else if (token == "COS" || token == "SIN" || token == "ABS" || token == "SQRT")
			{
				table.stateChecker(S1, S2, token, token2);
				token2 = token;
			}
				
			else
				table.stateChecker(S1, S2, token, token2);
		}

		int	counter = S2.getCursor();
		for (int i = 0; i < counter; i++)
		{
			S1.push(S2.peek());
			S2.pop();
		}
		cout << "Input equation: " << expression << endl;

		int counter2 = S1.isFull();
		for (int i = 0; i <= counter2; i++)
		{
			tempStack.push(S1.peek());
			S1.pop();
		}
		cout << "Postfix form: ";
		tempStack.print();

		eval.evaluate(tempStack);

		cout << "\nWould you like to enter a new expression? (Y/N): ";
		cin >> stop;
		if (toupper(stop) == 'Y')
			go = true;
		else
		{
			go = false;
			cout << "Ended application...";
		}
		cin.clear();
		cin.ignore();

	} while (go != false);

	return 0;
}