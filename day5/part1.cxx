#include <vector>
#include <iostream>
#include <utility>
#include <tuple>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

int main()
{
	vector<pair<tuple<int, int>, tuple<int, int>>> coords;
	string coord_line = "";
	regex coord_regex("^(\\d+),(\\d+)\\s{1}->\\s{1}(\\d+),(\\d+)$");
	smatch coord_match;

	while (getline(cin, coord_line))
	{
		if (regex_match(coord_line, coord_match, coord_regex))
		{
			int x1 = stoi(coord_match[1]);
			int y1 = stoi(coord_match[2]);
			int x2 = stoi(coord_match[3]);
			int y2 = stoi(coord_match[4]);

			coords.push_back(make_pair(make_tuple(x1, y1), make_tuple(x2, y2)));
		}	
	}

	for (auto const& c : coords)
	{
		cout << get<0>(c.first) << " " << get<1>(c.first) << " " << get<0>(c.second) << " " << get<1>(c.second) << endl;
	}

	return 0;
}
