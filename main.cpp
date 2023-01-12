#include <iostream>
#include <stack>

using namespace std;

int precendence(char op)
{
    if (op=='*' || op=='/')
        return 2;
    if (op=='+' || op=='-')
        return 1;
    return 0;
}

bool higher_or_equal(char op1, char op2)
{
    return precendence(op1) >= precendence(op2);
}

void calculate(char op)
{
    cout << "計算: " << op << endl;
}

int main()
{
    // char eq[501];
    // cin.get(eq, 500);
    char eq[] = "2+3*1+2*1";

    stack<char> op;

    for (char *p = eq; *p != '\0'; p++)
    {
        switch (*p)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            while (!op.empty() && higher_or_equal(op.top(),*p) ) {
                calculate(op.top());
                op.pop();
            }
            op.push(*p);
            break;
        default:
            cout << "數字: " << *p << endl;
        }
    }

    while (!op.empty()){
        calculate(op.top());
        op.pop();
    }

    return 0;
}