CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

# set the project name.
PROJECT(wire_com_setup VERSION 1.0)

# include directories.
INCLUDE_DIRECTORIES(include)

# set good gcc version.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -L/usr/local/lib -lserial -pthread -o CPUUsage")

############################################

# TEST CODE COMMUNICATION
ADD_EXECUTABLE(test-cpp 
    software/main.cpp)
TARGET_LINK_LIBRARIES(test-cpp 
    serial)