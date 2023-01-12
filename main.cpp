#include <iostream>

using namespace std;

int main()
{
    // char eq[501];
    // cin.get(eq, 500);
    char eq[] = "2+3*1+2+1";

    for (char *p = eq; *p != '\0'; p++)
    {
        cout << *p << endl;
    }

    return 0;
}