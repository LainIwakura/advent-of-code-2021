#include <vector>
#include <iostream>
#include <utility>
#include <tuple>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

typedef tuple<int, int> point;
typedef pair<point, point> line_segment;

void print_grid(const vector<vector<int>>& grid)
{
	for (auto const &row : grid)
	{
		for (auto const &sq : row)
			cout << ((sq == 0) ? "." : to_string(sq));
		cout << endl;
	}
}

void print_vars(int distance, int start_x, int start_y, int end_x, int end_y)
{
	cout << "Processing this distance: " << distance << ", at start point: (" << start_x << ", " << start_y << ")" << ", ending at: (" << end_x << ", " << end_y << ")" << endl;
}

int main()
{
	vector<line_segment> coords;
	string coord_line = "";
	regex coord_regex("^(\\d+),(\\d+)\\s{1}->\\s{1}(\\d+),(\\d+)$");
	smatch coord_match;

	int max_x = 0;
	int max_y = 0;

	while (getline(cin, coord_line))
	{
		if (regex_match(coord_line, coord_match, coord_regex))
		{
			int x1 = stoi(coord_match[1]);
			int y1 = stoi(coord_match[2]);
			int x2 = stoi(coord_match[3]);
			int y2 = stoi(coord_match[4]);

			max_x = (x1 > max_x && x1 > x2) ? x1 : (x2 > max_x) ? x2 : max_x;
			max_y = (y1 > max_y && y1 > y2) ? y1 : (y2 > max_y) ? y2 : max_y;

			coords.push_back(make_pair(make_tuple(x1, y1), make_tuple(x2, y2)));
		}	
	}

	vector<vector<int>> grid;
	for (int i = 0; i <= max_y; i++)
	{
		vector<int> v(max_x+1, 0);
		grid.push_back(v);
	}

	for (auto [start, end] : coords)
	{
		if ((get<0>(start) != get<0>(end)) && (get<1>(start) != get<1>(end)))
			continue;

		int start_x = get<0>(start);
		int start_y = get<1>(start);
		int end_x = get<0>(end);
		int end_y = get<1>(end);

		bool rows = (start_y == end_y);
		int distance = (rows) ? abs(end_x - start_x) : abs(end_y - start_y);

		if (start_x > end_x)
			swap(start_x, end_x);
		if (start_y > end_y)
			swap(start_y, end_y);


		if (rows)
		{
			for (int i = start_x; i <= end_x; i++)
				grid[end_y][i]++;
		}
		else
		{
			for (int i = start_y; i <= end_y; i++)
				grid[i][end_x]++;
		}
	}

	int overLappingPoints = 0;
	for (const auto& row : grid)
		for (const auto& tile : row)
			if (tile >= 2)
				++overLappingPoints;

	cout << overLappingPoints << endl;

	return 0;
}
