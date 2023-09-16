#include <iostream>
using namespace std;

int main()
{
    char ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '#')
        {
            break; 
        }
        int checksum = 0;
        int num = 1;
        while (ch != '\n')
        {
            if (ch == ' ')
            {
                checksum += 0;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                checksum += num * (ch - 'A' + 1);
            }
            num++;
            ch = getchar();
        }
        cout << checksum << endl;
    }

    return 0;
}
