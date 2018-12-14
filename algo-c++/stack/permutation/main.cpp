#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*! 排列算法 ,根据排序得来
 * 步骤:
 * 1.从右到左得到第一个<的序列, a < b
 * 2.从最后一个数值开始向左找到第一个大于a的数 c ,swap(a,c)
 * 3.a和c进行交换，并将b至最后一个元素进行逆操作(reverse(b, end))
*/
void next_perm(char *s) {

}

int main()
{
    char s[] = "abc";
    do {
        cout<<s<<endl;
    } while(next_permutation(s, s + strlen(s) ));

//    const int size = sizeof(s) / sizeof(char); // size ==4 (contains null-terminated char)
//    for(;; ) {
//        cout << s <<endl;
//        if(!next_permutation(s, s + size-1)) {
//            break;
//        }
//    }

    return 0;
}
