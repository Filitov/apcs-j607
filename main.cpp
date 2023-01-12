#include <iostream>
#include <stack>

using namespace std;

int main()
{
    // char eq[501];
    // cin.get(eq, 500);
    char eq[] = "2+3*1+2+1";

    stack<char> op;

    for (char *p = eq; *p != '\0'; p++)
    {
        switch (*p)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            if (!op.empty()){
                cout << "算符:" << op.top() << endl;
                op.pop();
            }
            op.push(*p);
            break;
        default:
            cout << "數字:" << *p << endl;
        }
    }

    if (!op.empty()){
        cout << "算符:" << op.top() << endl;
        op.pop();
    }

    return 0;
}