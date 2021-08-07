cmake_minimum_required(VERSION 3.20)

project(cookie-engine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
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
        src/opengl-api/OpenGLPlatformSpecificData.cpp
        src/opengl-api/buffer/OpenGLBufferStorage.cpp
        src/opengl-api/initializer/OpenGLInitializer.cpp
        src/opengl-api/shader/OpenGLShader.cpp
        src/opengl-api/time/OpenGLTime.cpp
        src/cookie-engine/struct/BufferStorage.cpp
        src/cookie-engine/base/Scene.cpp)

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

find_package(OpenGL REQUIRED)
target_link_libraries(cookie-engine PRIVATE ${OPENGL_LIBRARIES})
find_package(GLEW REQUIRED)
target_link_libraries(cookie-engine PRIVATE GLEW::GLEW)
find_package(glfw3 REQUIRED)
target_link_libraries(cookie-engine PRIVATE glfw)
find_package(glm REQUIRED)
target_link_libraries(cookie-engine PRIVATE ${GLM_LIBRARIES})