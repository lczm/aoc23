#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;
int main()
{
    string line;
    ifstream file("input.txt");
    int sum = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            string numStr = "";
            for (int i = 0; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    numStr += line[i];
                }
            }
            string firstLast = "";
            firstLast += numStr[0];
            firstLast += numStr[numStr.length() - 1];
            sum += stoi(firstLast);
        }
        file.close();
    }
    cout << sum;

    return 0;
}
