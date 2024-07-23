cmake_minimum_required(VERSION 3.10)
project(hit_menu)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
aux_source_directory(./src SRC_LIST)  

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Gui Network Multimedia MultimediaWidgets REQUIRED)
find_package(PCL COMPONENTS io common compression visualization REQUIRED)
find_package(VTK REQUIRED)
find_package(pcl_conversions REQUIRED)
# find_library(jawt HINTS ${JAVA_HOME}/lib ${JAVA_HOME}/lib/server)
# if (NOT JAWT_LIBRARY)
#     message(${JAVA_HOME})
#     message(FATAL_ERROR "libjawt.so not found")
# endif()

include_directories(
  src
  ${PCL__DIRS}
  ${pcl_conversions_INCLUDE_DIRS}
)


link_directories( ${PCL_LIBRARY_DIRS})
link_directories( /usr/lib/jvm/java-17-openjdk-amd64/lib)
add_definitions(${PCL_DEFINITIONS})

include_directories(include ${PCL_INCLUDE_DIRS} )


add_executable(${PROJECT_NAME}  ${SRC_LIST} resources.qrc)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::MultimediaWidgets)
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${pcl_conversions_LIBRARIES} ${JAVA})

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  sensor_msgs
  PCL
  pcl_conversions
)

# Install executable
install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

# Install include directories
install(DIRECTORY src/
  DESTINATION src/)

ament_package()
