#include "date.h"

using namespace std;

Date::Date(Month month, int day, int year):
	month{month},
	day{day},
	year{year}
{
}

Date::Date():
	month{INVALID},
	day{0},
	year{0}
{
}

Date::~Date(void)
{
}

ostream& operator<<(ostream& out, const Date& d)
{
	//ask about static_cast<enum Month>(d.month)
	switch (d.month)
	{
	case 0: out << "Invalid ";
		break;
	case 1: out << "January ";
		break;
	case 2: out << "February ";
		break;
	case 3: out << "March ";
		break;
	case 4: out << "April ";
		break;
	case 5: out << "May ";
		break;
	case 6: out << "June ";
		break;
	case 7: out << "July ";
		break;
	case 8: out << "August ";
		break;
	case 9: out << "September ";
		break;
	case 10: out << "October ";
		break;
	case 11: out << "November ";
		break;
	case 12: out << "December ";
		break;
	}
	out << d.day << ", " << d.year << endl;
	return out;
}
