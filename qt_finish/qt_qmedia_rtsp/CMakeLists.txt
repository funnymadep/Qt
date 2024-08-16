cmake_minimum_required(VERSION 3.10)
project(rtsp)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
aux_source_directory(./src SRC_LIST)  

# find dependencies
find_package(Qt5 COMPONENTS Core Widgets Gui Network Multimedia MultimediaWidgets REQUIRED)
# find_library(jawt HINTS ${JAVA_HOME}/lib ${JAVA_HOME}/lib/server)
# if (NOT JAWT_LIBRARY)
#     message(${JAVA_HOME})
#     message(FATAL_ERROR "libjawt.so not found")
# endif()





add_executable(${PROJECT_NAME}  ${SRC_LIST} )

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::MultimediaWidgets)

