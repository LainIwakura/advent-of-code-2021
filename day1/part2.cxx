#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string strReading = "";
	int lastReading = 0;
	int depthIncreases = 0;
	vector<int> depths;
	vector<int> windowedSums;

	while (getline(cin, strReading))
		depths.push_back(stoi(strReading));
	
	for (auto e = depths.begin(); e != depths.end() - 2; ++e)
	{
		int sum = *e + *(e + 1) + *(e + 2);
		windowedSums.push_back(sum);
	}

	for (auto const& e : as_const(windowedSums))
	{
		if (lastReading == 0)
		{
			lastReading = e;
			continue;
		}

		if (e > lastReading)
			depthIncreases++;

		lastReading = e;
	}

	cout << depthIncreases << endl;

	return 0;	
}
