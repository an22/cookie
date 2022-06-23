# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.
set(VERSION_NUM 0.0.1)
project(cookie VERSION ${VERSION_NUM})
SET(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Locate all files and headers
HEADER_DIRECTORIES(HEADER_DIRS)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.hpp"
        "src/*.c"
        "src/*.h"
        )

if (ANDROID)
    find_library(log-lib log)
    find_library(libGLESv3 SHARED)
    find_library(libEGL SHARED)

    #Libktx
    add_library(libktx SHARED IMPORTED)
    set_target_properties(libktx PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../jni/${ANDROID_ABI}/libktx.so)

    #cookie
    add_library(cookie SHARED ${SRC_LIST})

    target_include_directories(cookie PUBLIC ${HEADER_DIRS})
    target_link_libraries(cookie GLESv3)
    target_link_libraries(cookie EGL)
    target_link_libraries(cookie ${log-lib})
    target_link_libraries(cookie android)
    target_link_libraries(cookie libktx)
else ()
    add_executable(cookie ${SRC_LIST})
    add_library(CookieEngine OBJECT ${SRC_LIST})
    add_library(CookieEngineShared SHARED $<TARGET_OBJECTS:CookieEngine>)
    add_library(CookieEngineStatic STATIC $<TARGET_OBJECTS:CookieEngine>)

    target_include_directories(cookie PUBLIC ${HEADER_DIRS})
    target_include_directories(CookieEngine PUBLIC ${HEADER_DIRS})
    target_include_directories(CookieEngineShared PUBLIC ${HEADER_DIRS})
    target_include_directories(CookieEngineStatic PUBLIC ${HEADER_DIRS})

    install_default_dependencies(cookie)
    install_default_dependencies(CookieEngine)
    install_default_dependencies(CookieEngineShared)
    install_default_dependencies(CookieEngineStatic)


    # Export headers
    #    file(GLOB_RECURSE PUBLIC_HEADER_LIST CONFIGURE_DEPENDS "src/*.hpp" "src/*.h")
    #    add_custom_command(TARGET CookieEngine PRE_BUILD COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_BINARY_DIR}/include)
    #    add_custom_command(TARGET CookieEngine PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/include)
    #    add_custom_command(
    #            TARGET CookieEngine POST_BUILD
    #            COMMAND ${CMAKE_COMMAND} -E copy
    #            ${PUBLIC_HEADER_LIST}
    #            ${PROJECT_BINARY_DIR}/include/)


endif ()
