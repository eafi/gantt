cmake_minimum_required(VERSION 3.15)
project(gantt)

set(CMAKE_CXX_STANDARD 11)
IF (WIN32)
	set(OpenCV_DIR "C:/libraries/OpenCV")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
	find_package(OpenCV REQUIRED)
ELSEIF (APPLE)
	find_package(OpenCV)
	include_directories($OpenCV_INCLUDE_DIRS})
ENDIF ()
add_executable(gantt main.cpp Machine.h Job.h Gantt.cpp Gantt.h clrmap.h)
set(OpenCV_LIBS opencv_core opencv_highgui)
target_link_libraries(gantt ${OpenCV_LIBS})