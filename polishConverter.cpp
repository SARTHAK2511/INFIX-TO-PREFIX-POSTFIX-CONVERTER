#include <iostream>

#include <bits/stdc++.h>

#include <string>

using namespace std;

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isOperand(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string InfixToPrefix(stack<char> s, string infix)
{
    string prefix;
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(')
        {
            infix[i] = ')';
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
        }
    }
    for (int i = 0; i < infix.length(); i++)
    {
        if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
        {
            prefix += infix[i];
        }
        else if (infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while ((s.top() != '(') && (!s.empty()))
            {
                prefix += s.top();
                s.pop();
            }

            if (s.top() == '(')
            {
                s.pop();
            }
        }
        else if (isOperator(infix[i]))
        {
            if (s.empty())
            {
                s.push(infix[i]);
            }
            else
            {
                if (precedence(infix[i]) > precedence(s.top()))
                {
                    s.push(infix[i]);
                }
                else if ((precedence(infix[i]) == precedence(s.top())) && (infix[i] == '^'))
                {
                    while ((precedence(infix[i]) == precedence(s.top())) && (infix[i] == '^'))
                    {
                        prefix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
                else if (precedence(infix[i]) == precedence(s.top()))
                {
                    s.push(infix[i]);
                }
                else
                {
                    while ((!s.empty()) && (precedence(infix[i]) < precedence(s.top())))
                    {
                        prefix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }

    while (!s.empty())
    {
        prefix += s.top();
        s.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}
// infix to postfix
string infixToPostfix(stack<char> s, string infix)
{
    string postfix;
    for (int i = 0; i < infix.length(); i++)
    {
        /* 1 */
        if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
        {
            postfix += infix[i];
        }
        /* 2 */
        else if (infix[i] == '(')
        {
            s.push(infix[i]);
        }
        /* 3 */
        else if (infix[i] == ')')
        {
            while (s.top() != '(' && (!s.empty()))
            {
                char temp = s.top();
                postfix += temp;

                s.pop();
            }
        }
        /* 4   can use else also */
        else if (isOperator(infix[i]))
        {
            if (s.empty())
            {
                s.push(infix[i]);
            }
            else
            {
                if (precedence(infix[i]) > precedence(s.top()))
                {
                    s.push(infix[i]);
                }
                else if (precedence(infix[i]) == precedence(s.top()) && (infix[i] == '^'))
                {
                    s.push(infix[i]);
                }
                else
                {
                    while ((!s.empty()) && (precedence(infix[i]) <= precedence(s.top())))
                    {
                        char temp = s.top();
                        postfix += temp;

                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }
    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}
// postfix to infix
string PostfixToInfix(string postfix)
{
    stack<string> s;
    for (int i = 0; i < postfix.length(); i++) // traversal is in left to right direction
    {
        if (isOperand(postfix[i]))
        {
            string op(1, postfix[i]);
            // string op=postfix[i];
            s.push(op);
        }
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("(" + op2 + postfix[i] + op1 + ")"); // position of op1 and op2 changes in prefix to infix case
        }
    }

    return s.top();
}
// Prefix to Infix

string PrefixToInfix(string prefix)
{
    stack<string> s;
    for (int i = prefix.length() - 1; i >= 0; i--)
    // traversal is in opposite direction
    //  we can reverse the string also then traverse in normal way
    {
        if (isOperand(prefix[i]))
        {
            string op(1, prefix[i]);
            // string op = prefix[i];
            s.push(op);
        }
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("(" + op1 + prefix[i] + op2 + ")");
            // position of op1 and op2 changes in postfix to infix case
        }
    }
    return s.top();
}
// prefix to Postfix

string PrefixToPostfix(string prefix)
{
    stack<string> s;
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
        if (isOperand(prefix[i]))
        {
            string op(1, prefix[i]);
            s.push(op);
        }
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push(op1 + op2 + prefix[i]);
        }
    }

    return s.top();
}
// postfix to prefix
string PostfixToPrefix(string postfix)
{
    stack<string> s;
    for (int i = 0; i < postfix.length(); i++)
    {
        if (isOperand(postfix[i]))
        {
            string op(1, postfix[i]);
            s.push(op);
        }
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push(postfix[i] + op2 + op1);
        }
    }
    return s.top();
}

int main()
{
    string input, output;
    int option;
    stack<char> s;
    do{
    cout << " \n What action do you want to perform ?" << endl
         << "Press corresponding digit to choose the option" << endl
         << " press 0 to exit " << endl
         << endl;

    cout << " 1 : Infix to prefix converter \n";
    cout << " 2 : Infix to postfix converter  \n";
    cout << " 3 : Postfix to Infix  converter \n";
    cout << " 4 : Prefix  to Infix  converter \n";
    cout << " 5 : Prefix to postfix converter \n";
    cout << " 6 : Postfix to prefix converter \n";

    cin >> option;
    
    switch (option)
    {
    case 1:
        cout << "Enter the input \n";
        cin >> input;
        output = InfixToPrefix(s, input);
        cout << "Prefix Expression :-> " << output << endl;
        break;
    case 2:
        cout << "Enter the input \n";
        cin >> input;
        output = infixToPostfix(s, input);
        cout << "Prefix Expression :-> " << output << endl;
        break;
    case 3:
        cout << "Enter the input \n";
        cin >> input;
        output = PostfixToInfix(input);
        cout << "Infix Expression :-> " << output << endl;
        break;
    case 4:
        cout << "Enter the input \n";
        cin >> input;
        output = PrefixToInfix(input);
        cout << "Infix Expression :-> " << output << endl;
        break;
    case 5:
        cout << "Enter the input \n";
        cin >> input;
        output = PrefixToPostfix(input);
        cout << "Postfix Expression :-> " << output << endl;
        break;
    case 6:
        cout << "Enter the input \n";
        cin >> input;
        output = PostfixToPrefix(input);
        cout << "Prefix Expression :-> " << output << endl;
        break;
    }
    }
    while(option!=0);
    return 0;
}