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

int main()
{
    // char eq[501];
    // cin.get(eq, 500);
    char eq[] = "2+3*(1+2)*1";

    stack<char> op;
    stack<long long> opnd;

    for (char *p = eq; *p != '\0'; p++)
    {
        switch (*p)
        {
        case '(':
            op.push(*p);
            break;
        case ')':
            while (op.top() != '(') {      // 到左括號之前的運算子都要計算
                calculate(opnd, op.top());
                op.pop();
            }
            op.pop();  // 取走 '('
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