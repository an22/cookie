# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project(cookie VERSION 0.0.1)
SET(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/glm)

find_library(log-lib log)
find_library(libGLESv3 SHARED)
find_library(libEGL SHARED)
find_library(glm SHARED)

add_library(libktx SHARED IMPORTED)
add_library(ofbx SHARED lib/miniz.h lib/miniz.c lib/ofbx.h lib/ofbx.cpp)
add_library(cookie SHARED cookie.cpp src/core.cpp
        src/cookie-engine/base/SceneObject.cpp
        src/cookie-engine/component/Mesh.cpp
        src/cookie-engine/errors/GLErrorHandler.cpp
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
        src/cookie-engine/platform_abstracts/BufferStorage.cpp
        src/cookie-engine/base/Scene.cpp src/util/Util.cpp
        src/util/Util.h
        src/cookie-engine/platform_abstracts/DrawUtils.h
        src/opengl-api/draw/OpenGLDrawUtils.cpp
        src/opengl-api/draw/OpenGLDrawUtils.h
        src/cookie-engine/platform_abstracts/Shader.cpp
        src/cookie-engine/draw/Cube.cpp
        src/cookie-engine/platform_abstracts/PlatformSpecificBufferData.h
        src/opengl-api/buffer/OpenGLPSBufferData.cpp
        src/opengl-api/buffer/OpenGLPSBufferData.h
        src/cookie-engine/component/Material.cpp
        src/cookie-engine/component/Material.h
        src/cookie-engine/component/MeshStruct.cpp
        src/cookie-engine/component/MeshStruct.h
        src/cookie-engine/platform_abstracts/TextureProcessor.cpp
        src/cookie-engine/platform_abstracts/TextureProcessor.hpp
        src/opengl-api/draw/OpenGLTextureProcessor.cpp
        src/opengl-api/draw/OpenGLTextureProcessor.hpp
        src/cookie-engine/platform_abstracts/ErrorHandler.cpp
        src/cookie-engine/platform_abstracts/ErrorHandler.hpp
        src/cookie-engine/base/AssetImporter.cpp
        src/cookie-engine/base/AssetImporter.hpp
        src/cookie-engine/base/BatchManager.cpp
        src/cookie-engine/base/BatchManager.hpp
        src/cookie-engine/base/Batch.cpp
        src/cookie-engine/base/Batch.hpp
        src/cookie-engine/platform_abstracts/CrossBatchBufferStorage.hpp
        src/opengl-api/buffer/OpenGlCrossBatchBufferStorage.cpp
        src/opengl-api/buffer/OpenGlCrossBatchBufferStorage.hpp
        src/cookie-engine/base/BatchConfig.hpp
        src/cookie-engine/util/Utils.cpp
        src/cookie-engine/util/Utils.hpp
        src/opengl-api/initializer/OpenGLCookieFactory.cpp
        src/opengl-api/initializer/OpenGLCookieFactory.h
        src/cookie-engine/struct/CgAPI.h
        src/util/Macro.h
        src/cookie-engine/platform_abstracts/Time.hpp
        src/cookie-engine/platform_abstracts/Time.cpp
        src/core.hpp
        src/cookie-engine/io/FileManager.hpp
        src/platform/AndroidFileManager.hpp
        src/platform/AndroidFileManager.cpp)


set_target_properties(libktx PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../jni/${ANDROID_ABI}/libktx.so)
add_compile_definitions(BASE_DIR="${CMAKE_SOURCE_DIR}/")

target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/base)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/component)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/draw)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/errors)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/shader)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/struct)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/time)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/util)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/platform)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/platform_abstracts)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/factory)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/util)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/buffer)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/initializer)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/shader)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/time)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/draw)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/lib/glm)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(cookie PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/io)

target_link_libraries(cookie GLESv3)
target_link_libraries(cookie EGL)
target_link_libraries(cookie glm)
target_link_libraries(cookie ${log-lib})
target_link_libraries(cookie libktx)
target_link_libraries(cookie ofbx)
target_link_libraries(cookie android)

install(
        TARGETS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)