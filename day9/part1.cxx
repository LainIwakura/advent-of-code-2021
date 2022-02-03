#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    stringstream ss;
    string input_line;
    char c = ' ';
    vector<vector<int>> heightmap;
    vector<int> line;
    while (cin >> c)
    {
        line.push_back(c - '0');
        if (cin.peek() == '\n')
        {
            line.insert(line.begin(), 9);
            line.push_back(9);
            heightmap.push_back(line);
            line.clear();
        }
    }

    size_t row_size = heightmap.size();
    size_t col_size = heightmap[0].size();

    vector<int> dummy_row(col_size, 9);
    heightmap.insert(heightmap.begin(), dummy_row);
    heightmap.push_back(dummy_row);
    vector<int> low_points;

    for (int i = 1; i < heightmap.size() - 1; i++)
        for (int j = 1; j < heightmap[i].size() - 1; j++)
            if ((heightmap[i][j] < heightmap[i-1][j]) && (heightmap[i][j] < heightmap[i+1][j]) && (heightmap[i][j] < heightmap[i][j-1]) && (heightmap[i][j] < heightmap[i][j+1]))
                low_points.push_back(heightmap[i][j]);

    transform(low_points.begin(), low_points.end(), low_points.begin(), [](int x) { return x + 1; });
    int sum = accumulate(low_points.begin(), low_points.end(), 0);

    cout << sum << endl;

    return 0;
}
