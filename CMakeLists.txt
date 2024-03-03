cmake_minimum_required(VERSION 3.27)
project(CG2)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(soil CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLUT REQUIRED)
find_package(Stb REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)


add_executable(CG2_m1 main.cpp
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3_loader.h)
add_executable(CG2_m2 main2.cpp)

target_link_libraries(CG2_m1 PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(CG2_m1 PRIVATE soil)
target_link_libraries(CG2_m1 PRIVATE glfw)
target_include_directories(CG2_m1 PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(CG2_m1 PRIVATE GLUT::GLUT)
target_include_directories(CG2_m1 PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(CG2_m1 PRIVATE GLEW::GLEW)
target_link_libraries(CG2_m1 PRIVATE imgui::imgui)
