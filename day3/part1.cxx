#include <vector>
#include <bitset>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	vector<bitset<12>> diagnostics;
	string binNum = "";
	string gammaRate = "";
	string epsilonRate = "";

	int gamma = 0;
	int epsilon = 0;

	while (getline(cin, binNum))
	{
		reverse(binNum.begin(), binNum.end());
		diagnostics.push_back(bitset<12>(binNum));
	}

	for (int i = 0; i < 12; i++)
	{
		int on_bits = count_if(diagnostics.begin(), diagnostics.end(), [&](bitset<12> b) { return b.test(i); }); 
		int off_bits = count_if(diagnostics.begin(), diagnostics.end(), [&](bitset<12> b) { return !b.test(i); });

		if (on_bits > off_bits) {
			gammaRate += "1";
			epsilonRate += "0";
		} else {
			gammaRate += "0";
			epsilonRate += "1";
		}
	}

	gamma = stoi(gammaRate, nullptr, 2);
	epsilon = stoi(epsilonRate, nullptr, 2);

	cout << (gamma * epsilon) << endl;

	return 0;
}
