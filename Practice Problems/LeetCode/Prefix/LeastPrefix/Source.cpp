#include <vector>
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

string longestCommonPrefix(vector<string>&);


int main()
{
    vector<string> strs = { "reflower","flow","flight" };

    string prefix = longestCommonPrefix(strs);

    cout << prefix;

    return 0;
}

string longestCommonPrefix(vector<string>& strs) {
    string prefix = "";
    string front = strs[0];

    int shortest = strs[0].length();
    int size = strs.size();

    // Single string vector
    if (size == 1)
    {
        return prefix = strs[0];
    }

    // Find the shortest string in strs
    for (string s : strs)
    {
        int current = s.length();

        if (current == 0)
        {
            return prefix;
        }

        if (current < shortest)
        {
            shortest = current;
            //front = s;
        }
    }

    for (int i = 0; i < shortest; i++) // For each letter
    {
        for (int j = 1; j < size; j++) // For each string
        {
            if (front.at(i) != strs[j].at(i))
            {
                if (i == 0)
                {
                    return prefix = "";
                }

                return prefix = front.substr(0, i);
            }

        }

    }

    return prefix = front; // Shortest is prefix
}