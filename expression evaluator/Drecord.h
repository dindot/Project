// File: Drecord.h
// Class provided: Drecord
//
// Constructors for Drecord class:
//		Drecord()
//		postcondition: initialize key, rank, balance to null
//
//		Drecord(int newRank, int newBalance)
//		postcondition: initialize rank and balance with values passed
//
//		Drecord(const Drecord& newRecord)
//		postcondition: copy values from rank and balance to newRecord
//
// Manipulator/Accessor functions for Drecord class:
//		void setKey(string newKey) 
//		postcondition: key gets set with value from newKey
//
//		string getKey()
//		postcondition: return key as string
//
//		void setPrev(Drecord* previous)
//		postcondition: prev gets set with pointer previous to Drecord
//
//		Drecord* getPrev() 
//		postcondition: returns prev as pointer to Drecord
//
//		void setNext(Drecord* nextRec)
//		postcondition: sets next with pointer nextRec to Derecord
//
//		Drecord* getNext() 
//		postcondition: returns next as pointer to Drecord
//
//		void getnewDrecord(Drecord* newRec)
//		postcondition: sets newRec key field with the new key
//
//		void setRank(int newRank)
//		postcondition: sets rank with value passed in newRank
//
//		int getRank()
//		postcondition: returns rank as int
//
//		void setBalance(double newBalance) 
//		postcondition: sets balance with value passed in newBalance
//
//		double getBalance() 
//		postcondition: returns balance as double

#ifndef DRECORD_H
#define DRECORD_H
#include <iostream>

class Drecord
{
	private:
		std::string key;
		Drecord* prev;
		Drecord* next;
		int rank;
		double balance;

	public:
		Drecord();
		Drecord(int Newrank, double Newbalance) { rank = Newrank; balance = Newbalance; }
		Drecord(const Drecord& newRecord) { rank = newRecord.rank; balance = newRecord.balance; }
		void setKey(std::string newKey) { key = newKey; }
		std::string getKey() { return key; }
		void setPrev(Drecord* previous) { prev = previous; }
		Drecord* getPrev() { return prev; }
		void setNext(Drecord* nextRec) { next = nextRec; }
		Drecord* getNext() { return next; }
		void getnewDrecord(Drecord* newRec);
		void setRank(int newRank) { rank = newRank; }
		int getRank() { return rank; }
		void setBalance(double newBalance) { balance = newBalance; }
		double getBalance() { return balance; }
};
#endif
