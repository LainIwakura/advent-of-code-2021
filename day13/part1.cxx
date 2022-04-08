#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <utility>

using namespace std;

int max_x, max_y;
typedef tuple<int, int> coord_t;

vector<tuple<int, int>> coords;
vector<vector<char>> paper;
vector<string> fold_instructions;

auto print_paper() -> void
{
    for (auto const& row : paper)
    {
        for (auto const& cell : row)
            cout << cell;
        cout << endl;
    }
    cout << endl;
}

auto print_coords() -> void
{
    for (auto const& c : coords)
        cout << "(" << get<0>(c) << "," << get<1>(c) << ")" << endl;
    cout << endl;
}

auto repopulate_coords() -> void
{
    coords.clear();
    for (int y = 0; y < paper.size(); y++)
        for (int x = 0; x < paper[0].size(); x++)
            if (paper[x][y] == '#')
                coords.push_back(make_tuple(x, y));
}

auto populate_paper(int x, int  y) -> void
{
    for (int i = 0; i <= y; i++)
    {
        vector<char> row;
        for (int j = 0; j <= x; j++)
            row.push_back('.');
        paper.push_back(row);
    }

    for (auto const& c : coords)
    {
        int x_pos = get<0>(c);
        int y_pos = get<1>(c);

        paper[y_pos][x_pos] = '#';
    }
}

auto read_coords_and_folds() -> void
{
    string coord = "";
    while (getline(cin, coord))
    {
        if (coord == "") break;

        auto pos = coord.find(',');
        int x_point = stoi(coord.substr(0, pos));
        int y_point = stoi(coord.substr(pos+1));

        coords.push_back(make_tuple(x_point, y_point));
    }

    string fold = "";
    while (getline(cin, fold))
        fold_instructions.push_back(fold);
}

auto mark_fold(bool is_vertical, int fold_line) -> void
{
    if (!is_vertical)
        for (auto& e : paper[fold_line])
            e = '-';
    else
        for (int i = 0; i < max_y; i++)
            paper[i][fold_line] = '|';
}

auto fold_paper(bool is_vertical, int fold_line) -> void
{
    for (auto& c : coords)
    {
        if (!is_vertical)
        {
            int x = get<0>(c);
            int y = get<1>(c);
            if (y > fold_line)
                y = abs(y -= max_y);
            else
                continue;

            paper[y][x] = '#';
        }
        else
        {
            int x = get<0>(c);
            int y = get<1>(c);
            if (x < fold_line)
            {
                x = x + fold_line + 1;
                y = abs(y - max_y); 
            }
            else
                continue;

            cout << "(" << x << "," << y << ")" << endl;

            paper[y][x] = '#';
        }
    }

    if (!is_vertical)
    {
        paper.erase(paper.begin()+fold_line, paper.end());
    }

    max_x = paper[0].size();
    max_y = paper.size();
}

int main()
{
    read_coords_and_folds();

    max_x = get<0>(*max_element(coords.begin(), coords.end(), [](coord_t x, coord_t y) { return get<0>(x) < get<0>(y); }));
    max_y = get<1>(*max_element(coords.begin(), coords.end(), [](coord_t x, coord_t y) { return get<1>(x) < get<1>(y); }));

    populate_paper(max_x, max_y);

    print_paper();
    print_coords();

    for (auto& fold : fold_instructions)
    {
        auto pos = fold.find('=');
        bool vertical_fold = (fold[pos-1] == 'x');
        int fold_line = stoi(fold.substr(pos+1));
        mark_fold(vertical_fold, fold_line);
        fold_paper(vertical_fold, fold_line);
        repopulate_coords();
        print_coords();
        print_paper();
    }

    return 0;
}
