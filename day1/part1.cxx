#include <iostream>
#include <string>

using namespace std;

int main()
{
	string strReading = "";
	int lastReading = 0;
	int depthIncreases = 0;

	while (getline(cin, strReading))
	{
		int currentReading = stoi(strReading);
		if (lastReading == 0)
		{
			lastReading = currentReading;
			continue;
		}

		if (currentReading > lastReading)
			depthIncreases++;
		lastReading = currentReading;
	}
	
	cout << depthIncreases << endl;

	return 0;	
}
