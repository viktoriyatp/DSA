#include <iostream>
#include <stack>
using std::stack;

void solve(char* str, stack<char> s)
{
    if (str[0] == '\0')
    {
        while (!s.empty())
        {
            std::cout << s.top();
            s.pop();
        }
        std::cout << std::endl;
        return;
    }
    if (str[0] == '0' || str[0] == '1')
    {
        s.push(str[0]);
        solve(++str, s);
    }
    else
    {
        s.push('0');
        solve(++str, s);
        s.pop();
        s.push('1');
        solve(str, s);
        s.pop();
    }
}

int main()
{
    stack<char> s;
    char str[] = "10?100?";
    solve(str, s);
}

