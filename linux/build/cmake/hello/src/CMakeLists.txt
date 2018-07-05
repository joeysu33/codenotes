set(SRC_FILES
    "main.c"
    )

#PROJECT_SOURCE_DIR应该是定义project的目录---
include_directories(${PROJECT_SOURCE_DIR}/libhello)
link_directories(${CMAKE_INSTALL_PREFIX}/lib)

#aux_source_directory(<dir> <variable>)
#在指定的目录搜索源文件,注意仅包含源文件，并将结果存储至variable变量内
add_executable(hello ${SRC_FILES})

#指定hello目标链接所需要的库 libhello
target_link_libraries(hello libhello)

install(TARGETS hello RUNTIME DESTINATION bin)
set_property(TARGET hello PROPERTY INSTALL_RPATH_USE_LINK_PATH)
