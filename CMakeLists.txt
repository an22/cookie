cmake_minimum_required(VERSION 3.20)

project(cookie-engine VERSION 0.0.1)
SET(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(zstd REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_package(Ktx CONFIG REQUIRED)

if(APPLE)
set_target_properties(assimp::assimp PROPERTIES MAP_IMPORTED_CONFIG_DEBUG Release)
target_include_directories(cookie-engine PUBLIC /usr/local/lib)
endif()

add_executable(cookie-engine src/main.cpp
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
		src/cookie-engine/base/BatchManager.cpp src/cookie-engine/base/BatchManager.hpp src/cookie-engine/base/Batch.cpp src/cookie-engine/base/Batch.hpp src/cookie-engine/platform_abstracts/CrossBatchBufferStorage.hpp src/opengl-api/buffer/OpenGlCrossBatchBufferStorage.cpp src/opengl-api/buffer/OpenGlCrossBatchBufferStorage.hpp src/cookie-engine/base/BatchConfig.hpp src/cookie-engine/util/Utils.cpp src/cookie-engine/util/Utils.hpp src/opengl-api/initializer/OpenGLCookieFactory.cpp src/opengl-api/initializer/OpenGLCookieFactory.h src/cookie-engine/struct/CgAPI.h)

target_include_directories(cookie-engine PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(cookie-engine PUBLIC ${ASSIMP_INCLUDE_DIRS})
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/base)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/component)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/draw)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/errors)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/shader)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/struct)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/time)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/util)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/cookie-engine/platform_abstracts)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/factory)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/util)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/buffer)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/initializer)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/shader)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/time)
target_include_directories(cookie-engine PUBLIC ${CMAKE_SOURCE_DIR}/src/opengl-api/draw)

target_link_libraries(cookie-engine PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(cookie-engine PRIVATE GLEW::GLEW)
target_link_libraries(cookie-engine PRIVATE glfw)
target_link_libraries(cookie-engine PRIVATE ${GLM_LIBRARIES})
target_link_libraries(cookie-engine PRIVATE assimp::assimp)
target_link_libraries(cookie-engine PRIVATE KTX::ktx)

install(
		TARGETS cookie-engine
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
