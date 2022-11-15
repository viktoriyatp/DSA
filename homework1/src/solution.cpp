#include <stack>
#include "solution.h"
using std::stack;

bool isRightBracket(const char character)
{
    return (character == ')' || character == '}' || character == ']');
}

bool isLeftBracket(const char character)
{
    return (character == '(' || character == '{' || character == '[');
}

bool isMatchingBrackets(const char left_bracket, const char right_bracket)
{
    return (left_bracket == '(' && right_bracket == ')') ||
        (left_bracket == '{' && right_bracket == '}') ||
        (left_bracket == '[' && right_bracket == ']');
        
}

bool isCorrect(const char* expression)
{
    stack<char> brackets;
    size_t size_of_expression = strlen(expression);
    for (size_t i = 0; i < size_of_expression; ++i)
    {
        char curr_character = expression[i];
        if (isRightBracket(curr_character))
        {
            if (!brackets.empty() && isMatchingBrackets(brackets.top(), curr_character))
            {
                brackets.pop();
            }
            else
            {
                return false;
            }
        }
        else if (isLeftBracket(curr_character))
        {
            brackets.push(curr_character);
        }
    }
    return brackets.empty();
}