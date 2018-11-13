#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

using namespace std;
class Output
{
public:
    Output();
    void newSplitLine();
    void newSplitLine(const string& s);
    string nTimes(const char c, int count);
    void newLine();
};

#endif // OUTPUT_H
