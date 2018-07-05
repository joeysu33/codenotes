#设置需要最低版本的CMAKE
cmake_minimum_required(VERSION 2.8.12)

#设置项目名称(PROJECT_NAME)
project(HELLO)

message("PROJET_NAME= " ${PROJECT_NAME})
set(CMAKE_INSTALL_PREFIX /tmp/hello)

#增加子项目对象,分别是libhello和src，其对应子目录
add_subdirectory(libhello)
add_subdirectory(src)


