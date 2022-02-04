#include <deque>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

map<char, int> syntax_scores = {
    { ')', 3     },
    { ']', 57    },
    { '}', 1197  },
    { '>', 25137 }
};

map<char, char> chars = {
    { '(', ')' },
    { '{', '}' },
    { '[', ']' },
    { '<', '>' }
};

int main()
{
    vector<string> incomplete;
    string line = "";
    int error_score = 0;
    while (getline(cin, line))
    {
        char c;
        stringstream ss;
        ss << line;
        deque<char> brackets;

        bool bad_line = false;
        while (ss >> c)
        {
            if (c == '(' || c == '[' || c == '{' || c == '<')
            {
                brackets.push_back(c);
            }
            else if (c == ')' || c == ']' || c == '}' || c == '>')
            {
                char match = brackets.back();
                brackets.pop_back();
                if (c != chars[match])
                {
                    error_score += syntax_scores[c];
                    bad_line = true;
                }
            }

            if (bad_line)
                break;
        }

        if (!bad_line)
            incomplete.push_back(line);

        brackets.clear();
    }

    for (auto const&l : incomplete)
        cout << l << endl;


    return 0;
}
