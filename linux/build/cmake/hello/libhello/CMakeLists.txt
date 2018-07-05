set(LIB_SRC hello.c)
add_definitions("-DLIBHELLO_BUILD")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#生成共享库
add_library(libhello SHARED ${LIB_SRC} )
#生成静态库,可以省略STATIC，默认STATIC
add_library(hello_static STATIC ${LIB_SRC})

#DESTINATION表示目标目录下的子目录位置
#安装目标,共享库
install(TARGETS libhello LIBRARY DESTINATION lib)
#安装目标,归档文件(静态库)
install(TARGETS hello_static ARCHIVE DESTINATION lib)
#安装附属文件，例如头文件资源文件等
install(FILES hello.h DESTINATION include)

#如果不加上OUTPUT_NAME，则默认输出liblibhello.so,输出libhello.so
set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")
#如果不加上OUTPUT_NAME，则默认输出libhello_static.a，输出libhello-st.a
set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello-st")

