#include "hashmap.h"
#include <cstring>
#include <iostream>

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	HashMap::YOUR_NAME[] = "Julian Kaufman";

HashMap::HashMap(int capacity):
	capacity{capacity},
	slots{new Slot[capacity]},
	nStocks{0}
{
}

HashMap::~HashMap(void)
{
	delete [] slots;
	slots = nullptr;
}

bool HashMap::get(char const * const symbol, Stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& seqLength)
	 const
{
	// If the symbol is not found, this function is required
	// to set usedIndex to -1 before it returns false.
	symbolHash = HashMap::hashStr(symbol);
	hashIndex = symbolHash % capacity;
	usedIndex = hashIndex;
	seqLength = 1;
	
	for(;;)
	{
		//slot empty
		if (slots[usedIndex].slotStatus == 0)
		{
			usedIndex = -1;
			return false;
		}
		
		//slot full
		else if (slots[usedIndex].slotStatus == 1)
		{
			//correct stock found
			if(symbolHash == (HashMap::hashStr(slots[usedIndex].slotStock.getSymbol())))
				return true;
			//keep looking
			else
			{
				seqLength++;
				usedIndex == ((unsigned int)capacity - 1) ? usedIndex = 0 : usedIndex++;
			}
		}
		
		//slot was full, keep looking
		else if (slots[usedIndex].slotStatus == 2)
		{
			seqLength++;
			usedIndex == ((unsigned int)capacity - 1) ? usedIndex = 0 : usedIndex++;
		}

		//searched entire table
		else if (seqLength == (unsigned int)capacity)
		{
			usedIndex = -1;
			return false;
		}

	}

}

bool HashMap::put(const Stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& seqLength)
{
	symbolHash = HashMap::hashStr(s.symbol);
	hashIndex = symbolHash % capacity;
	usedIndex = hashIndex;
	seqLength = 1;
	
	//target hashIndex was never full
	if (slots[usedIndex].slotStatus == 0 || slots[usedIndex].slotStatus == 2)
	{
		slots[usedIndex].slotStock = s;
		slots[usedIndex].slotStatus = IS_FULL;
		nStocks++;
		return true;
	}

	for(;;)
	{
		usedIndex == ((unsigned int)capacity - 1) ? usedIndex = 0 : usedIndex++;
		seqLength++;
		
		//search for stock
		//stock exists already
		if (slots[usedIndex].slotStatus == 0 || slots[usedIndex].slotStatus == 2)
		{
			slots[usedIndex].slotStock = s;
			slots[usedIndex].slotStatus = IS_FULL;
			nStocks++;
			return true;
		}
		else if(symbolHash == (HashMap::hashStr(slots[usedIndex].slotStock.getSymbol())))
			return false;
		
		//search for stock
		//ask about this
		//"binding discards qualifiers"
		/*
		if (HashMap::get(s.getSymbol(), s, symbolHash, hashIndex, usedIndex, seqLength))
			return false;
		*/
		
		
		
	}
	
}

bool HashMap::remove(char const * const symbol, Stock& s,
					 unsigned int& symbolHash, unsigned int& hashIndex,
					 unsigned int& usedIndex, unsigned int& seqLength)
{
	bool found;
	found = HashMap::get(symbol, s, symbolHash, hashIndex, usedIndex, seqLength);
	if (found)
	{
		slots[usedIndex].slotStatus = WAS_FULL;
		delete [] slots[usedIndex].slotStock.name;
		slots[usedIndex].slotStock.name = nullptr;
		delete [] slots[usedIndex].slotStock.symbol;
		slots[usedIndex].slotStock.symbol = nullptr;
		nStocks--;
		return true;
	}
	else	
		return false;
}

unsigned int HashMap::hashStr(char const * const s)
{
	// Hash C string argument using the formula in java.lang.String.hashCode():
	//
	//   s[0]*(31^(n-1)) + s[1]*(31^(n-2)) + ... + s[n-1]
	//
	// s is the array of characters, n is the number of characters in the string,
	// and 31^n means 31 to the nth power.
	//
	// This function is declared static because its result depends
	// only on the characters in the string. You will need to apply
	// the modulo operator to the result of this function to generate
	// the required table index. The place to do this is in the functions
	// that call this function.
	//
	// You can and should do this computation entirely with integers. In other
	// words, there is no need to use floating point values. In particular, you
	// should not use the pow() function from <math.h> in this lab.
	
	int size = strlen(s);
	int sum = 0;
	int item = 0;

	for (int i = 0; i < size; i++)
	{
		sum *= 31;
		item = (int)s[i];
		sum += item;
	}		
	return sum;
}

ostream& operator<<(ostream& out, const HashMap &h)
{
	//out << "<print the contents of the HashMap>" << endl;
	if (h.nStocks == 0)
		out << "no stocks" << endl;
	else
	{
		Stock::displayHeaders(out);
		for (int i = 0; i < h.capacity; i++)
		{
			if (h.slots[i].slotStatus == 1)
			out << h.slots[i].slotStock;
		}	
	}

	return out;
}
