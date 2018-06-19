/*!
 * scanf中正则表达匹配的使用
 * scanf如果遇到输入结束(linux下ctrl+z)则返回EOF，否则
 * 返回已经正确读入的个数
 */

#include <stdio.h>

/*![] 匹配*/
void
scanf_match() {
    char buf[32];
    const char *s1 = "aabb cc dd E";
    sscanf(s1, "%s", buf);  //默认遇到空格，制表符、换行符就终止解析
    printf("scanf_match::match=%s\n", buf);
    sscanf(s1, "%[^E]", buf); //可以一直读到E(只要不是E就一直读取)
    printf("scanf_match::match=%s\n", buf);
}

/*! 
 * *[]过滤匹配 */
void
scanf_filter() {
    char buf[32];
    const char *s1 = "AAbbjjKK";
    /*!首先过滤[A-Z]的字符，
     * 然后匹配一个非[A-Z]的字符终止
     * 一个scanf中可以有多个"*[]过滤",
     * 但是仅能有一个终止匹配
     */
    sscanf(s1,"%*[A-Z]%[^A-Z]", buf);
    printf("scanf_filter::buf=%s\n", buf);
}

/*!
 * scanf 读取char
 */
void 
scanf_readchr() {
    char buf[16];
    char c;
    const char *s1 = "ab\t\n\f\v.ab~\"";
    const char *s2 = s1;
    printf("read chars:\n");
    for(; (*s2); s2++) {
        sscanf(s2, "%c", &c);
        printf("%c, ", c);
    }
    printf("\n");
}

/*!
 * 使用scanf来提取email
 */
void
scanf_extractEmail() {
    char buf[32];
    const char *s1 = "FFJJ:AFJJsskk@qq.com";
    const char *s2 = "FFJJ:joi@eznet99.com";
    /*!提取AFJJsskk, 在:和@之间的内容*/
    sscanf(s1, "%*[^:]:%[^@]", buf);
    printf("scanf_extract::name=%s\n", buf);

    /*!提取@和.com之间的内容*/
    sscanf(s2, "%*[^@]@%[^.]",buf);
    printf("scanf_extract::net=%s\n", buf);
}

void
main() {
    scanf_match();
    scanf_filter();
    scanf_readchr();
    scanf_extractEmail();
}


