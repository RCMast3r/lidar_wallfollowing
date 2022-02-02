cmake_minimum_required(VERSION 3.5)
project(lidar_wallfollowing)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)



catkin_package(
  CATKIN_DEPENDS
    roscpp
    std_msgs
)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include

)
add_executable(lidar_wallfollowing_node 
  src/main.cpp
  src/lidar_wallfollowing.cpp

)
target_link_libraries(lidar_wallfollowing_node 
   ${catkin_LIBRARIES} 
 )
install(TARGETS lidar_wallfollowing_node 
 ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
