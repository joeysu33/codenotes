#include <iostream>
#include <string>

using namespace std;

#define MAXN 1024

int  findStr(const string& s , const string & pat, int from = 0) {
    for( int i=from, j= 0;  i < s.size() && j < pat.size(); ) {
        if(s[i] == pat[j]) {
            ++i; ++ j;
        } else {
            i = i -j + 1;
            j=0;
        }
        if(j == pat.size()) return i-j;
    }
    return -1;
}

void findAll(const string& s, const string& pat) {
    int i = 0;
    while(i >= 0) {
        i = findStr(s, pat, i);
        cout<<"find:"<<pat<<" in:"<<i <<endl;

        if( i >= 0) i++;
    }
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    findAll(s1, s2);
    return 0;
}
