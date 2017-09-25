cmake_minimum_required(VERSION 2.8.4)
project(saveEndoscopeVideo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp webcam.cpp
        resource.cpp resource.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_BUILD_TYPE Debug)

# Where to find CMake modules and OpenCV and Dynamixel
if (WIN64 OR WIN32 OR MSVC OR MINGW OR MSYS)
    set(OpenCV_DIR "C:/Users/jg5915/Documents/opencv320/mingw-build/install")
endif (WIN64 OR WIN32 OR MSVC OR MINGW OR MSYS)

if (UNIX)
    set(OpenCV_DIR "/home/jg5915/Documents/opencv/build")
endif(UNIX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#set(CTR_INCLUDE include DynamixelDependencies/c++/include
#        CACHE INTERNAL "Include directories needed for the CTR library" FORCE)
include_directories(${CTR_INCLUDE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Set library for thread usage
find_package(Threads)

# Opencv libs and camera decoding
find_package(OpenCV REQUIRED)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_tracking avformat avdevice avcodec avutil swscale)
set(DYNAMIXEL_LIB dxl_x64_cpp)

# Comand line interface
#add_executable(test_endo grab.cpp webcam.cpp)
add_executable(saveEndoscopeVideo ${SOURCE_FILES})

# linking the libraries
target_link_libraries(saveEndoscopeVideo ${OpenCV_LIBS})
target_link_libraries(saveEndoscopeVideo ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(saveEndoscopeVideo ${DYNAMIXEL_LIB})

# add the install targets
install (TARGETS saveEndoscopeVideo DESTINATION bin)
