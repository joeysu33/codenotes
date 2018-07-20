cmake_minimum_required(VERSION 2.8.3)

project(Algorithms)

set(EXECUTABLE_OUTPUT_PATH ./bin)
set(LIBRARY_OUTPUT_PATH ./lib)

#将指定目录下的所有源文件存储到指定的变量
#aux_source_directory(<dir> <variable>)

aux_source_directory(. srcs)

foreach(i ${srcs})
    #string(SUBSTRING string (begin) (end,or-1) (variable))
    string(SUBSTRING ${i} 2 -1 filename)
    string(REPLACE ".c" "" basename ${filename}) #将文件名称中的.c去掉，保留basename,basename作为输出
    add_executable(${basename} ${filename})
endforeach()

