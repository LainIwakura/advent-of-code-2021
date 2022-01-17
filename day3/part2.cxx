#include <vector>
#include <bitset>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int oxygenRate = 0;
int CO2Rate = 0;

void getCO2Rating(vector<bitset<12>>& diagnostics, int maxIndex)
{
	if (diagnostics.size() == 1)
	{
		CO2Rate = stoi(diagnostics[0].to_string(), nullptr, 2);
		return;
	}

	int on_bits = count_if(diagnostics.begin(), diagnostics.end(), [&](bitset<12> b) { return b.test(maxIndex); });
	int off_bits = count_if(diagnostics.begin(), diagnostics.end(), [&](bitset<12> b) { return !b.test(maxIndex); });

	bool keep_bits = (off_bits <= on_bits);
	erase_if(diagnostics, [&](bitset<12> b) { return ((keep_bits) ? b.test(maxIndex) : !b.test(maxIndex)); });

	getCO2Rating(diagnostics, maxIndex - 1);
}

void getOxygenRating(vector<bitset<12>>& diagnostics, int maxIndex)
{
	if (diagnostics.size() == 1)
	{
		oxygenRate = stoi(diagnostics[0].to_string(), nullptr, 2);
		return;
	}

	int on_bits = count_if(diagnostics.begin(), diagnostics.end(), [&](bitset<12> b) { return b.test(maxIndex); });
	int off_bits = count_if(diagnostics.begin(), diagnostics.end(), [&](bitset<12> b) { return !b.test(maxIndex); });

	bool keep_on_bits = (on_bits >= off_bits);
	erase_if(diagnostics, [&](bitset<12> b) { return ((keep_on_bits) ? !b.test(maxIndex) : b.test(maxIndex)); });

	getOxygenRating(diagnostics, maxIndex - 1);
}

int main()
{
	vector<bitset<12>> diagnostics;
	string binNum = "";


	while (getline(cin, binNum))
		diagnostics.push_back(bitset<12>(binNum));

	vector<bitset<12>> diagnostics2(diagnostics.begin(), diagnostics.end());

	getOxygenRating(diagnostics, 11);
	getCO2Rating(diagnostics2, 11);

	cout << (oxygenRate * CO2Rate) << endl;

	return 0;
}
