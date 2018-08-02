cmake_minimum_required(VERSION 3.5)

project (training)
set(EXECUTABLE_OUTPUT_PATH ./bin)
set(PROJECT_VERSION 1.0.0)

aux_source_directory(. Srcs)
set(LIBRARY_OUTPUT_PATH ./lib)
add_compile_options(-g)

foreach(i ${Srcs})
    string(SUBSTRING ${i} 2 -1 FileName)
    string(REPLACE ".c" "" BaseFileName ${FileName})
    add_executable(${BaseFileName} ${i})
endforeach()

