cmake_minimum_required (VERSION 3.1)
project (ringbuff)

#添加子目录
#ADD_SUBDIRECTORY(log)

aux_source_directory(. dir_src)
add_executable(demo ${dir_src})

#添加头文件目录
include_directories(./log)

