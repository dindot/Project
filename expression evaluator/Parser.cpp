// File: Parser.cpp
// Class implementation: Parser
#include "Parser.h"
#include <iostream>

Parser::Parser(std::string raw, char delimiter)
{
	if (raw.size() == 0)			// Return back to caller if the passed string is no length.
		return;

	size_t start = 0;
	size_t end = 0;
	for (size_t i = 0; i < raw.size(); i++)
	{
		char c = raw.at(i);
		// Acquire tokens.
		if (c == delimiter)
		{
			end = i;
			int len = end - start;
			if (len > 0)
			{
				std::string token = raw.substr(start, len);
				tokens.push_back(token);		// Store extracted token into vector.
			}
			start = i + 1;
		}
	}
	// Acquire the final token.
	end = raw.size();
	int len = end - start;
	if (len > 0)
	{
		std::string token = raw.substr(start, len);
		tokens.push_back(token);
	}
}

std::string Parser::NextToken()
{
	std::string ret;
	if (HasMoreTokens())				// Check if any tokens are left.
	{									// Gets the next token available in the token buffer.
		ret = tokens.front();
		tokens.erase(tokens.begin());	// Erase the token from vector once used
		return ret;
	}
	else
	{
		std::string ret = "NULL";
		return ret;						// No more tokens left
	}
}