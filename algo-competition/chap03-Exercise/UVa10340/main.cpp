/*！
 * 子序列，输入两个字符串s和t，判断是否可以从t中删除0个到多个字符（字符顺序不变），
 * 得到字符串s。例如abcde可以得到bce，但是无法得到dc。
 * 思路：状态机，状态转换
 */
#include <iostream>

using namespace std;

#define MAX_LEN 1000

bool allInAll(const char *s, const char *t) {
    int n = strlen(t);
    int cnt=0;
    for(const char *i =s, *j = t; *i && *j; ) {
        if(*i != *j) {
            ++i;
        } else {
            ++i;
            ++j;
            cnt++;
            if(cnt == n) return true;
        }
    }

    return false;
}

int main()
{
    char s[MAX_LEN], t[MAX_LEN];
    if(scanf("%s%s", s, t) != 2) return 0;
    printf("%s\n", allInAll(s, t) ? "Yes" : "No");

    return 0;
}
