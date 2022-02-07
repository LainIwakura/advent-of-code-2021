#include <iostream>
#include <tuple>
#include <string>

using namespace std;

int main()
{
	string currentCommand = "";
	tuple<int, int, int> subCoords = make_tuple(0, 0, 0);

	while (getline(cin, currentCommand))
	{
		size_t pos = currentCommand.find(' ');
		string command = currentCommand.substr(0, pos);
		int value = stoi(currentCommand.substr(pos+1));

		if (command == "forward")
		{
			get<0>(subCoords) += value;
			if (get<2>(subCoords) == 0)
				continue;
			get<1>(subCoords) += (get<2>(subCoords) * value);
		}
		else if (command == "up")
		{
			get<2>(subCoords) -= value;
		}
		else if (command == "down")
		{
			get<2>(subCoords) += value;
		}
		else
		{
			cout << "Unrecognized command: " << command << endl;
		}
	}

	cout << (get<0>(subCoords) * get<1>(subCoords)) << endl;

	return 0;
}
