#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

int main()
{
	int times_appeared = 0;
	string whole_line = "";
	string signal_line = "";
	string output_val = "";
	stringstream ss;

	while (getline(cin, whole_line))
	{
		size_t pos = whole_line.find('|');
		signal_line = whole_line.substr(0, pos-1);
		output_val = whole_line.substr(pos+2);

		ss << output_val;
		string single_digit = "";
		while (getline(ss, single_digit, ' '))
			if (single_digit.length() == 2 || single_digit.length() == 3 || single_digit.length() == 4 || single_digit.length() == 7) 
				++times_appeared;

		ss.clear();
	}

	cout << times_appeared << endl;

	return 0;
}
