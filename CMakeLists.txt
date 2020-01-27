cmake_minimum_required(VERSION 2.8)
project(labelRabel)
find_package(OpenCV REQUIRED)

set(sources main.cpp)

add_executable(labelRabel ${sources})



target_compile_options( labelRabel PUBLIC -std=c++11 -fpermissive -w -Wall )

target_link_libraries( labelRabel ${OpenCV_LIBS} -L/usr/lib64 -ldl)
