cmake_minimum_required(VERSION 3.16)
project(xbot_joint_state_republisher)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(xbot_msgs REQUIRED)

add_library(xbot_joint_state_republisher_component SHARED
  src/xbot_joint_state_republisher_node.cpp
)

target_include_directories(xbot_joint_state_republisher_component PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(xbot_joint_state_republisher_component
  rclcpp
  rclcpp_components
  sensor_msgs
  xbot_msgs
)

rclcpp_components_register_node(
  xbot_joint_state_republisher_component
  PLUGIN "xbot_joint_state_republisher::XbotJointStateRepublisher"
  EXECUTABLE xbot_joint_state_republisher
)

ament_export_targets(export_xbot_joint_state_republisher_component)

install(
  TARGETS xbot_joint_state_republisher_component
  EXPORT export_xbot_joint_state_republisher_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include/
)

ament_package()
