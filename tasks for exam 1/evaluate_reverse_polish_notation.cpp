
#include <iostream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using std::vector;
using std::stack;
using std::string;
using std::cin;
using std::cout;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> output;
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/")
            {
                int current_num = stoi(tokens[i]);
                output.push(current_num);
            }
            else
            {
                int left = output.top();
                output.pop();
                int right = output.top();
                output.pop();
                int res;
                if (tokens[i] == "+")
                    res = right + left;
                else if (tokens[i] == "-")
                    res = right - left;
                else if (tokens[i] == "*")
                    res = right * left;
                else if (tokens[i] == "/")
                    res = right / left;

                output.push(res);
            }


        }
        return output.top();
    }
};

int main()
{
    vector<string> tokens = { "2", "1", "+", "3", "*" };
    Solution s;
    cout << s.evalRPN(tokens);
}

