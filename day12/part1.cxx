#include <set>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;;

typedef map<string, vector<string>> CaveSystem;
CaveSystem cv;
set<string> paths;

auto find_small_caves(CaveSystem& cv) -> map<string, int>
{
    map<string, int> small_cave_visits;
    for (auto& [k, _v] : cv)
        if (all_of(k.begin(), k.end(), [](char c) { return islower(c); }) && k != "start" && k != "end")
            small_cave_visits.insert(pair{k, 0});
    return move(small_cave_visits);
}

auto generate_caves_from_file() -> void
{
    string line = "";
    fstream ifs{"input"};
    if (!ifs.is_open())
    {
        cerr << "Error opening file." << endl;
        return;
    }

    while (getline(ifs, line))
    {
        auto pos = line.find('-');
        string c1 = line.substr(0, pos);
        string c2 = line.substr(pos+1);

        vector<string> c1_connections;
        vector<string> c2_connections;
        
        if (cv.find(c1) == cv.end()) {
            c1_connections.push_back(c2);
            cv.insert(pair{c1, c1_connections});
        } else {
            cv[c1].push_back(c2);
        }

        if (cv.find(c2) == cv.end()) {
            c2_connections.push_back(c1);
            cv.insert(pair{c2, c2_connections});
        } else {
            cv[c2].push_back(c1);
        }
    } 
}

auto find_all_paths(string node, map<string, int> smallVisits, string path) -> void
{
    path += "," + node;

    if (node == "end")
    {
        paths.insert(path);
        return;
    }
    else if (all_of(node.begin(), node.end(), [](char c) { return islower(c); }))
    {
        smallVisits[node]++;
    }

    for (auto neighbour : cv[node])
        if (neighbour != "start" && smallVisits[neighbour] == 0) 
            find_all_paths(neighbour, smallVisits, path); 

}

auto main() -> int
{
    generate_caves_from_file();
    map<string, int> small_caves = find_small_caves(cv);

    for (auto neighbour : cv["start"])
        find_all_paths(neighbour, small_caves, "start");

    cout << paths.size() << endl;

    return 0;
}
