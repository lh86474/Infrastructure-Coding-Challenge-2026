cmake_minimum_required(VERSION 3.8)
project(infra_coding_challenge_package)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(adder_node src/adder_node.cpp)
target_compile_features(adder_node PUBLIC cxx_std_17)

ament_target_dependencies(adder_node
  rclcpp
  std_msgs
)

install(TARGETS adder_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
