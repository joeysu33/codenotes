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

5.在共享库中设置LD_LIBRARY_PATH
-Wl,-rpath,/home/ds/Qt/Qt5.8.0/5.8/gcc_64/lib

参见qtcreator中libQmlDebug库的Makefile
LFLAGS        = -Wl,-z,origin '-Wl,-rpath,$$ORIGIN:$$ORIGIN/..:$$ORIGIN/../lib/qtcreator' -Wl,-O1 -Wl,-rpath,/home/ds/Qt/Qt5.8.0/5.8/gcc_64/lib -shared -Wl,-soname,libQmlDebug.so.4
LIBS          = $(SUBLIBS) -L/home/ds/sources/qt-creator-opensource-src-4.4.0/lib/qtcreator -lUtils -L/home/ds/Qt/Qt5.8.0/5.8/gcc_64/lib -lQt5Widgets -lQt5Gui -lQt5Network -lQt5Concurrent -lQt5Core -lGL -lpthread
AR            = ar cqs
RANLIB        =
SED           = sed
STRIP         = strip


