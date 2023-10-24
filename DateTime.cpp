#include <iostream>
#include <string>
#include "DateTime.h"

using namespace std;


// enter data
DateTime::DateTime(const char* data) {
	// give names for all arguments
	int& years = arg[0];
	int& months = arg[1];
	int& days = arg[2];
	int& hours = arg[3];
	int& minutes = arg[4];
	int& seconds = arg[5];

	int buffer = 0;
	int pos = 0;

	// finding lenght of data array
	int Size = 0;
	while (data[Size] != '\0') Size++;

	for (int i = 0; i < Size; i++) {
		// if we can convert elen to int - add it in buffer
		if ((int)data[i] > 47 && (int)data[i] < 58) {
			buffer = buffer * 10 + (data[i] - '0');

			// if this is the last elem add it
			if (i == Size - 1) {
				arg[pos] = buffer;
				buffer = 0;
			}
		}// if we can't convert elen to int - save buffer date
		else {
			// if we need to add date or we need to finish adding data
			if (data[i] == '-' || data[i] == 'T') {
				arg[pos] = buffer;
				buffer = 0;
			}

			// if we need to add time
			else if (data[i] == ':') {
				// if we don't neet to add date
				if (pos < 3) {
					pos = 3;
				}
				arg[pos] = buffer;
				buffer = 0;
			}
			else {
				cout << "Err - not correct date";
				break;
			}
			pos++;
			// if we can count total number of days
			if (pos <= 3 && total_days == -1) {
				days_counting(*this);
			}
		}
	}
}


// enter data
DateTime::DateTime(const string data) {
	// give names for all arguments
	int& years = arg[0];
	int& months = arg[1];
	int& days = arg[2];
	int& hours = arg[3];
	int& minutes = arg[4];
	int& seconds = arg[5];

	int buffer = 0;
	int pos = 0;

	// finding lenght of data array
	int Size = 0;
	while (data[Size] != '\0') Size++;

	for (int i = 0; i < Size; i++) {
		// if we can convert elen to int - add it in buffer
		if ((int)data[i] > 47 && (int)data[i] < 58) {
			buffer = buffer * 10 + (data[i] - '0');

			// if this is the last elem add it
			if (i == Size - 1) {
				arg[pos] = buffer;
				buffer = 0;
			}
		}// if we can't convert elen to int - save buffer date
		else {
			// if we need to add date or we need to finish adding data
			if (data[i] == '-' || data[i] == 'T') {
				arg[pos] = buffer;
				buffer = 0;
			}

			// if we need to add time
			else if (data[i] == ':') {
				// if we don't neet to add date
				if (pos < 3) {
					pos = 3;
				}
				arg[pos] = buffer;
				buffer = 0;
			}
			else {
				cout << "Err - not correct date";
				break;
			}
			pos++;
			// if we can count total number of days
			if (pos <= 3 && total_days == -1) {
				days_counting(*this);
			}
		}
	}
}


//  print data operator
ostream& operator <<(ostream& out, const DateTime& data) {
	for (int i = 0; i < num; i++) {
		if (data.arg[i] != -1) {
			out << data.arg[i];
			// add special symbols
			if (i < 2) {
				out << "-";
			}
			else if (i == 2) {
				out << " ";
			}
			else if (i > 2 && i != num - 1) {
				out << ":";
			}
		}
	}
	return out;
}



// function that count total numer of days in entered date
void DateTime::days_counting(DateTime& data) {
	// give names for all arguments
	int& years = arg[0];
	int& months = arg[1];
	int& days = arg[2];

	// count total number of  days
	total_days = 0;

	// days in all years defore today year
	for (int year = 1; year < years; year++) {
		if (year % 4 == 0) {
			total_days += leap_year[0];
		}
		else {
			total_days += normal_year[0];
		}
	}

	// finding today year tipe
	if (years % 4 == 0) {
		// days in today year (leap year)
		for (int month = 1; month < months; month++) {
			total_days += leap_year[month];
		}
	}
	else {
		// days in today year (normal year)
		for (int month = 1; month < months; month++) {
			total_days += normal_year[month];
		}
	}
	// days in today month
	total_days += days;
}


// operator - another DataTime
int DateTime::operator -(const DateTime data) const {
	if (data.total_days == -1 || total_days == -1) {
		cout << "Error uncorrect datas";
		return 0;
	}
	int res = total_days - data.total_days;
	return res;
}



//operator -=
DateTime& DateTime::operator -=(const int& days_num) {
	// give names for all arguments
	int& years = arg[0];
	int& months = arg[1];
	int& days = arg[2];

	total_days -= days_num;
	int add_days = days_num;

	const int* year_now{ normal_year };
	// finding today year tipe
	if (years % 4 == 0) {
		const int* year_now{ normal_year };
	}
	else {
		const int* year_now{ leap_year };
	}

	// start days adding
	while (add_days > 0) {
		// add days
		if (add_days <= days) {
			days -= add_days;
			add_days = 0; // finish adding
		}
		else {
			add_days -= days;
			months -= 1; // go to previous month

			if (months < 1) {
				months = 12;
				years -= 1; // go to previous year
				// finding today year tipe
				if (years % 4 == 0) {
					const int* year_now{ normal_year };
				}
				else {
					const int* year_now{ leap_year };
				}
			}
			days = *(year_now + months);
		}
	}
	return *this;
}

