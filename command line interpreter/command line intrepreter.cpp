// Din Bostandzic
// CISP 400 Final Project. This program is a command line intrepreter that 
// takes in user input based on commands entered, then parses commands 
// and converts to common case, trims, then the input is executed if valid.
// The final results of the command are displayed with their answers produced.
// A .txt file is also read in using batch processing and the commands 
// from it are parsed/same process used as described above is performed.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Function prototypes
void ProcessCommand(string cmd);
string strtolower(string str);
string trim(string str);
void TokenMaker2Args(string& userInput, int& arg1, int& arg2);
void TokenMaker3Args(string& userInput, int& arg1, int& arg2, int& arg3);
void ProcessScript(string script);
string factorialFinder(int factNum);
void ExitProgram();

// Class definition of EZFileRead 
class EZFileRead 
{
	private:
		vector<string> v;			// Private variable v as vector of strings to be used for storing data from file read in

	public:
		EZFileRead(string);			// Class constructor	
		size_t GetNumLines();		// Function used for total number of lines in file being read in
		string GetLine(size_t);		// Function used to access a specific line in file being read in
		int failed = 0;
};

// Class definition of Tokenizer
class Tokenizer 
{
	private:
		vector <string> tokens;			// Store the extracted tokens

	public:
		Tokenizer(string, char);		// Class constructor
		int GetNumTokens();				// Total number of tokens
		bool HasMoreTokens();			// Check if there are any tokens left
		string NextToken();				// Move on to the next token
};

// Function definition of EZFileRead constructor
EZFileRead::EZFileRead(string filename) 
{
	ifstream f;					// Create file to be used for input
	f.open(filename);			// Open the file to be read in
	if (!f.is_open())			// Check if the file exists
	{			
		cout << "File not successfully opened...operation aborted." << endl;
		failed = 1;
		return;
	}
	// Read in the file (if there is anything to read)
	string inp;
	while (getline(f, inp))
		v.push_back(inp);
	f.close();					// Close the file
}

// Function definition of GetNumLines, which returns the total number of lines
// in the file that is being read in
size_t EZFileRead::GetNumLines() 
{
	return v.size();			// Return the current size of the vector
}

// Function definition of GetLine, access the specified line in the file
string EZFileRead::GetLine(size_t index) 
{
	if (index >= v.size())					// Check to make sure line num in bounds
		return "NO SUCH ELEMENT";

	return v.at(index);
}

// Function defintion of Tokenizer constructor
Tokenizer::Tokenizer(string raw, char delimiter) 
{
	if (raw.size() == 0)			// Return back to caller if the passed string is no length
		return;
	size_t start = 0;
	size_t end = 0;
	for (size_t i = 0; i < raw.size(); i++) 
	{
		char c = raw.at(i);
		// Acquire tokens
		if (c == delimiter) 
		{
			end = i;
			int len = end - start;
			if (len > 0) 
			{
				string token = raw.substr(start, len);
				tokens.push_back(token);
			}
			start = i + 1;
		}
	}
	// Acquire the final token
	end = raw.size();
	int len = end - start;
	if (len > 0) 
	{
		string token = raw.substr(start, len);
		tokens.push_back(token);
	}
}

// Function definition of GetNumTokens 
int Tokenizer::GetNumTokens() 
{
	return tokens.size();		// Return how many tokens are in token buffer
}

// Function definition of HasMoreTokens
bool Tokenizer::HasMoreTokens() 
{
	return tokens.size() != 0;		// Returns whether there are any more tokens in buffer 
}

// Function definition of NextToken
string Tokenizer::NextToken() 
{
	string ret = "NULL";
	if (HasMoreTokens()) 
	{									// Gets the next token available in the token buffer
		ret = tokens.front();
		tokens.erase(tokens.begin());
	}
	return ret;
}


