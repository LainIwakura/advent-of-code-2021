#include <deque>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

map<char, unsigned long> syntax_scores = {
    { ')', 1UL },
    { ']', 2UL },
    { '}', 3UL },
    { '>', 4UL }
};

map<char, char> chars = {
    { '(', ')' },
    { '{', '}' },
    { '[', ']' },
    { '<', '>' }
};

int main()
{
    vector<unsigned long> scores;
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

        unsigned long auto_complete_score = 0;
        if (!bad_line && !brackets.empty())
        {
            while (!brackets.empty())
            {
                c = brackets.back();
                brackets.pop_back();
                auto_complete_score *= 5UL;
                auto_complete_score += syntax_scores[chars[c]];
            }

            scores.push_back(auto_complete_score);
        }

        brackets.clear();
    }

    sort(scores.begin(), scores.end());
    cout << scores[scores.size() / 2] << endl;

    return 0;
}
