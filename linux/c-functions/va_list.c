/*! 标准c中变参的使用方法*/
#include <stdio.h>
#include <stdarg.h>

float average(int count, ...) {
    //va_list a_start va_arg va_end
    if(count <= 0) return 0;
    float i,sum=0;
    va_list al;
    va_start(al, count);
    while(count--) {
        //va_arg(va_list, type)
        i=va_arg(al,double);
        sum +=i;
    }
    va_end(al);
    return (float)sum/count;
}

int main() {
    //这里浮点数在传递的时候，...会按照dobule进行解析
    float v=average(3, 9.,10.,11.);
    fprintf(stdout,"ave=%f\n", v);
}

