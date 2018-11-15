/*! 回文串，镜像串
 * 回文串 abba madam
 * 镜像串 2S和3AAE
 * 镜像表
 * A - A
 * E - 3
 * H - H
 * I - I
 * J - L
 * L - J
 * M - M
 * O - O
 * S - 2
 * T - T
 * U - U
 * V - V
 * W - W
 * X - X
 * Y - Y
 * Z - 5
 * 1 - 1
 * 2 - S
 * 3 - E
 * 5 - Z
 * 8 - 8
 */

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct {
    char m_ochar;
    char m_rchar;
} rtable[] = {
{'A','A'}, {'E', '3'}, {'H', 'H'}, {'I', 'I'}, {'J', 'L'}, {'M', 'M'}, {'O', 'O'},
{'S', '2'}, {'T', 'T'}, {'U', 'U'}, {'V', 'V'}, {'W', 'W'}, {'X', 'X'}, {'Y', 'Y'},
{'Z', '5'}, {'1', '1'}, {'2', 'S'}, {'3', 'E'}, {'5', 'Z'}, {'8', '8'},
};

static int rtblsize = sizeof(rtable)/sizeof(rtable[0]);

char rchar(char ochar) {
    for(int i=0; i<rtblsize; ++i)
        if(rtable[i].m_ochar == ochar) return rtable[i].m_rchar;
    return 0;
}

bool isPalindrome(const char *s) {
    if(!s) return false;
    int len = strlen(s);
    if(len == 1) return true;
    for(const char *i = s, *j=s+len-1; i < j; ++i, --j) {
        if(*i != *j) return false;
    }

    return true;
}

bool isImage(const char *s) {
    if(!s) return false;
    int len = strlen(s);
    if(len == 1) return rchar(s[0]) != 0;

    char k;
    for(const char *i = s, *j=s+len-1; i < j; ++i, --j) {
        k = rchar(*i);
        if(!k) return false;
        if(k != *j) return false;
    }

    return true;
}

int main()
{
    char buffer[1000], c;

    //必须初始化内存空间为0
    memset(buffer, 0, sizeof(buffer));

    int i=0;
    while((c = fgetc(stdin)) != EOF) {
        if(c == '\n') c = 0;
        buffer[i++] = c;
    }
    if(i == 0) return 0;

    int st = 0;
    string sstate;
    for(char *s = buffer; *s; s += strlen(s)+1) {
        st = 0;
        if(isPalindrome(s)) {
            st |= 0x1;
        }
        if(isImage(s)) {
            st |= 0x2;
        }
        if(st == 0)  sstate = "is not a palindrome.";
        else if(st == 1) sstate = "is a regular palindrome.";
        else if(st == 2) sstate = "is a mirrored string.";
        else sstate = "is a mirrored palindrome.";
        printf("%s -- %s\n", s, sstate.c_str());
    }

    return 0;
}
