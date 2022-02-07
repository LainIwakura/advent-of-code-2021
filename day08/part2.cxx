#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

size_t intersectionSize(const string& a, const string& b)
{
    string tmp;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(tmp));
    return tmp.size();
}

vector<string>::const_iterator findByIntersectionSize(const vector<string>& v, const string& other, int size)
{
    return find_if(v.begin(), v.end(), [&](const auto& s) { return intersectionSize(s, other) == size; });
}

int main()
{
    int result = 0;
    string whole_line = "";
    string signal_line = "";
    string output_val = "";
    stringstream ss;

    while (getline(cin, whole_line))
    {
        size_t pos = whole_line.find('|');
        signal_line = whole_line.substr(0, pos-1);
        output_val = whole_line.substr(pos+2);
        unordered_map<string, int> m;
        unordered_map<int, string> r;
        vector<string> length5, length6;

        ss << signal_line;
        string single_digit = "";
        while (getline(ss, single_digit, ' '))
        {
            sort(single_digit.begin(), single_digit.end());
            switch (single_digit.length())
            {
                case 2: m[single_digit] = 1; break;
                case 3: m[single_digit] = 7; r[7] = single_digit; break;
                case 4: m[single_digit] = 4; r[4] = single_digit; break;
                case 5: length5.push_back(single_digit); break;
                case 6: length6.push_back(single_digit); break;
                case 7: m[single_digit] = 8; break;
            }
        }

        ss.clear();

        auto it = findByIntersectionSize(length5, r[7], 3);
        m[*it] = 3;
        r[3] = *it;
        length5.erase(it);

        // find 5
        it = findByIntersectionSize(length5, r[4], 3);
        m[*it] = 5;
        length5.erase(it);

        // deduce 2
        m[length5[0]] = 2;

        // find 9
        it = findByIntersectionSize(length6, r[3], 5);
        m[*it] = 9;
        length6.erase(it);

        // find 0
        it = findByIntersectionSize(length6, r[7], 3);
        m[*it] = 0;
        length6.erase(it);

        // deduce 6
        m[length6[0]] = 6;

        int curr = 0;
        ss << output_val;
        while (getline(ss, single_digit, ' '))
        {
            sort(single_digit.begin(), single_digit.end());
            curr *= 10;
            curr += m[single_digit];
        }
        ss.clear();
        result += curr;
    }

    cout << result << endl;

    return 0;
}
