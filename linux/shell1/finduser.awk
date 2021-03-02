#!/usr/bin/awk -f

#查找passwd中用户名称的 uid和gid并打印出来

BEGIN {
    #for(i in ARGV) {
    #    printf("ARGV[%s]=%s\n", i, ARGV[i]);
    #}
    FS=":";
    name="";
    #getline name;
    #print("name=", name);
    if (ARGC < 2) {
       #输入要查询的用户名称
        #while(!name)  {
            #print("Please , Enter a name:");
            #将输入读取到name
            getline name
            print("name=", name);
        #} 
    } else {
            name = ARGV[1];
            #必须要删除该参数，否则该参数作为文件名称解析读取
            delete ARGV[1]; 
    }
}

#Processing
#/pattern/{process}
$1~name { print($1,$3,$4) }; 

#or
#{
#    if(match($1,name)) {
#        print($1,$3,$4);
#    } 
#}
#

#End

