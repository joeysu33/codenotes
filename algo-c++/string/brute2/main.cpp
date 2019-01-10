#include <iostream>

using namespace std;

#define MAXN 1024

int  findStr(const string& s , const string & pat, int from = 0) {
    for(int i=from, j=s.size() - pat.size(); i <= j; ++i) {
        int k;
        for(k=0; k<pat.size() ; ++k) {
            if(s[k+i] != pat[k])  break;
        }
        if(k == pat.size()) return i;
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
