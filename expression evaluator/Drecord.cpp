// File: Drecord.cpp
// Class implementation: Drecord

#include "Drecord.h"
#include <iostream>

Drecord::Drecord()
{
	key = "NULL";
	rank = 0;
	balance = 0.0;
}

void Drecord::getnewDrecord(Drecord* newRec)
{
	std::string newKey;
	std::cout << "Enter the key value: ";
	std::cin >> newKey;
	newRec->setKey(newKey);
	std::cin.ignore();
	std::cin.clear();
}
