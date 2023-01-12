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

void calculate(stack<long long> &opnd, char op)
{
    long long a, b;
    b = opnd.top();
    opnd.pop();
    a = opnd.top();
    opnd.pop();
    cout << "計算: " << a << " " << op << " " << b << endl;
    switch (op)
    {
        case '+': opnd.push(a+b); break;
        case '-': opnd.push(a-b); break;
        case '*': opnd.push(a*b); break;
        case '/': opnd.push(a/b); break;
    }
}

void calculate_f(stack<long long> &opnd, stack<char> &op)
{
    long long v;
    v = opnd.top();    // at least one
    opnd.pop();

    cout << "f(" << v;       // DEBUG

    while (op.top()!='f')
    {
        op.pop();
        v = opnd.top();
        opnd.pop();
        cout << "," << v;   // DEBUG
    }

    cout << ")" << endl; // DEBUG
    opnd.push(0);

    op.pop();                    // 取走 'f'
}

int main()
{
    // char eq[501];
    // cin.get(eq, 500);
    char eq[] = "2+3*f(1+2*3,2*3)*1";

    stack<char> op;
    stack<long long> opnd;

    for (char *p = eq; *p != '\0'; p++)
    {
        switch (*p)
        {
        case 'f':
            op.push(*p);
            p++;
            break;
        case ')':
        case ',':
            while (op.top() != 'f' && op.top() != ',') {
                calculate(opnd, op.top());
                op.pop();
            }

            if (*p == ',')
                op.push(*p);
            else
                calculate_f(opnd, op);

            break;
        case '+':
        case '-':
        case '*':
        case '/':
            while (!op.empty() && higher_or_equal(op.top(),*p) ) {
                calculate(opnd, op.top());
                op.pop();
            }
            op.push(*p);
            break;
        default:
            opnd.push(*p-'0');
        }
    }

    while (!op.empty()){
        calculate(opnd, op.top());
        op.pop();
    }

    cout << "結果: " << opnd.top() << endl;

    return 0;
}