int main()
{
	//////// MAKE SURE ALL VALUES IN OUTPUT ARE FORMATTED RIGHT and string formt
	string cmd = " ";
	// Program description and list of available commands
	cout << "SCRIPTING/COMMAND LINE INTREPRETER PROGRAM" << endl;
	cout << "List of commands: project, points, display, sqrt, log2, add, sub, mul, div, mod, shr, shl, add3, mul3, fact, load, quit" << endl;
	cout << string(119, '*') << endl << endl;

	while (1)
	{			// User inputs desired command string which gets processsed 
		cout << "Enter a command to process (type quit to exit program): ";
		getline(cin, cmd);								
		ProcessCommand(cmd);
	}

	system("pause");
	return 0;
}

// Function definition of ProcessCommand, takes in string inputted by user,
// depending on specified command entered comparisons are performed to get
// to the proper procedure desired, if there are arguments and any spaces or
// upper/mixed case, the strings are trimmed and processed accordingly.
void ProcessCommand(string cmd) 
{
	int arg1, arg2, arg3 = 0;			// To be passed by reference
	int answer = 0;						// Store the result of operation on arguments
	
	cmd = strtolower(cmd);				// Convert string to lower case
	cmd = trim(cmd);					// Trim out all the leading and trailing whitespaces in string

	if (cmd.compare("quit") == 0)		// When user enters quit, program terminates
		ExitProgram();
	else if (cmd.compare("project") == 0)	// When user enters project display the description of the final project
		cout << "This is the final project for CISP 400" << endl;
	else if (cmd.compare("points") == 0)	// When user enters points display the total points for the final project
		cout << "This assignment is worth 250 points" << endl;
	else if (cmd.compare("display") == 0)	// When user enters display allow for any string to be entered which will be displayed
	{
		string msg = " ";
		cout << "display: ";
		getline(cin, msg);					// Input the desired string to be displayed
		cout << msg << endl;
	}
	else if (cmd.compare("sqrt") == 0)		// When user enters sqrt display the square root of a desired number
	{
		int value = 0;
		cout << "sqrt: ";
		cin >> value;						// Input the number to be "square rooted", then display
		cout << "The sqrt of " << to_string(value) << " is: " << to_string(static_cast<int>(sqrt(value))) << endl;
		cin.ignore();
		cin.clear();						// Clear the input buffer
	}
	else if (cmd.compare("log2") == 0)		// When user enters log2 display the log (base 2) of a desired number
	{
		int log = 0;
		cout << "log2: ";
		cin >> log;							// Input the number to be "logged", then display
		cout << "The log2 of " << to_string(log) << " is: " << to_string(static_cast<int>(log2(log))) << endl;
		cin.ignore();
		cin.clear();						// Clear the input buffer
	}
	else if (cmd.compare("add") == 0)		// When user enters add, enter 2 numbers to be added whose sum is displayed
	{
		string addNum = " ";
		cout << "add: ";
		getline(cin, addNum);				// Enter the 2 numbers to be added separated by comma
		TokenMaker2Args(addNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in addition
		answer = (arg1 + arg2);					// Perform addition and display
		cout << to_string(arg1) + " + " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("sub") == 0)		// When user enters sub, enter 2 numbers to be subtracted whose difference is displayed
	{
		string subNum = " ";
		cout << "sub: ";
		getline(cin, subNum);				// Enter the 2 numbers to be subtracted separated by a comma
		TokenMaker2Args(subNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in subtraction
		answer = (arg1 - arg2);					// Perform subtraction and display
		cout << to_string(arg1) + " - " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("mul") == 0)		// When user enters mul, enter 2 numbers to be multiplied whose product is displayed
	{
		string mulNum = " ";
		cout << "mul: ";
		getline(cin, mulNum);				// Enter in the 2 numbers to be multiplied, separated by comma
		TokenMaker2Args(mulNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in multiplication
		answer = (arg1 * arg2);					// Perform multiplication and display
		cout << to_string(arg1) + " * " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("div") == 0)		// When user enters div, enter 2 numbers to be divided whose quotient is displayed
	{
		string divNum = " ";
		cout << "div: ";
		getline(cin, divNum);				// Enter the 2 numbers to be divided separated by comma
		TokenMaker2Args(divNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in division
		if (arg2 == 0)							// Check for dividing by 0
			cout << "Dividing by zero is undefined!" << endl;
		else
		{
			answer = (arg1 / arg2);				// Perform the division and displau
			cout << to_string(arg1) + " / " + to_string(arg2) + " = " + to_string(answer) << endl;
		}
	}
	else if (cmd.compare("mod") == 0)		// When user enters mod, perform modulo on the 2 specified number
	{
		string modNum = " ";
		cout << "mod: ";
		getline(cin, modNum);				// Enter the 2 numbers whose modulus will be taken, separated by comma
		TokenMaker2Args(modNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in modulus	
		answer = (arg1 % arg2);					// Perform modulo and display
		cout << to_string(arg1) + " % " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("shr") == 0)		// When user enters shr, perform bitwise shift right operation
	{
		string shrNum = " ";
		cout << "shr: ";
		getline(cin, shrNum);				// Enter the 2 numbers first num is the desired num, second num is how many bits to shift
		TokenMaker2Args(shrNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in the shr procedure
		answer = (arg1 >> arg2);				// Peform the shift right on the number and display
		cout << to_string(arg1) + " >> " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("shl") == 0)		// When user enters shl, perform bitwise shift leftwise operation
	{
		string shlNum = " ";
		cout << "shl: ";
		getline(cin, shlNum);				// Enter the 2 numbers first num is the desired num, second num is how many bits to shift
		TokenMaker2Args(shlNum, arg1, arg2);	// Call TokenMaker2Args to "extract" the numbers from string to be used in the shl procedure
		answer = (arg1 << arg2);				// Peform the shift left on the number and display
		cout << to_string(arg1) + " << " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("add3") == 0)		// When user enters add3, perform addition on 3 specified numbers
	{
		string add3Num = " ";
		cout << "add3: ";
		getline(cin, add3Num);				// Enter the 3 numbers to be added, separated by commas
		TokenMaker3Args(add3Num, arg1, arg2, arg3);		// Call TokenMaker3Args to "extract" the 3 numbers from string to be used add3
		answer = (arg1 + arg2 + arg3);					// Perfom the addition and display
		cout << to_string(arg1) + " + " + to_string(arg2) + " + " + to_string(arg3) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("mul3") == 0)		// When user enters mul3, perform multiplication on 3 specified numbers
	{
		string mul3Num = " ";
		cout << "mul3: ";
		getline(cin, mul3Num);				// Enter the 3 numbers to be multiplied, separated by comma
		TokenMaker3Args(mul3Num, arg1, arg2, arg3);		// Call TokenMaker3Args to "extract" the 3 numbers from string to be used mul3
		answer = (arg1 * arg2 * arg3);					// Perfom the multiplication and display
		cout << to_string(arg1) + " * " + to_string(arg2) + " * " + to_string(arg3) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("fact") == 0)		// When user enters fact, perform factorial on the specified number
	{
		int factNum = 0;
		cout << "fact: ";
		cin >> factNum;						// Enter a number to find its factorial
		string factorial = factorialFinder(factNum);	// Call factorialFinder to return the number's factorial as string to display
		cout << "Factorial " + to_string(factNum) + "!" + " is: " + factorial << endl;					
		cin.ignore();
		cin.clear();									// Clear the input buffer
	}
	else if (cmd.compare("load") == 0)		// When user enters load, load in the file to be read
	{
		string scriptName = " ";
		cout << "load: ";
		getline(cin, scriptName);			// Get the name of the desired file
										    // Place file in same directory as .cpp source file to be opened

		EZFileRead* ezr = new EZFileRead(scriptName);			// New object on heap for reading to file of entered file .txt
		size_t num2 = ezr->GetNumLines();						// Gets the number of lines that have been written on the file
		if (ezr->failed != 1)
		{
			cout << endl;
			cout << "Processing Script..." << endl;
			for (size_t i = 0; i < num2; i++)
			{
				ProcessScript(ezr->GetLine(i));			// Loop through to access each line of the file to be processed individually
			}
			cout << endl;
			delete ezr;									// Clean up dynamically allocated memory
		}
	}
	else if (cmd.compare("quit") == 0)				// When user enters quit, exit the program
	{
		ExitProgram();
	}
	else
	{
		cout << "Unknown Command" << endl;			// If user enters anything but the listed commands, return unknown command
	}
}

// Function definition of strtolower, converts a string no matter what case
// it is currently in, to all lower case
string strtolower(string str) 
{
	string ret = str;
	for (size_t i = 0; i < str.size(); i++)
	{
		ret.at(i) = tolower(str.at(i));		// Convert each character to lower case
	}
	return ret;
}

// Function definition of trim, takes a string and trims in down,
// returning a string without the leading and trailing whitespace
string trim(string str) 
{
	size_t first = str.find_first_not_of(' ');	// Find first character that isn't a space
	if (first == string::npos)			// If nothing is found return
		return "";
	if (string::npos == first)			// Go until end of string reached
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');	// Make end the first character that isn't a space
	return str.substr(first, (last - first + 1));	// Return trim starting at position first, going until length of string
}

// Function definition of TokenMaker2Args, takes in the passed (by reference)
// string and 2 numbers to be used for operations once "extracted" from the string
void TokenMaker2Args(string &numString, int& arg1, int& arg2)
{
	Tokenizer* t1 = new Tokenizer(numString, ',');			// Dynamically create new object on heap passing the string and comma as delimiter
	arg1 = stoi(trim(t1->NextToken()));						// Arg1 is the trimmed value up to the comma as string
	string tok1 = t1->NextToken();							// Go to next token
	tok1 = tok1.substr(0, tok1.length() + 1);				// The token is one spot above the comma
	arg2 = stoi(tok1);										// This is the second argument to be extracted
	delete t1;												// Clean up dynamically allocated memory
}

// Function definition of TokenMaker2Args, takes in the passed (by reference)
// string and 3 numbers to be used for operations once "extracted" from the string
void TokenMaker3Args(string& userInput, int& arg1, int& arg2, int& arg3)
{
	Tokenizer* t1 = new Tokenizer(userInput, ',');			// Dynamically create new object on heap passing the string and comma as delimiter
	arg1 = stoi(trim(t1->NextToken()));						// Arg1 is the trimmed value up to the first comma as string
	string tok1 = t1->NextToken();							// Go to next token
	tok1 = tok1.substr(0, tok1.length() + 1);				// The next token is extracted, located one spot above first comma
	arg2 = stoi(tok1);										// This is the second argument which gets extracted as string
	string tok2 = t1->NextToken();							// Go to next token which is second comma
	tok2= tok2.substr(0, tok2.length() + 1);				// The third argument is one spot about the second comma
	arg3 = stoi(tok2);										// This is the third argument that gets extracted
	delete t1;												// Clean up dynamically allocated memory
}

// Function definition of ProcessScript, takes in string value from an opened
// file that is being read in. Each line from the .txt file is parsed to get
// the specific command which get processed to display proper output.
void ProcessScript(string script)
{
	int arg1, arg2, arg3, answer = 0;					// Args passed by reference, answer used to store arithmetic operation answer
	Tokenizer* t1 = new Tokenizer(script, ':');		    // Dynamically create new object on heap passing the string and colon as delimiter
	string cmd = strtolower(trim(t1->NextToken()));		// Command one spot behind colon is converted to lower case and trimmed down
	string tok1 = t1->NextToken();						// Next token is value after colon			
	tok1 = tok1.substr(0, tok1.length() + 1);			// Extract the token which is one spot from colon
	string cmd2 = tok1;									// Assign the values that the commands will work with, to cmd2
	delete t1;											// Clean up dynamically allocated memory
	
	if (cmd.compare("project") == 0)		// If the command is project, display the details of the final project
		cout << "This is the final project for CISP 400" << endl;
	else if (cmd.compare("points") == 0)	// If the command is points, display the total points of the final project
		cout << "This assignment is worth 250 points" << endl;
	else if (cmd.compare("display") == 0)	// If the command is display, display the string after the colon
		cout << cmd2.substr(1,cmd2.length()) << endl;
	else if (cmd.compare("sqrt") == 0)		// If the command is sqrt, display the square root of number after colon
		cout << "The sqrt of 16 is: " + to_string(static_cast<int>(sqrt(stoi(cmd2)))) << endl;
	else if (cmd.compare("log2") == 0)		// If command is log2, display the log (base 2) of number after colon
		cout << "The log2 of 256 is: " + to_string(static_cast<int>(log2(stoi(cmd2)))) << endl;
	else if (cmd.compare("add") == 0)		// If command is add display the sum of the two numbers after colon
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		answer = (arg1 + arg2);				// Add the 2 numbers and display
		cout << to_string(arg1) + " + " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("sub") == 0)	// If command is sub display the difference of the two numbers after colon
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		answer = (arg1 - arg2);				// Subtract the 2 numbers and display
		cout << to_string(arg1) + " - " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("mul") == 0)	// If command is mul display the product of the two numbers after colon
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		answer = (arg1 * arg2);				// Multiply the 2 numbers and display
		cout << to_string(arg1) + " * " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("div") == 0)	// If command is div display the quotient of the two numbers after colon
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		if (arg2 == 0)						// Check if division by 0
			cout << "Dividing by zero is undefined!" << endl;
		else
		{
			answer = (arg1 / arg2);			// Perform division of the 2 numbers and display
			cout << to_string(arg1) + " / " + to_string(arg2) + " = " + to_string(answer) << endl;
		}
	}
	else if (cmd.compare("mod") == 0)		// If command is mod display the modulo given the 2 numbers
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		answer = (arg1 % arg2);				// Perform the modulus and display
		cout << to_string(arg1) + " % " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("shr") == 0)		// If command is shr display the value after bitwise shift right is performed on specified value 
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		answer = (arg1 >> arg2);			// Shift right by number of bits (arg2) and display
		cout << to_string(arg1) + " >> " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("shl") == 0)		// If command is shl display the value after bitwise shift left is performed on specified value
	{
		TokenMaker2Args(cmd2, arg1, arg2);	// Tokenize the string to remove comma delimiter
		answer = (arg1 << arg2);			// Shift left by number of bits(arg2) and display
		cout << to_string(arg1) + " << " + to_string(arg2) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("add3") == 0)		// If command is add3, display sum of 3 numbers	
	{
		TokenMaker3Args(cmd2, arg1, arg2, arg3);	// Tokenize the string to remove comma delimiter
		answer = (arg1 + arg2 + arg3);				// Perform addition of 3 numbers and display
		cout << to_string(arg1) + " + " + to_string(arg2) + " + " + to_string(arg3) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("mul3") == 0)		// If command is mul3, display product of 3 numbers 
	{
		TokenMaker3Args(cmd2, arg1, arg2, arg3);	// Tokenize the string to remove comma delimiter
		answer = (arg1 * arg2 * arg3);				// Perform multiplication of 3 numbers and display
		cout << to_string(arg1) + " * " + to_string(arg2) + " * " + to_string(arg3) + " = " + to_string(answer) << endl;
	}
	else if (cmd.compare("fact") == 0)		// If command is fact, find the factorial of the specified number
	{
		string factorial = factorialFinder(stoi(cmd2));		// Call the factorialFinder to return the factorial value to display
		cout << "Factorial" + cmd2 + "! " + "is: " + factorial << endl;
	}
	else
		cout << "Unknown Command" << endl;		// If none of the commands on file matched supported commands, return unknown command
}

// Function definition of factorialFinder, passed factNum gets multiplied by its
// decremented value and looped so on, until it gets to 1.
string factorialFinder(int factNum)
{
	int factorial = 1;
	for (size_t i = factNum; i >= 1; --i)
	{
		factorial *= i;			// Keep looping until the factNum is 1 and multiply it to running total factorial each time
	}
	return to_string(factorial);
}

// Function definition of ExitProgram allows for user to quit the program at any time
void ExitProgram() 
{
	exit(EXIT_SUCCESS);			// Exit successfully and terminate program when called
}