# CMake 最低版本要求
#cmake_minimum_required(VERSION 3.0 FATAL_ERROR)#new
cmake_minimum_required(VERSION 2.8.3) 
project(ican_vision)

# 库文件的放置目录
set(OpenCV_DIR /home/liqianqi/opencv-3.4.14/build)

# 开启 DeBug 调试
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# C++11 标准、o3优化、多线程
set(CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS} -o3 -pthread")


find_package(OpenCV REQUIRED)


include_directories($(OpenCV_INCLUDE_DIRS)) 


include_directories("/usr/incude/eigen3")#new
include_directories(${OpenCV_INCLUDE_DIRS} )


include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)


set(CPP_SOURCES 
    main.cpp
    icanvision.cpp
    measure.cpp
    serial.cpp
    dector.cpp
)


## 指定生成目标
add_executable(ican_vision ${CPP_SOURCES})


target_link_libraries(ican_vision ${OpenCV_LIBS} )#new

