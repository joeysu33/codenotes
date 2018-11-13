#include "output.h"
#include <iostream>

Output::Output()
{

}

void Output::newSplitLine()
{
    newSplitLine("");
}

void Output::newSplitLine(const string &s)
{
    cout<<nTimes('-',20) << s << nTimes('-', 20) <<endl;
}

string Output::nTimes(const char c, int count)
{
    string s;
    while(count-- > 0)
        s += c;
    return s;
}

void Output::newLine()
{
    cout<<endl;
}
