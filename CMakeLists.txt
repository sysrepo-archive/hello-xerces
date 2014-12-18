cmake_minimum_required(VERSION 3.0)
PROJECT(hello-xerces)
ADD_DEFINITIONS(-Os -Wall -Wmissing-declarations)
INCLUDE_DIRECTORIES(include)

FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/modules")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(SOURCES
	src/main.cpp
)

ADD_EXECUTABLE(hello-xerces ${SOURCES})

#FIND_PACKAGE(LIBXERCES REQUIRED)
#INCLUDE_DIRECTORIES(${LIBXERCES_INCLUDE_DIR})
#TARGET_LINK_LIBRARIES(hello-xerces ${LIBXERCES_LIBRARIES})

#include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)
find_package(PkgConfig)

pkg_check_modules (XERCES REQUIRED xerces-c)
include_directories(${XERCES_INCLUDE_DIRS})
link_directories(${XERCES_LIBRARY_DIRS})
target_link_libraries(hello-xerces ${XERCES_LIBRARIES})
