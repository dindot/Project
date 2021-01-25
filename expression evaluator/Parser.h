// File: Parser.h
// Class provided: Parser
//
//	Constructors for Parser class:
//		Parser()
//		postcondition: Initialize the vector of strings to hold tokens.
//
//		Parser(vector <string> &newToken)
//		postcondition: Copies contents of previous vector into newToken
//
//		Parser(string, char)
//		postcondition: Parses given string into tokens, split by the char delimiter.
//
//	Manipulator/Accessor functions for Parser class:
//		int GetNumTokens() 
//		postcondition: Returns the total number of tokens extracted.
//
//		bool HasMoreTokens() 
//		postcondition: Returns true if there are tokens left, false otherwise
//
//		string NextToken()
//		postcondition: Extracts the next token from vector of tokens.

#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>

class Parser
{
	private:
		std::vector <std::string> tokens;
	public:
		Parser() { tokens.clear(); }	// Class constructors
		Parser(std::vector <std::string> &newToken) { for (int i = 0; i < tokens.size(); i++) newToken.push_back(tokens[i]);}
		Parser(std::string, char);		

		int GetNumTokens() { return tokens.size(); }			// Total number of tokens
		bool HasMoreTokens() { return tokens.size() != 0; }		// Check if there are any tokens left
		std::string NextToken();
};
#endif PARSER_H