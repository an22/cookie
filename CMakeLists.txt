cmake_minimum_required(VERSION 3.20)

project(cookie-engine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(cookie-engine src/main.cpp
        src/cookie-engine/base/SceneObject.cpp
        src/cookie-engine/component/Mesh.cpp
        src/cookie-engine/errors/GLErrorHandler.cpp
        src/cookie-engine/shader/ShaderManager.cpp
        src/cookie-engine/struct/FramerateInfo.cpp
        src/cookie-engine/struct/SceneSettings.cpp
        src/cookie-engine/util/Constants.cpp
        src/cookie-engine/Cookie.cpp
        src/factory/CookieFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/opengl-api/OpenGLPlatformSpecificData.cpp
        src/opengl-api/buffer/OpenGLBufferStorage.cpp
        src/opengl-api/initializer/OpenGLInitializer.cpp
        src/opengl-api/shader/OpenGLShader.cpp
        src/opengl-api/time/OpenGLTime.cpp)

target_include_directories(cookie-engine PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/lib/glew/include)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/base)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/component)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/draw)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/errors)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/shader)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/struct)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/time)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/util)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/factory)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/buffer)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/initializer)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/shader)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/time)

# glfw
add_subdirectory(lib/glfw-3.3.4 EXCLUDE_FROM_ALL)
target_link_libraries(cookie-engine PRIVATE glfw ${GLFW_LIBRARIES})

# glew
find_package(GLEW REQUIRED)
add_subdirectory(lib/glew)
include_directories(glew/include)
target_link_libraries(cookie-engine PRIVATE GLEW::GLEW)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(cookie-engine PRIVATE glm)

target_compile_features(cookie-engine PRIVATE cxx_std_17)