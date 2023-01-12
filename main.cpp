#include <iostream>
#include <stack>

using namespace std;

int precendence(char op)
{
    if (op=='+' || op=='-')
        return 2;
    if (op=='*' || op=='/')
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
    long long v, v_max, v_min;
    v_max = v_min = opnd.top();    // at least one
    opnd.pop();

    cout << "f(" << v_max;       // DEBUG

    while (op.top()!='f')
    {
        op.pop();
        v = opnd.top();
        opnd.pop();
        cout << "," << v;   // DEBUG
        if (v>v_max) v_max = v;
        if (v<v_min) v_min = v;
    }

    cout << ") = "  << v_max-v_min << endl; // DEBUG
    opnd.push(v_max-v_min);

    op.pop();                    // 取走 'f'
}

int main()
{
    // char eq[501];
    // cin.get(eq, 500);
    char eq[] = "12+f(13,2+f(8,1+2*3),1+1*f(20,4)*f(2))*2";

    stack<char> op;
    stack<long long> opnd;

    long long val = -1;  // 取巧, 題目中沒有負數

    for (char *p = eq; *p != '\0'; p++)
    {
        // 處理多位數元
        if (*p >= '0' && *p <= '9')
        {
            if (val == -1)
                val = *p - '0';
            else
                val = val * 10 + (*p - '0');
            continue;
        }

        // 不是數元
        if (val >= 0)
        {
            opnd.push(val);
            val = -1;
        }

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
        case '*':
            while (!op.empty() && higher_or_equal(op.top(),*p) ) {
                calculate(opnd, op.top());
                op.pop();
            }
            op.push(*p);
            break;
        }
    }

    // 以數元結束
    if (val>=0) {
        opnd.push(val);
    }

    while (!op.empty()){
        calculate(opnd, op.top());
        op.pop();
    }

    cout << "結果: " << opnd.top() << endl;

    return 0;
}