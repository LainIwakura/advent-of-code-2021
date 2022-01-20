#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

int main()
{
	string positions;
	stringstream ss;
	vector<int> crab_pos;
	getline(cin, positions);

	ss << positions;
	string crab_spot = "";
	while (getline(ss, crab_spot, ','))
		crab_pos.push_back(stoi(crab_spot));

	// lol, max crab
	int max_crab = *(max_element(crab_pos.begin(), crab_pos.end()));
	vector<int> x_axis(max_crab+1);
	iota(x_axis.begin(), x_axis.end(), 0);

	int least_fuel_used = INT_MAX;
	for (auto const& pos : x_axis)
	{
		int fuel_used = 0;
		for (auto const& crab_x : crab_pos)
		{
			fuel_used += abs(pos - crab_x);
		}
		least_fuel_used = (fuel_used < least_fuel_used) ? fuel_used : least_fuel_used;
	}

	cout << least_fuel_used << endl;

	return 0;
}
