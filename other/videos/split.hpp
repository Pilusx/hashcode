#include <string>
#include <vector>

using namespace std;

void split(vector<int> &tokens, const string& str, const string& delim)
{
    tokens.clear();
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(atoi(token.c_str()));
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
}
