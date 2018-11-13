#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <string>

using namespace std;
namespace  Output {
    void newSplitLine(const string& s) {
        cout<<"----------"<<s<<"------------";
    }
    void newSplitLine() { newSplitLine("");}

    void spaceLine() { cout<<endl; }
}
#endif // OUTPUT_H
