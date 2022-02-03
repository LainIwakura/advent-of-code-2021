#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

void calculate_basin_size(vector<vector<tuple<int, bool>>>& heightmap, int r, int c, vector<int>& basin_squares)
{
    if (get<0>(heightmap[r][c]) == 9) return;
    if (get<1>(heightmap[r][c]) == true) return;
    get<1>(heightmap[r][c]) = true;

    basin_squares.push_back(get<0>(heightmap[r][c]));

    calculate_basin_size(heightmap, r - 1, c, basin_squares); 
    calculate_basin_size(heightmap, r + 1, c, basin_squares);
    calculate_basin_size(heightmap, r, c - 1, basin_squares);
    calculate_basin_size(heightmap, r, c + 1, basin_squares);

    return;
}

int main()
{
    stringstream ss;
    string input_line;
    char c = ' ';
    vector<vector<tuple<int, bool>>> heightmap;
    vector<tuple<int, bool>> line;
    while (cin >> c)
    {
        line.push_back(make_tuple(c - '0', false));
        if (cin.peek() == '\n')
        {
            line.insert(line.begin(), make_tuple(9, false));
            line.push_back(make_tuple(9, false));
            heightmap.push_back(line);
            line.clear();
        }
    }

    size_t row_size = heightmap.size();
    size_t col_size = heightmap[0].size();

    vector<tuple<int, bool>> dummy_row(col_size, make_tuple(9, false));
    heightmap.insert(heightmap.begin(), dummy_row);
    heightmap.push_back(dummy_row);
    vector<int> basins;

    for (int i = 1; i < heightmap.size() - 1; i++)
    {
        for (int j = 1; j < heightmap[i].size() - 1; j++)
        {   
            if (get<0>(heightmap[i][j]) == 9)
                continue;

            int currVal = get<0>(heightmap[i][j]);
            if ((currVal < get<0>(heightmap[i-1][j])) && (currVal < get<0>(heightmap[i+1][j])) && (currVal < get<0>(heightmap[i][j-1])) && (currVal < get<0>(heightmap[i][j+1])))
            {
                vector<int> basin_squares;
                calculate_basin_size(heightmap, i, j, basin_squares);
                basins.push_back(basin_squares.size());
            }
        }
    }

    sort(basins.rbegin(), basins.rend());

    int size = basins[0] * basins[1] * basins[2];
    cout << size << endl;

    return 0;
}
