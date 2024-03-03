cmake_minimum_required(VERSION 3.27)
project(CG2)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(soil CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLUT REQUIRED)
find_package(Stb REQUIRED)
find_package(GLEW REQUIRED)


add_executable(CG2 main.cpp)

target_link_libraries(CG2 PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(CG2 PRIVATE soil)
target_link_libraries(CG2 PRIVATE glfw)
target_include_directories(CG2 PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(CG2 PRIVATE GLUT::GLUT)
target_include_directories(CG2 PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(CG2 PRIVATE GLEW::GLEW)
