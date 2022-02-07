#include <iostream>
#include <utility>
#include <string>

using namespace std;

int main()
{
	string currentCommand = "";
	pair<int, int> position = make_pair(0, 0);

	while (getline(cin, currentCommand))
	{
		size_t pos = currentCommand.find(' ');
		string command = currentCommand.substr(0, pos);
		int value = stoi(currentCommand.substr(pos+1));

		if (command == "forward")
		{
			position.first += value;
		}
		else if (command == "up")
		{
			position.second -= value;
		}
		else if (command == "down")
		{
			position.second += value;
		}
		else
		{
			cout << "Unrecognized command: " << command << endl;
		}
	}

	cout << (position.first * position.second) << endl;

	return 0;
}
