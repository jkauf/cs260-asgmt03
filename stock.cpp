#include <iomanip>
#include <cstring>
#include "stock.h"

using namespace std;

Stock::Stock(char const * const symbol, char const * const name, int sharePrice, Date priceDate):
	symbol{strcpy(new char[strlen(symbol)+1], symbol)},
	name{strcpy(new char[strlen(name)+1], name)},
	sharePrice{sharePrice},
	priceDate{priceDate}

{
}

Stock::Stock(void):
	//initialize to null/zero
	symbol{nullptr},
	name{nullptr},
	sharePrice{0},
	priceDate{}
{
}

Stock::~Stock(void)
{
	
	delete [] symbol;
	delete [] name;
	symbol = nullptr;
	name = nullptr;
	
}

char const * const Stock::getSymbol(void) const
{
	return symbol;	// change this to return the actual stock symbol
}


Stock& Stock::operator=(const Stock& s)
{
	//Stock* aStock;
	//aStock = new Stock(s.symbol, s.name, s.sharePrice, s.priceDate);
	this->symbol = strcpy(new char[strlen(s.symbol)+1], s.symbol);
	this->name = strcpy(new char[strlen(s.name)+1], s.name);
	this->sharePrice = s.sharePrice;
	this->priceDate = s.priceDate;

	return *this;
}
/*
you can choose to implement any of the next 3 items if necessary --
if not, feel free not to implement them

Stock::Stock(const Stock& s)
{
}



Stock& Stock::operator=(Stock const * const s)
{
	return *this;
}
*/

// display column headers for printout of stocks
void Stock::displayHeaders(ostream& out)
{
	// print something like this:
	//
	//  symbol  name                                      price   date
	//  ------  ----                                      -----   ----
	out << left << "symbol" << "  "
		<< "name" << setw(38) << ""
		<< "price" << "   " << "date" << endl
		<< left << setfill('-')
		<< setw(6) << ""
		<< "  "
		<< setw(4) << ""
		<< setfill(' ') << setw(38) << ""
		<< setfill('-') << setw(5) << ""
		<< "   " << setw(4) << "" << setfill(' ') <<  endl;
}

// print share price as DOLLARS
// (e.g. 2483 would print out as 24.83 and 200 would print out as 2.00)
ostream& operator<<(ostream& out, const Stock& s)
{
	int dollars, cents;
	dollars = s.sharePrice / 100;
	cents = s.sharePrice - (dollars * 100);
	out << left << setfill(' ') <<  setw(6) << s.symbol << "  "
		<< setw(42) << s.name
		<< setw(2) << right << dollars << '.' << setw(2) << setfill('0') << cents << "   "
		<< s.priceDate << setfill(' ');
	return out;
}
