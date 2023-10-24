#ifndef _DATETIME
#define _DATETIME

#include <iostream>
#include <string> 
using namespace std;

// number of value in class
const int num = 6;

// days in normal year
const int normal_year[13] = { 365, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// days in leap year
const int leap_year[13] = { 366, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// class to contain date and time
class DateTime {
	// user can use
public:
	// all arguments
	int arg[num] = { -1,-1,-1,-1,-1,-1 };


	// total number of days
	int total_days = -1;

	// enter data 
	DateTime() {}

	// enter data from char array
	DateTime(const char* data);

	// enter data from string
	DateTime(const string data);

	// print data operator
	friend ostream& operator <<(ostream& out, const DateTime& data);


	// operators

	// operator +=
	DateTime& operator +=(const int& days_num);

	// operator +
	DateTime operator +(const int& days_num) const;


	// operator -=
	DateTime& operator -=(const int& days_num);

	// operator -
	DateTime operator -(const int& days_num) const;

	// operator - another DataTime
	int operator -(const DateTime data) const;


	// logic operators

	// operator ==
	bool operator ==(const DateTime& data) const;

	// operator !=
	bool operator !=(const DateTime& data) const;

	// operator >
	bool operator >(const DateTime& data) const;

	// operator >=
	bool operator >=(const DateTime& data) const;

	// operator <
	bool operator <(const DateTime& data) const;

	// operator <=
	bool operator <=(const DateTime& data) const;


	// additional function

	// count day of week
	string weekday();

	// count easter date
	DateTime easter();

	// user can't use
private:
	// countin total number of days
	void days_counting(DateTime& data);

};


// fast sort
void fast_sort(DateTime* &arr, int first, int last);

#endif