#include <iostream>
#include <string> 
#include <fstream>
#include "DateTime.h"

using namespace std;
// Start program hear
int main(void) {
	setlocale(LC_ALL, "Russian");

	DateTime TestData1 = "2023-10-16T07:54:34";
	cout << "Data1 " << TestData1 << "  => " << TestData1.total_days << " days" << '\n';

	DateTime TestData2 = "2021-12-10";
	cout << "Data2 " << TestData2 << "  => " << TestData2.total_days << " days" << '\n';

	DateTime TestData3 = "07:54:34";
	cout << "Data3 " << TestData3 << "  => " << TestData3.total_days << " days" << '\n' << '\n';


	cout << TestData1 << " + 366" << "  => " << TestData1 + 366 << '\n';

	cout << TestData1 << " - 366" << "  => " << TestData2 - 366 << '\n';

	cout << TestData2 << "- " << TestData1 << " = " << (TestData2 - TestData1) << " days" << '\n' << '\n';

	cout << TestData2 << " == " << TestData2 << " => " << (TestData2 == TestData2) << '\n';
	cout << TestData2 << " == " << TestData1 << " => " << (TestData2 == TestData1) << '\n';
	cout << TestData2 << " < " << TestData1 << " => " << (TestData2 < TestData1) << '\n';
	cout << TestData2 << " > " << TestData1 << " => " << (TestData2 > TestData1) << '\n' << '\n';

	cout << TestData1.weekday() << '\n';
	cout << TestData2.weekday() << '\n';
	cout << TestData3.weekday() << '\n' << endl;


	string line;
	ifstream File("Dates.txt");

	if (File.is_open()) {
		int lenght = 0;

		// count number of dates
		while (getline(File, line)) {
			if (not(line.empty())) {
				lenght++;
			}
		}
		File.close();
		ifstream File("Dates.txt");

		// take dates from File
		DateTime* Dates = new DateTime[lenght];		
		int pos = 0;
		while (getline(File, line)) {
			if (not(line.empty())) {
				Dates[pos] = line;
				//cout << Dates[pos] << endl;
				pos++;
			}
		}

		// Sort array
		fast_sort(Dates, 0, lenght-1);

		// print Soer array
		for (int i = 0; i < lenght; i++) {
			cout << Dates[i] << endl;
		}

		delete[] Dates;
		File.close();
		}
	else {
		cout << "Error - file not found" << '\n';
	}


	DateTime when_ester1 = "2023-01-01";
	cout << '\n' << "ester date in 2023 => " << when_ester1.easter() << endl;
	DateTime when_ester2 = "2024-01-01";
	cout << "ester date in 2024 => " << when_ester2.easter() << endl;
	

}