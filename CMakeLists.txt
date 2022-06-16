cmake_minimum_required(VERSION 3.10)
project(logWrapper CXX)

set(CMAKE_CXX_STANDARD 17)  # ROS2 

#set(GLOG_INCLUDE_PATH /root/liqiang/glog/build)
#set(SPD_INCLUDE_PATH /root/liqiang/spdlog/include)
#set(ROS_INCLUDE_PATH /opt/ros/galactic/include)
#find_package(rclcpp)
include_directories(./include)
#include_directories(${SPD_INCLUDE_PATH})
#include_directories(${GLOG_INCLUDE_PATH})
#include_directories(${ROS_INCLUDE_PATH})


add_executable(logWrapper main.cpp src/LogWrapper.cpp)

#target_link_libraries(logWrapper 
 #               /root/liqiang/glog/build/libglog.so 
 #               libpthread.so
 #               /opt/ros/galactic/lib/librclcpp.so
 #               /opt/ros/galactic/lib/librcutils.so
 #               )
