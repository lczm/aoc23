#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;

char strToDigitChar(string str);
int counter = 0;
int main()
{
    string line;
    ifstream file("input.txt");
    int sum = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            counter += 1;

            // store string representing the num
            string numStr = "";
            // store string of letters
            string alphaStr = "";
            // for each line of input, fill numStr
            for (int i = 0; i < line.length(); i++)
            {
                // if the current char is an alphabet, append to alphaStr
                if (isalpha(line[i]))
                {
                    alphaStr += line[i];
                    char digitChar = strToDigitChar(alphaStr);
                    if (digitChar != '-')
                    {
                        numStr += digitChar;

                        alphaStr = alphaStr[alphaStr.length() - 1];
                    }
                }
                if (line[i] >= '0' && line[i] <= '9')

                {
                    alphaStr = "";
                    numStr += line[i];
                }
            }
            // get the first and last num and parse into an int
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

char strToDigitChar(string str)
{
    if (str.find("one") != -1)
    {
        return '1';
    }
    else if (str.find("two") != -1)
    {
        return '2';
    }
    else if (str.find("three") != -1)
    {
        return '3';
    }
    else if (str.find("four") != -1)
    {
        return '4';
    }
    else if (str.find("five") != -1)
    {
        return '5';
    }
    else if (str.find("six") != -1)
    {
        return '6';
    }
    else if (str.find("seven") != -1)
    {
        return '7';
    }
    else if (str.find("eight") != -1)
    {
        return '8';
    }
    else if (str.find("nine") != -1)
    {
        return '9';
    }
    else
        return '-';
}
