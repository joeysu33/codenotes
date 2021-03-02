#!/usr/bin/awk -f

###函数必须定义在三个域的外部"{xxx}"
function sort1(a, n) {
    #i=0;j=0; h=0.0;
    for(i=0; i<n-1;++i)   {
        //j总是从0开始比较
        for(j=0; j<n-i-1;++j) {
            if(a[j] > a[j+1]) 
            {
                #printf("j=%d,j+1=%d, a[j]=%.2f, a[j+1]=%.2f\n", j, j+1,a[j], a[j+1]);
                h = a[j];
                a[j] = a[j+1];
                a[j+1] = h;
            }
        }
        #break;
    }
}

function pr(a, n, s) {
    if(s) printf("%s:\n", s); 
    for(i=0; i<n;++i) {
        printf("%-.2f, ",a[i]);
    }
    printf("\n");
}

BEGIN {
a[0]=4;
a[1]=90;
a[2]=6.9;
a[3]=8;
a[4]=10;
a[5]=1;
a[6]=60;
a[7]=7.8;
a[8]=9.3;

pr(a,9);
sort1(a,9);
pr(a,9,"sorted");
}





