cmake_minimum_required(VERSION 3.10)
project(TCP)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
aux_source_directory(./src SRC_LIST)  

find_package(Qt5 COMPONENTS Core Widgets Gui Network   REQUIRED)
find_package(PCL  REQUIRED)

add_executable(${PROJECT_NAME}  ${SRC_LIST})
 
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

