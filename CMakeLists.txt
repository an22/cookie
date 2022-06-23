# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project(cookie-solution VERSION 0.0.1)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list src/*.h src/*.hpp)
    SET(dir_list "")
    FOREACH (file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH ()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
    list(LENGTH HEADER_DIRS header_dir_list_count)
    message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")
ENDMACRO()

function(install_default_dependencies TARGET_NAME)
    find_library(glm SHARED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(Ktx REQUIRED)
    find_package(zstd CONFIG REQUIRED)
    if (UNIX)
        find_package(Threads REQUIRED)
        target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads)
    endif ()

    target_link_libraries(${TARGET_NAME} PUBLIC ${OPENGL_LIBRARIES})
    target_link_libraries(${TARGET_NAME} PUBLIC GLEW::GLEW)
    target_link_libraries(${TARGET_NAME} PUBLIC glfw)
    target_link_libraries(${TARGET_NAME} PUBLIC KTX::ktx)
    target_link_libraries(${TARGET_NAME} PUBLIC $<IF:$<TARGET_EXISTS:zstd::libzstd_shared>,zstd::libzstd_shared,zstd::libzstd_static>)
    target_link_libraries(${TARGET_NAME} PRIVATE glm)
endfunction()

add_subdirectory(lib/glm)
add_subdirectory("${PROJECT_SOURCE_DIR}/engine")
add_subdirectory("${PROJECT_SOURCE_DIR}/jni")
