Linux下动态库的编译(c版)
gcc -fPIC -shared -o libXX.so XX.c

注意事项
1.编译的结果必须是libXXX.so，因为使用动态库的时候如果依赖的是-lXXX,
  那么自动从库搜索目录中查找libXXX.so
2.-fPIC 选项用来指明位置无关代码,产生的代码全部使用相对地址
  PIC Position Independent Code


