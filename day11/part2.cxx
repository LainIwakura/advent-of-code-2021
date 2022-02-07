#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

typedef vector<vector<tuple<int, bool>>> octo;

void print_grid(const octo& octopi)
{
    for (auto const& oct_line : octopi)
    {
        for (auto const& oct : oct_line)
            cout << get<0>(oct) << " ";
        cout << endl;
    }

    cout << endl;
}

auto is_valid_position(octo& octopi, int32_t i, int32_t j) -> bool
{
    return ((i >= 0 && i < octopi.size()) && (j >= 0 && j < octopi[i].size()));
}

auto bfs_flashpoints(octo& octopi, int32_t i, int32_t j) -> uint32_t
{
    auto adj_dirs = vector<pair<int, int>>
    {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
        {1, 1},
        {-1, 1},
        {1, -1},
        {-1, -1}
    };

    auto frontier = queue<pair<int32_t, int32_t>>{};
    frontier.push({i, j});
    get<1>(octopi[i][j]) = true;
    uint32_t flashes = 0;
    while (!frontier.empty())
    {
        auto node = frontier.front();
        frontier.pop();
        auto fst = node.first;
        auto snd = node.second;

        for (const auto& adj : adj_dirs)
        {
            if (is_valid_position(octopi, fst + adj.first, snd + adj.second))
            {
                // Haven't visited this node yet
                if (get<1>(octopi[fst + adj.first][snd + adj.second]) == false)
                {
                    get<0>(octopi[fst + adj.first][snd + adj.second])++;
                    if (get<0>(octopi[fst + adj.first][snd + adj.second]) > 9)
                    {
                        flashes++;
                        get<0>(octopi[fst + adj.first][snd + adj.second]) = 0;
                        get<1>(octopi[fst + adj.first][snd + adj.second]) = true;
                        frontier.push({fst + adj.first, snd + adj.second});
                    }
                }
            }
        }
    }

    return flashes;
}

auto find_flash_point_sync(octo& octopi) -> uint32_t
{
    uint32_t flashpoints = 0;
    uint32_t steps = 0;
    for (;;)
    { 
        ++steps;
        auto is_solution = uint32_t{0};
        
        for (int i = 0; i < octopi.size(); i++)
        {
            for (int j = 0; j < octopi[i].size(); j++)
            {
                get<0>(octopi[i][j])++;
                get<1>(octopi[i][j]) = false;
            }
        }

        for (int i = 0; i < octopi.size(); i++)
        {
            for (int j = 0; j < octopi[j].size(); j++)
            {
                if (get<0>(octopi[i][j]) > 9)
                {
                    get<0>(octopi[i][j]) = 0;
                    flashpoints += (1 + bfs_flashpoints(octopi, i, j));
                }
            }
        }

        auto n = octopi.size();
        auto m = 0;

        for (const auto& row : octopi)
        {
            m = row.size();
            for (const auto& energy_val : row)
                is_solution += (get<0>(energy_val) == 0);

            if (is_solution == m * n)
                return steps;
        }
    }

    return flashpoints;
}

auto main(void) -> int
{
    octo octopi;
    string line = "";
    while (getline(cin, line))
    {
        stringstream ss;
        ss << line;
        char c;
        vector<tuple<int, bool>> octopi_line;
        while (ss >> c)
            octopi_line.push_back(make_tuple(c - '0', false));
        ss.clear();
        octopi.push_back(octopi_line);
    }
        
    unsigned int sync_point = find_flash_point_sync(octopi);        
    cout << sync_point << endl;

    return 0;
}
