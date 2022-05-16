# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project(cookie VERSION 0.0.1)
SET(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h *.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

add_subdirectory(lib/glm)

#Find libraries
find_library(log-lib log)
find_library(libGLESv3 SHARED)
find_library(libEGL SHARED)
find_library(glm SHARED)

#Locate all files and headers
HEADER_DIRECTORIES(HEADER_DIRS)

list(LENGTH HEADER_DIRS header_dir_list_count)
message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
        "*.cpp"
        "*.hpp"
        "*.c"
        "*.h"
        )


#Libktx
add_library(libktx SHARED IMPORTED)
set_target_properties(libktx PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../jni/${ANDROID_ABI}/libktx.so)

#cookie
add_library(cookie SHARED ${SRC_LIST})

target_include_directories(cookie PUBLIC ${HEADER_DIRS})

target_link_libraries(cookie GLESv3)
target_link_libraries(cookie EGL)
target_link_libraries(cookie glm)
target_link_libraries(cookie ${log-lib})
target_link_libraries(cookie libktx)
target_link_libraries(cookie android)

install(
        TARGETS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)