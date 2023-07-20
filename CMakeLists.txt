cmake_minimum_required(VERSION 3.10)

project(Glut_Village_Scenario)
set(CMAKE_CXX_STANDARD 11)

find_package(GLUT REQUIRED)

add_executable(Glut_Village_Scenario main.cpp)
target_link_libraries(Glut_Village_Scenario ${GLUT_LIBRARIES} GL)
