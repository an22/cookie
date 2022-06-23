# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project(jnicookie VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

find_package(JNI REQUIRED)

set(LIB_NAME jnicookie)

add_library(${LIB_NAME} SHARED src/NativeBridge.cpp)

target_include_directories(${LIB_NAME} PUBLIC ${JNI_INCLUDE_DIRS})
target_include_directories(${LIB_NAME} PUBLIC include)
target_link_libraries(${LIB_NAME} PRIVATE ${JNI_LIBRARIES})
target_link_libraries(${LIB_NAME} PRIVATE CookieEngineStatic)
install_default_dependencies(${LIB_NAME})
