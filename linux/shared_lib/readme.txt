Linux下动态库的编译(c版)
gcc -fPIC -shared -o libXX.so XX.c

注意事项
1.编译的结果必须是libXXX.so，因为使用动态库的时候如果依赖的是-lXXX,
  那么自动从库搜索目录中查找libXXX.so
2.-fPIC 选项用来指明位置无关代码,产生的代码全部使用相对地址
  PIC Position Independent Code
3.C++链接C函数的时候一定需要增加extern "C"
  例如 extern "C" { #include "cfunctions.h" }
  或者 extern "C" void add(int, int);

4.在共享库中设置别名soname
-Wl,-soname,libQmlDebug.so.4 给动态库设置别名，这样在动态库的搜索的时候会按照这个名称来进行搜索（采用软连接），
这样自动引入了版本的概念，避免在搜索的过程中使用了错误的动态库的版本
其中-Wl设置连接选项 -Wl,option,XXXX
连接选项
-Wl,option
   Pass option as an option to the linker.  If option contains commas, it is split into multiple options at the commas.
   You can use this syntax to pass an argument to the option.  For example,
   -Wl,-Map,output.map passes -Map output.map to the linker.  When using the GNU linker, you can also get the same effect with -Wl,-Map=output.map.

5.在共享库中设置运行目录，如果没有设置-rpath，可以在环境变量中设置LD_RUN_PATH
-Wl,-rpath,/home/ds/Qt/Qt5.8.0/5.8/gcc_64/lib

6.在共享库设置$ORIGIN,指定一个相对于当前目录的运行路径,参考ld_var_origin.txt
-Wl,-z,origin '-Wl,-rpath,$$ORIGIN'  #这里需要注意的是ORIGIN需要使用"$$"来修饰,要使用''来标识，避免$ORIGIN转义
或者
-Wl,-rpath,'$$ORIGIN'
上述两种方法的区别是，第一种会在dynamic段中生成一个FLAGS_1 ORIGIN，第二种方式不会,可以使用readelf -d XXX来输出查看


7.动态库中几个重要的环境变量
LD_LIBRARY_PATH 如果可执行文件是一个set-user-id或set-group-id程序，那么就会忽略LD_LIBRARY_PATH变量，这么做是为了防止用户欺骗动态链接器让其加载与可执行文件所需库同名的私有库,
                否则私有的动态库就会获取可执行文件的特权（变相获取了用户特权，文件漏洞)
LD_RUN_PATH (当没有设置-rpath的时候)

8.控制动态库中函数的可见性
动态库中默认符号的可见性是GLOBAL，可以通过readelf -s XXX来输出查看
如果对函数增加attribte修饰，可以设置可见性为LOCAL，（类似static对文件外不可见)
void __attribute__((visibility("hidden"))) function() { }


参见qtcreator中libQmlDebug库的Makefile
LFLAGS        = -Wl,-z,origin '-Wl,-rpath,$$ORIGIN:$$ORIGIN/..:$$ORIGIN/../lib/qtcreator' -Wl,-O1 -Wl,-rpath,/home/ds/Qt/Qt5.8.0/5.8/gcc_64/lib -shared -Wl,-soname,libQmlDebug.so.4
LIBS          = $(SUBLIBS) -L/home/ds/sources/qt-creator-opensource-src-4.4.0/lib/qtcreator -lUtils -L/home/ds/Qt/Qt5.8.0/5.8/gcc_64/lib -lQt5Widgets -lQt5Gui -lQt5Network -lQt5Concurrent -lQt5Core -lGL -lpthread
AR            = ar cqs
RANLIB        =
SED           = sed
STRIP         = strip

在QtCreator中可以直接给RPATH来设置依赖的库路径