//operator -
DateTime DateTime::operator -(const int& days_num) const {
	DateTime res(*this);
	return (res -= days_num);
}



// operator +=
DateTime& DateTime::operator +=(const int& days_num) {
	// give names for all arguments
	int& years = arg[0];
	int& months = arg[1];
	int& days = arg[2];

	total_days += days_num;
	int add_days = days_num;

	const int* year_now{ normal_year };
	// finding today year tipe
	if (years % 4 == 0) {
		const int* year_now{ normal_year };
	}
	else {
		const int* year_now{ leap_year };
	}

	// start days adding
	while (add_days > 0) {
		// add days
		if (add_days <= *(year_now + months) - days) {
			days += add_days;
			add_days = 0; // finish adding
		}
		else {
			add_days -= *(year_now + months) - days + 1;
			days = 1;
			months += 1; // go to next month

			if (months > 12) {
				months = 1;
				years += 1; // go to next year
				// finding today year tipe
				if (years % 4 == 0) {
					const int* year_now{ normal_year };
				}
				else {
					const int* year_now{ leap_year };
				}
			}
		}
	}
	return *this;
};

// operator +
DateTime DateTime::operator +(const int& days_num) const {
	DateTime res(*this);
	return (res += days_num);
}



// logic operators

	// operator ==
bool DateTime::operator ==(const DateTime& data) const {
	return (total_days == data.total_days);
}

// operator !=
bool DateTime::operator !=(const DateTime& data) const {
	return (total_days != data.total_days);
}

// operator >
bool DateTime::operator >(const DateTime& data) const {
	return (total_days > data.total_days);
}

// operator >=
bool DateTime::operator >=(const DateTime& data) const {
	return (total_days >= data.total_days);
}

// operator <
bool DateTime::operator <(const DateTime& data) const {
	return (total_days < data.total_days);
}

// operator <=
bool DateTime::operator <=(const DateTime& data) const {
	return (total_days <= data.total_days);
}


// count day of week
string DateTime::weekday() {
	// give names for all arguments
	int& years = arg[0];
	int& months = arg[1];
	int& days = arg[2];

	if (years <= 0 or months <= 0 or days <= 0) {
		return "Error - swrong data";
	}

	int LeapYears = (int)years / 4;
	long a = (years - LeapYears) * 365 + LeapYears * 366;
	if (months >= 2) a += 31;
	if (months >= 3 && (int)years / 4 == years / 4) a += 29;
	else if (months >= 3) a += 28;
	if (months >= 4) a += 31;
	if (months >= 5) a += 30;
	if (months >= 6) a += 31;
	if (months >= 7) a += 30;
	if (months >= 8) a += 31;
	if (months >= 9) a += 31;
	if (months >= 10) a += 30;
	if (months >= 11) a += 31;
	if (months == 12) a += 30;
	a += days;
	int b = (a - 2) % 7;
	switch (b) {
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	case 7:
		return "Sunday";
	}
}


// count easter date
DateTime DateTime::easter() {
	// give names for all arguments
	const int& year = arg[0];
	// ester date
	DateTime Ester;
	if (year < 0) {
		cout << "Error - wrong date";
		Ester = "0000-00-00";
		return Ester;
	}

	int a = (19 * (year % 19) + 15) % 30;
	int b = (2 * (year % 4) + 4 * (year % 7) + 6 * a + 6) % 7;

	if (a + b > 10) {
		int day = a + b - 9;
		string ester = to_string(year) + "-04-" + to_string(day);
		Ester = ester;
		Ester += 13;
		return Ester;
	}
	else {
		int day = a + b + 22;
		string ester = to_string(year) + "-03-" + to_string(day);
		Ester = ester;
		Ester += 13;
		return Ester;
	}
}



// fast sort
void fast_sort(DateTime* &arr, int first, int last) {
	
	int i = first, j = last;
	int senter = arr[(last + first) / 2].total_days;
	do {
		while (arr[i].total_days < senter && i < last) { // если первый элемент меньше центра и не дошёл до левой половины, мы берем следующий
			i++;
		}
		while (arr[j].total_days > senter && j > first) { // если последний элемент больше центра и не дошёл до правой половины, мы берем следующий
			j--;
		}
		if (i <= j) {
			if (arr[i] > arr[j]) { // если первый элемент больше последнего, меняем их 
				DateTime swap = arr[i];
				arr[i] = arr[j];
				arr[j] = swap;
			}
			i++; j--;
		}
	} while (i < j);
	if (first < j) {	// если центр меньше крайнего левого элемента, сортируем левую часть
		fast_sort(arr, first, j);
	}
	if (i < last) {		// если центр меньше правого крайнего элемента, сортируем правую часть
		fast_sort(arr, i, last);
	}
}